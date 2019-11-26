#ifndef BST_H
#define BST_H
#include"tree_node.h"
#include<vector>
#include<stack>
#include<iostream>

using namespace std;

template<typename T>
class BinarySearchTree{
 public:
	//构造
	BinarySearchTree();
	//析构
	~BinarySearchTree();
	//只读接口
	T max();
	T min();
	T lower_bound(const T& value);
	T upper_bound(const T& value);
	//可写接口
	void insert(const T& value);
	void erase(const T& value);
	void clear();
	//遍历
	vector<T> preorder();

 private:
	TreeNode<T>* root_;
	TreeNode<T>* insert(TreeNode<T>* node, const T& value);
	TreeNode<T>* erase(TreeNode<T>* node, const T& value);
	TreeNode<T>* lower_bound(TreeNode<T>* node, const T& value);
	TreeNode<T>* upper_bound(TreeNode<T>* node, const T& value);
	void postorder_clear(TreeNode<T>* node);
};

#endif

