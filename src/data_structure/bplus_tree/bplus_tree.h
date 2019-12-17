#ifndef BPULS_TREE_H
#define BPLUS_TREE_H

#include"definition.h"
#include"basic_node.h"
#include"internal_node.h"
#include"leaf_node.h"

class BplusTree{
 public:
  //构造函数，需要指定max_degree
  BplusTree(int degree = DEFAULT_DEGREE) : tree_degree_(degree), root_(nullptr){};
  //插入接口
  void insert(KeyType key, ValueType value);
  //查找是否存在
  bool find(KeyType key);
  //删除
  void erase(KeyType key);

 private:
  //递归插入
  void insert(KeyType key, ValueType value, BasicNode* root);
  void build_new_tree(KeyType key, ValueType value);
  //插入到叶子结点
  void insert_to_leaf(KeyType key, ValueType value);
  //找到对应叶子结点
  LeafNode* find_leaf(KeyType key);
  //B+树的degree
  int tree_degree_;
  //维护根结点
  BasicNode* root_;
};


#endif