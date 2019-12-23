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
  int get_size() const;

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
  //当root的size为1时，删除与孩子结点的连接并返回孩子结点
  Node* cut_first_child();
  //根据Node*找位置
  int search_node_by_pointer(Node* node);
  //根据index取元素
  Node* get_pos_node(int pos);
  //根据index取key
  Key get_pos_key(int pos);

  //转移所有数据到receiver
  void move_all_to(InterNode* receiver, int pos);
  //从指定keys拷贝数据
  void copy_all_from(vector<Pair>* data);
  //删除指定pos元素
  void erase(int pos);
  void move_first_to_end_of(InterNode* node);
  void move_last_to_head_of(InterNode* node);
  void copy_first_from(Pair first);
  Key first_key() const;
  void set_key_pos(int pos, Key key);
  void copy_last_from(Pair last);
  void copy_last_from(Pair last, int node_pos);
  void move_last_to_head_of(InterNode* node, int node_pos);
  

 private:
  vector<Pair> keys_;

};

#endif