#include"leaf_node.h"

int  LeafNode::max_size() const{
    return degree_;
}

  int LeafNode::min_size() const {
    return (degree_+1)/2;
  }

int LeafNode::create_and_append(Key key, Value value){
  Record* check = search(key);
  if(!check){
    Record* new_record = new Record(value);
    //找到合适的位置插入为了保持有序。
    insert(key, new_record);
  }
  return leaves_.size();
}

Record* LeafNode::search(Key key){
  auto searching = leaves_.begin();
  while(searching != leaves_.end()){
    if(searching->first == key){
      return searching->second;
    }
    searching++;
  }
  return nullptr;
}

void LeafNode::insert(Key key, Record* record){
  //找到第一个大于key的位置插入
  auto searching = leaves_.begin();
  while(searching != leaves_.end() && searching->first < key) searching++;
  leaves_.insert(searching, Pair(key,record));
}

void LeafNode::set_next(LeafNode* node){
  next_ = node;
}

  //移动后半部分到新的结点
void LeafNode::move_half_to(LeafNode* receiver){
   receiver->copy_half_from(leaves_);
   int size = leaves_.size();
  for(int i = min_size(); i < size; i++){
    leaves_.pop_back();
  } 
}

//拷贝
void LeafNode::copy_half_from(const vector<Pair>& origin_keys){
  //先拷贝后半部分
  for(int i = min_size(); i < origin_keys.size(); i++){
    //移动前先把parent信息更改为接受者
    leaves_.push_back(origin_keys[i]);
  }
}

void LeafNode::printleaf() const {
  auto element = leaves_.begin();
  while(element != leaves_.end()){
    cout << "leaf key: " << element->first  <<  "leaf value:  " << element->second->get_value() << endl;
    element++;
  }
}

LeafNode* LeafNode::get_next() const{
  return next_;
}

Key LeafNode::first_key() const{
  return leaves_.begin()->first;
}