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
	BinarySearchTree() : root_(nullptr) {};
	//析构
	virtual ~BinarySearchTree();
	//只读接口
	T max() const;
	T min() const;
	T lower_bound(const T& value) const;
	T upper_bound(const T& value) const;
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
	TreeNode<T>* lower_bound(TreeNode<T>* node, const T& value) const;
	TreeNode<T>* upper_bound(TreeNode<T>* node, const T& value) const;
	void postorder_clear(TreeNode<T>* node);
};

#endif

