#include"bplus_tree.h"

//插入部分
void BplusTree::insert(KeyType key, ValueType value){
  insert(key, value, root_);
}

void BplusTree::insert(KeyType key, ValueType value, BasicNode* root){
  //如果树是空的那么建立新结点返回;
  if(!root){
    //构造指定degree,key,value的根(同时也是叶子)结点
    build_new_tree(key, value);
    return;
  }
  //把key,value插入到对应叶子结点
  //insert_to_leaf(key, value);
}

void BplusTree::build_new_tree(KeyType key, ValueType value){
  //建立一个叶子结点
  //并且把这个value添加到记录
  LeafNode* new_leaf_node = new LeafNode(tree_degree_);
  new_leaf_node->create_record_insert(key,value);
  root_ =  new_leaf_node;
}

void BplusTree::insert_to_leaf(KeyType key, ValueType value){
  //要找到对应的位置
  LeafNode* leaf = find_leaf(key);
  if(!leaf){
    throw "没有找到可以插入的叶子结点";
  }
  //看是否有对应记录，有则更新，没有则找到对应位置插入
  Record* record = leaf->search_record(key);
  if(record){
    record->set_value(value);
    return;
  }
  //插入并查看容量
  int after_size = leaf->create_record_insert(key, value);
  //如果大于max_degree 调整
  
}

LeafNode* BplusTree::find_leaf(KeyType key){
  //如果树空无法查找
  if(!root_) return nullptr;
  auto finding = root_;
  while(!finding->is_leaf()){
    auto internal = static_cast<InternalNode*>(finding);
    finding = internal->search_for_last_lessequal(key);
  }
  return static_cast<LeafNode*>(finding);
}


