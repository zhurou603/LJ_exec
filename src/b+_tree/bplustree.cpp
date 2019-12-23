#include"bplustree.h"
#include<iostream>

using namespace std;

void BplusTree::insert(Key key, Value value){
  //如果一开始为空树，则加入一个叶子结点
  if(!root_){
    insert_empty_tree(key, value);
    return;
  }else{
    //找到对应叶子结点插入
    insert_to_leaf(key, value);
  }
}

void BplusTree::insert_empty_tree(Key key, Value value){
  LeafNode* new_leaf = new LeafNode(tree_degree_);
  //向叶子结点添加一个记录
  new_leaf->create_and_append(key,value);
  //合理的转换，派生类的指针向基类指针
  root_ = new_leaf;
}

void BplusTree::insert_to_leaf(Key key, Value value){
  //先通过search找到对应叶子结点，再修改对应Record
  LeafNode* find = nullptr;
  Node* node = root_;
  while(!node->is_leaf()){
    //不是叶子结点时要找到internode中对应的值
    auto inter =  static_cast<InterNode*>(node);
    node = inter->find(key);
  }
  find = static_cast<LeafNode*>(node);
  //在叶子结点找到对应record
  Record* record = find->search(key);
  if(record){
    record->set(value);
    return;
  }
  //添加新纪录
  int new_size = find->create_and_append(key,value);
  //超过最大size则调整
  if(new_size > find->max_size()){
    //split返回新产生的结点
    LeafNode* new_leaf = split(find);
    //建立链表关系
    new_leaf->set_next(find->get_next());
    find->set_next(new_leaf);
    //向上递归更新key
    Key new_first = new_leaf->first_key();
    insert_key_to_parent(find, new_first, new_leaf);
  }
}

template<typename T>
T* BplusTree::split(T* node){
  //传递parent关系
  T* new_node = new T(tree_degree_, node->get_parent());
  //拷贝
  node->move_half_to(new_node);
  return new_node;
}

void BplusTree::insert_key_to_parent(Node* old_node, Key key, Node* new_node){
  //先获取parent结点
  InterNode* parent = static_cast<InterNode*>(old_node->get_parent());
  //根结点没有父结点
  if(!parent){
    //创建新的根结点
    root_ = new InterNode(tree_degree_);
    parent = static_cast<InterNode*>(root_);
    old_node->set_parent(parent);
    new_node->set_parent(parent);
    //填充新的根
    parent->fill_new_root(old_node, key, new_node);
  }else{
    //如果还没更新到根结点,插入key到parent结点中old_node之后的位置
    int new_size = parent->insert_after_old(old_node, key, new_node);
    //B+树如果degree为3，包含dummy key应该要4才split
    if(new_size-1 > parent->max_size()){
      InterNode* after_split = split(parent);
      Key new_key = after_split->replace_first_key();
      //递归更新
      insert_key_to_parent(parent, new_key, after_split);
    }
  }
}

void BplusTree::print_all(){
  if(!root_){
    cout <<"empty" << endl;
    return;
  }
  auto node = root_;
  while(!node->is_leaf()){
    node = static_cast<InterNode*>(node)->get_first_child();
  }
  LeafNode* leaf = static_cast<LeafNode*>(node);
  while(leaf){
    leaf->printleaf();
    leaf = leaf->get_next();
    cout << "一组结束" << endl;
  }
}

void BplusTree::bfs_key(vector<Key>* result){
  Node* node = root_;
  queue<Node*> nodes;
  nodes.push(node);
  while(!nodes.empty() && !nodes.front()->is_leaf()){
    node = nodes.front();
    InterNode* inter = static_cast<InterNode*>(node);
    inter->append_element_to_vector(result);
    nodes.pop();
    //遍历孩子
    inter->append_child_to_queue(&nodes);
  }
}

void BplusTree::remove(Key key){
  if(!root_) return;
  remove_leaf(key);
}

void BplusTree::remove_leaf(Key key){
  //查找如果没有对应LeafNode则删除失败
  LeafNode* target_leaf = nullptr;
  Node* node = root_;
  while(!node->is_leaf()){
    InterNode* inter = static_cast<InterNode*>(node);
    node = inter->find(key);
  }
  target_leaf = static_cast<LeafNode*>(node);
  if(!target_leaf) return;
  //查找是否有对应Record
  if(!target_leaf->search(key)) return;
  //如果存在则删除后，返回新size，处理是否underflow
  int new_size = target_leaf->remove_record(key);
  if(new_size < target_leaf->min_size()){
    solve_underflow(target_leaf);
  }
}

template<typename T>
void BplusTree::solve_underflow(T* node){
  //如果是根结点需要调整(结点数量<2)
  if(!node->get_parent()){
    adjust_root();
    return;
  }
  //如果是一般的InterNode or LeafNode
  //左顾右盼，看是否有可借的元素(类似左旋右旋)
  //如果没有左兄弟，则看看右边
  InterNode* parent = static_cast<InterNode*>(node->get_parent());
  int position = parent->search_node_by_pointer(node);
  int neighbor_pos = (0 == position) ? 1 : position - 1;
  //拿到邻居结点
  T* neighbor = static_cast<T*>(parent->get_pos_node(neighbor_pos));
  //如果左右都不能借，和parent合并
  if(node->get_size() + neighbor->get_size() <= node->max_size()){
    merge(node, neighbor, parent, position);
  }else{
    redistribute(node, neighbor, parent, position);
  }
}

template<typename T>
void BplusTree::merge(T* node, T* neighbor, InterNode* parent, int position){
  //使用邻居的key，因为更小
  //把node的数据拷贝到neighbor，删除node，至此完成合并
  if(!position){
    swap(node, neighbor);
  }
  node->move_all_to(neighbor,position);
  parent->erase(position);
  delete node;
  //递归处理
  if(parent->get_size() < parent->min_size()){
    solve_underflow(parent);
  }
}

template<typename T>
void BplusTree::redistribute(T* node, T* neighbor, InterNode* parent, int position){
  //要看是从左边还是右边借
  //如果向右兄弟借，那么从它的第一个借到node的末尾
  //如果向左兄弟借，从它的最大值借到node的首部
  if(!position){
    neighbor->move_first_to_end_of(node);
  }else{
    neighbor->move_last_to_head_of(node,position);
  }
}







void BplusTree::adjust_root(){
  //如果只有InterNode且size为一，释放结点，把孩子结点作为新根
  if(!root_->is_leaf() && static_cast<InterNode*>(root_)->get_size() == 1){
    InterNode* old_root = static_cast<InterNode*>(root_);
    root_ = old_root->cut_first_child();
    delete old_root;
  }
  else if(!static_cast<InterNode*>(root_)->get_size()){
    delete root_;
    root_ = nullptr;
  }
}

Record* BplusTree::search(Key key){
  LeafNode* target_leaf = nullptr;
  Node* node = root_;
  while(!node->is_leaf()){
    InterNode* inter = static_cast<InterNode*>(node);
    node = inter->find(key);
  }
  target_leaf = static_cast<LeafNode*>(node);
  if(!target_leaf) return nullptr;
  //查找是否有对应Record
  Record* result = target_leaf->search(key);
  if(!result) return nullptr;
  return result;
}

