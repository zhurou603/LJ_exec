#ifndef INTERNODE_H
#define INTERNODE_H

#include"node.h"
#include"definition.h"
#include<vector>
#include<utility>
#include<cstdio>
#include<queue>
#include<iostream>

using namespace std;

//内部结点
class InterNode : public Node{
 public:
  using Pair  = pair<Key,Node*>;

  //构造函数
  InterNode(int d) : Node(d) {}
  InterNode(int d, Node* p) : Node(d, p) {}

  //可读接口
  bool is_leaf() const;
  int max_size() const;
  int min_size() const;
  Node* get_first_child() const;
  void print_all() const;

  //可写接口
  void append_element_to_vector(vector<Key>* result);
  void append_child_to_queue(queue<Node*>* q);
  //递归更新到root后，分裂后填充新的root
  void fill_new_root(Node* old_node, Key key, Node* new_node);
  //插入new节点到old的之后的位置,返回插入后的size
  int insert_after_old(Node* old_node, Key key, Node* new_node);
  //抽取最小的key
  Key replace_first_key();
  //移动后半部分到新的结点
  void move_half_to(InterNode* receiver);
  //拷贝后半部分
  void copy_half_from(const vector<Pair>& origin_keys);
  //顺序找到key
  Node* find(Key key);

 private:
  vector<Pair> keys_;

};

#endif