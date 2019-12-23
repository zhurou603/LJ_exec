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