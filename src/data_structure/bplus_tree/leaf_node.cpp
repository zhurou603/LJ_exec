#include"leaf_node.h"

int LeafNode::max_size() const{
  return get_degree() - 1;
}

void LeafNode::insert(KeyType key, Record* record){
  auto insert_position = leaf_nodes.begin();
  //第一条大于等于
  while(insert_position != leaf_nodes.end() && insert_position->first < key){
    insert_position++;
  } 
  leaf_nodes.insert(insert_position, LeafType(key, record));
}

int LeafNode::create_record_insert(KeyType key, ValueType value){
  //生成一条记录
  Record* new_record = new Record(value);
  //找到第一个大于等于的记录，暂时用线性查找
  insert(key, new_record);
  //返回插入后size
  return leaf_nodes.size();
}

//查找是否有对应记录
Record* LeafNode::search_record(KeyType key) const{
  auto finding_record = leaf_nodes.begin();
  while(finding_record != leaf_nodes.end()){
    if(key == finding_record->first){
      return finding_record->second;
    }
    finding_record++;
  }
  return nullptr;
}