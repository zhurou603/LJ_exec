#ifndef BPLUSTREE_H
#define BPLUSTREE_H

#include"definition.h"
#include"node.h"
#include"leaf_node.h"
#include"inter_node.h"
#include<queue>

const int DEFAULT_DEGREE = 3;

class BplusTree{
 public:
  //构造函数
  BplusTree(int d = DEFAULT_DEGREE) : tree_degree_(d), root_(nullptr) {}

  //外部接口
  void insert(Key key, Value value);
  void remove(Key key);
  Record* search(Key key);

  //遍历
  void print_all();
  //BFS
  void bfs_key(vector<Key>* result);

 private:
  //空树增加一个结点
  void insert_empty_tree(Key key, Value value);
  //插入到叶子结点
  void insert_to_leaf(Key key, Value value);
  //split
  template <typename T>
  T* split(T* node);
  //叶子结点split后把key更新到parent
  void insert_key_to_parent(Node* old_node, Key key, Node* new_node);

  //删除对应叶子结点的记录
  void remove_leaf(Key key);
  //处理下溢
  template<typename T>
  void solve_underflow(T* node);
  //根结点vector的size小于等于1
  void adjust_root();
  
  //合并
  template<typename T>
  void merge(T* node, T* neighbor, InterNode* parent, int position);
  //旋转
  template<typename T>
  void redistribute(T* node, T* neighbor, InterNode* parent, int position);

  int tree_degree_;
  Node* root_;

};

#endif