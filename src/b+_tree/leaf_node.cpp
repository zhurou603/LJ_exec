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

int LeafNode::remove_record(Key key){
  //先找到Record,从vector中删除，然后释放
  auto target = leaves_.begin();
  while(target != leaves_.end() && target->first != key) target++;
  Record* target_record = target->second;
  leaves_.erase(target);
  delete target_record;
  return leaves_.size();
}

int LeafNode::get_size() const{
  return leaves_.size();
}

void LeafNode::move_all_to(LeafNode* receiver, int pos){
  receiver->copy_all_from(&leaves_);
  leaves_.clear();
  receiver->set_next(next_);
}

void LeafNode::copy_all_from(vector<Pair>* data){
  for(int i = 0; i < (*data).size(); i++){
    leaves_.push_back((*data)[i]);
  }
}

void LeafNode::move_first_to_end_of(LeafNode* node){
  node->copy_first_from(leaves_.front());
  leaves_.erase(leaves_.begin());
  //删除后需要更新上一层的key
  static_cast<LeafNode*>(parent_)->set_key_pos(1, leaves_.front().first); 
}

void LeafNode::copy_first_from(Pair first){
  leaves_.push_back(first);
}

void LeafNode::set_key_pos(int pos, Key key){
  leaves_[pos].first = key;
}

void LeafNode::move_last_to_head_of(LeafNode* node, int node_pos){
  node->copy_last_from(leaves_.back(),node_pos);
  leaves_.pop_back();
}

void LeafNode::copy_last_from(Pair last, int node_pos){
    leaves_.insert(leaves_.begin(), last);
    static_cast<LeafNode*>(parent_)->set_key_pos(node_pos, leaves_.front().first);
}