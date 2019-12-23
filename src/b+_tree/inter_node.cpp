#include"inter_node.h"

bool InterNode::is_leaf() const {
  return false;
}

  int  InterNode::max_size() const { 
    return degree_;
  }

int InterNode::min_size() const{
  //注意向上取整
  return (degree_ + 1) / 2;
}

Node*  InterNode::get_first_child() const{
  return keys_.begin()->second;
}

  void InterNode::print_all() const{
    auto t = keys_.begin();
    while(t != keys_.end()){
      cout << "key :" << t->first << endl;
      t++;
    }
  }

Node* InterNode::find(Key key){
  auto finding = keys_.begin();
  //找到最后一个大于等于容器内的值
  while(finding != keys_.end() && key >= finding->first) finding++;
  finding--;
  return finding->second;
}

void InterNode::fill_new_root(Node* old_node, Key key, Node* new_node){
  keys_.push_back(make_pair(DUMMY_KEY, old_node));
  keys_.push_back(make_pair(key, new_node));
}

int InterNode::insert_after_old(Node* old_node, Key key, Node* new_node){
  auto finding = keys_.begin();
  while(finding != keys_.end() && finding->second != old_node) finding++;
  keys_.insert(finding+1, make_pair(key, new_node));
  return keys_.size();
}

void InterNode::move_half_to(InterNode* receiver){
  //先拷贝，后删除
  receiver->copy_half_from(keys_);
  int size = keys_.size();
  for(int i = min_size()+1; i < size; i++){
    keys_.pop_back();
  }
}

void InterNode::copy_half_from(const vector<Pair>& origin_keys){
  //先拷贝后半部分
  for(int i = min_size()+1; i < origin_keys.size(); i++){
    //移动前先把parent信息更改为接受者
    origin_keys[i].second->set_parent(this);
    keys_.push_back(origin_keys[i]);
  }
}

//向result添加key用于遍历
void InterNode::append_element_to_vector(vector<Key>* result){
  auto t = keys_.begin();
  while(t != keys_.end()){
    result->push_back(t->first);
    t++;
  }
}

void InterNode::append_child_to_queue(queue<Node*>* q){
  auto t = keys_.begin();
  while(t != keys_.end()){
    q->push(t->second);
    t++;
  }
}

Key InterNode::replace_first_key(){
  Key new_key = keys_.begin()->first;
  keys_.begin()->first = DUMMY_KEY;
  return new_key;
}

int InterNode::get_size() const{
  return keys_.size();
}

Node* InterNode::cut_first_child(){
  Node* first = get_first_child();
  keys_.pop_back();
  return first;
}

int InterNode::search_node_by_pointer(Node* node){
  for(int i = 0; i < keys_.size(); i++){
    if(keys_[i].second == node) return i;
  }
  return -1;
}

Node* InterNode::get_pos_node(int pos){
  return keys_[pos].second;
}

Key InterNode::get_pos_key(int pos){
  return keys_[pos].first;
}

void InterNode::move_all_to(InterNode* receiver, int pos){
  //更改dummy为合并后的key
  keys_.begin()->first = static_cast<InterNode*>(get_parent())->get_pos_key(pos);
  //copy
  receiver->copy_all_from(&keys_);
  keys_.clear();
}

void InterNode::copy_all_from(vector<Pair>* data){
  for(int i = 0; i < (*data).size(); i++){
    (*data)[i].second->set_parent(this);
    keys_.push_back((*data)[i]);
  }
}

void InterNode::erase(int pos){
  keys_.erase(keys_.begin() + pos);
}

void InterNode::move_first_to_end_of(InterNode* node){
  node->copy_first_from(keys_.front());
  keys_.erase(keys_.begin());
  //删除后需要更新上一层的key
  static_cast<InterNode*>(parent_)->set_key_pos(1, keys_.front().first); 
}

Key InterNode::first_key() const{
  return keys_[1].first;
}

void InterNode::copy_first_from(Pair first){
  keys_.push_back(first);
  //转移key
  keys_.back().first = keys_.back().second->first_key();
  keys_.back().second->set_parent(this);
}

void InterNode::set_key_pos(int pos, Key key){
  keys_[pos].first = key;
}

void InterNode::move_last_to_head_of(InterNode* node, int node_pos){
  node->copy_last_from(keys_.back(),node_pos);
  keys_.pop_back();
}

void InterNode::copy_last_from(Pair last, int node_pos){
    keys_.front().first = static_cast<InterNode*>(parent_)->get_pos_key(node_pos);
    keys_.insert(keys_.begin(), last);
    keys_.front().first = DUMMY_KEY;
    keys_.front().second->set_parent(this);
    static_cast<InterNode*>(parent_)->set_key_pos(node_pos, keys_.front().first);
}