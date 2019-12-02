#ifndef RBTREE_H
#define RBTREE_H
#include"tree_node.h"
#include<iostream>
#include<vector>

using namespace std;

//Left-leaning Red Black BST
//其中：min,max,lower_bound,upper_bound和BST一样，因为红黑树也符合bst性质
template<typename T>
class Rbtree{
 public:
	//构造
  Rbtree() : root_(nullptr) {};
	//析构
  virtual ~Rbtree();
  //只读
  T min() const;
  T max() const;
  T lower_bound(const T& value) const;
  T upper_bound(const T& value) const;
  vector<T> preorder();
  //可写
  void insert(const T& value);
  void erase(const T& value);
  void clear();

 private:
  TreeNode<T>* root_;
	//以下为辅助函数
  TreeNode<T>* left_rotation(TreeNode<T>* node);
  TreeNode<T>* right_rotation(TreeNode<T>* node);
  TreeNode<T>* flip(TreeNode<T>* node);
  bool is_red(TreeNode<T>* node) const;
	TreeNode<T>* move_red_left(TreeNode<T>* node);
	TreeNode<T>* move_red_right(TreeNode<T>* node);
	TreeNode<T>* rebalance(TreeNode<T>* node);
	//以下为递归接口
	TreeNode<T>* lower_bound(TreeNode<T>* node, const T& value) const;
	TreeNode<T>* upper_bound(TreeNode<T>* node, const T& value) const;
  void preorder(TreeNode<T>* root, vector<T>* data);
  TreeNode<T>* insert(TreeNode<T>* node, const T& value);
  TreeNode<T>* erase(TreeNode<T>* node, const T& value);
	void postorder_clear(TreeNode<T>* node);
};

#endif
