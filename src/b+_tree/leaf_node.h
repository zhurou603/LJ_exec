#ifndef LEAF_NODE_H
#define LEAF_NODE_H

#include"definition.h"
#include"node.h"
#include<vector>
#include<utility>
#include"record.h"
#include<iostream>
#include"inter_node.h"

using namespace std;

//叶结点
class LeafNode : public Node {
 public:
  //vector存储的Key和实际的记录Record
  using Pair = pair<Key,Record*>;
  //构造函数
  LeafNode(int d) : Node(d), next_(nullptr) {}
  LeafNode(int d, Node* p) : Node(d, p), next_(nullptr) {}

  //可读接口
  bool is_leaf() const{
    return true;
  }
  //查找为key的记录是否存在
  Record* search(Key key);
  //返回最大容量
  int max_size() const;
  //返回最小容量
  int min_size() const;
  //打印叶子结点
  void printleaf() const;
  //获取next结点
    LeafNode* get_next() const;
  //拿到第一个元素，方便split
  Key first_key() const;

  //可写接口
  //向leaves创建记录并添加,返回当前size以便调整
  int create_and_append(Key key, Value value);
  //在合适的位置插入一个pair
  void insert(Key key, Record* record);
  //类似链表下一指针
  void set_next(LeafNode* node);
  //移动后半部分到新的结点
  void move_half_to(LeafNode* receiver);
  //拷贝
  void copy_half_from(const vector<Pair>& origin_keys);

 private:
  vector<Pair> leaves_;
  //底层链表结构
  LeafNode* next_;
};

#endif