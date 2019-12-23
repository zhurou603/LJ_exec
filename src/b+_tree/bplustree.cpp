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