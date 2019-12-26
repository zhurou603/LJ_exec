#include"bplustree.h"
#include<iostream>

using namespace std;

void BplusTree::insert(Key key, Value value){
  //如果一开始为空树，则加入一个叶子结点
  if(!root_){
    insert_empty_tree(key, value);
  }
	else{
    //找到对应叶子结点插入
    insert_to_leaf(key, value);
  }
	/*auto should_free = used.begin();
	while(should_free != used.end()){
		(*should_free)->free_space();
		should_free++;
	}
	used.clear();*/
}

void BplusTree::insert_empty_tree(Key key, Value value){

  //LeafNode* new_leaf = new LeafNode(tree_degree_);
	shared_ptr<DiskNode> new_leaf = make_shared<DiskNode>(tree_degree_);
	//used.insert(new_leaf);
  //向叶子结点添加一个记录
  new_leaf->create_and_append(key,value);
  //合理的转换，派生类的指针向基类指针
  root_ = new_leaf;
}

void BplusTree::insert_to_leaf(Key key, Value value){
  //先通过search找到对应叶子结点，再修改对应Record
  shared_ptr<DiskNode> find = nullptr;
  shared_ptr<Node> node = root_;
  while(!node->is_leaf()){
    //不是叶子结点时要找到internode中对应的值
    auto inter = static_pointer_cast<InterNode>(node);
    node = inter->find(key);
  }
  find = static_pointer_cast<DiskNode>(node);
	//used.insert(find);
  //在叶子结点找到对应record
  shared_ptr<Record> record = find->search(key);
  if(record){
    record->set(value);
    return;
  }
  //添加新纪录
  int new_size = find->create_and_append(key,value);
  //超过最大size则调整
  if(new_size > find->max_size()){
    //split返回新产生的结点
    shared_ptr<DiskNode> new_leaf = split(find);
		used.insert(new_leaf);
    //建立链表关系
    new_leaf->set_next(find->get_next());
    find->set_next(new_leaf);
    //向上递归更新key
    Key new_first = new_leaf->first_key();
    insert_key_to_parent(find, new_first, new_leaf);
  }
}

template<typename T>
shared_ptr<T> BplusTree::split(shared_ptr<T> node){
  //传递parent关系
  shared_ptr<T> new_node = make_shared<T>(tree_degree_, node->get_parent());
  //拷贝
  node->move_half_to(new_node);
  return new_node;
}

void BplusTree::insert_key_to_parent(shared_ptr<Node> old_node, Key key, shared_ptr<Node> new_node){
  //先获取parent结点
  shared_ptr<InterNode> parent = static_pointer_cast<InterNode>(old_node->get_parent());
  //根结点没有父结点
  if(!parent){
    //创建新的根结点
    root_ = make_shared<InterNode>(tree_degree_);
    parent = static_pointer_cast<InterNode>(root_);
    old_node->set_parent(parent);
    new_node->set_parent(parent);
    //填充新的根
    parent->fill_new_root(static_pointer_cast<InterNode>(old_node), key, static_pointer_cast<InterNode>(new_node));
  }else{
    //如果还没更新到根结点,插入key到parent结点中old_node之后的位置
    int new_size = parent->insert_after_old(old_node, key, new_node);
    //B+树如果degree为3，包含dummy key应该要4才split
    if(new_size-1 > parent->max_size()){
      shared_ptr<InterNode> after_split = split(parent);
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
    node = static_pointer_cast<InterNode>(node)->get_first_child();
  }
  shared_ptr<LeafNode> leaf = static_pointer_cast<LeafNode>(node);
  while(leaf){
    leaf->printleaf();
    leaf = leaf->get_next();
    cout << "一组结束" << endl;
  }
}

void BplusTree::bfs_key(vector<Key>* result){
  shared_ptr<Node> node = root_;
  queue<shared_ptr<Node>> nodes;
  nodes.push(node);
  while(!nodes.empty() && !nodes.front()->is_leaf()){
    node = nodes.front();
    shared_ptr<InterNode> inter = static_pointer_cast<InterNode>(node);
    inter->append_element_to_vector(result);
    nodes.pop();
    //遍历孩子
    inter->append_child_to_queue(&nodes);
  }
}

shared_ptr<Record> BplusTree::search(Key key){
  shared_ptr<LeafNode> target_leaf = nullptr;
  shared_ptr<Node> node = root_;
  while(!node->is_leaf()){
    shared_ptr<InterNode> inter = static_pointer_cast<InterNode>(node);
    node = inter->find(key);
  }
  target_leaf = static_pointer_cast<LeafNode>(node);
  if(!target_leaf) return nullptr;
  //查找是否有对应Record
  shared_ptr<Record> result = target_leaf->search(key);
  if(!result) return nullptr;
  return result;
}

