#include"rbtree.h"
#include<gtest/gtest.h>

using namespace std;

//析构，清空所有结点后析构
template<typename T>
Rbtree<T>::~Rbtree(){	
	clear();
}

//从这里开始为可读接口实现
//最小值
template<typename T>
T Rbtree<T>::min() const{
	if(!root_) throw "without min because tree is empty";
	TreeNode<T>* find_min = root_;
	while(find_min->left){
		find_min = find_min->left;
	}
	return find_min->val;
}

//最大值
template<typename T>
T Rbtree<T>::max() const{
	if(!root_) throw "without max because tree is empty";
	TreeNode<T>* find_max = root_;
	while(find_max->right){
		find_max = find_max->right;
	}
	return find_max->val;
}

//第一个大于等于元素
template<typename T>
T Rbtree<T>::lower_bound(const T& value) const{
	TreeNode<T>* tree_root = root_;
	TreeNode<T>* result = lower_bound(tree_root, value);
	if(!result) throw "所有结点均小于value";
	return result->val;
}

template<typename T>
TreeNode<T>* Rbtree<T>::lower_bound(TreeNode<T>* node, const T& value) const{
	if(!node) return nullptr;
	if(node->val == value) return node;
	//如果该结点的值小于value，那么向右搜索
	if(node->val < value) return lower_bound(node->right, value);
	//为第一个比value大的子树的根,有可能是答案,因此要找该树左边check
	TreeNode<T>* check = lower_bound(node->left, value);
	if(!check) return node;
	return check;
}

//第一个大于的元素
template<typename T>
T Rbtree<T>::upper_bound(const T& value) const{
	TreeNode<T>* tree_root = root_;
	TreeNode<T>* result = upper_bound(tree_root, value);
	if(!result) throw "所有结点均小于等于value";
	return result->val;
}

template<typename T>
TreeNode<T>* Rbtree<T>::upper_bound(TreeNode<T>* node, const T& value) const{
	if(!node) return nullptr;
	//如果该结点的值小于value，那么向右搜索
	if(node->val <= value) return upper_bound(node->right, value);
	//为第一个比value大的子树的根,有可能是答案,因此要找该树左边check
	TreeNode<T>* check = upper_bound(node->left, value);
	if(!check) return node;
	return check;
}

//递归前序遍历
template<typename T>
vector<T> Rbtree<T>::preorder(){
	vector<T> data;  
	preorder(root_,&data);
	return data;
}

template<typename T>
void Rbtree<T>::preorder(TreeNode<T>* root, vector<T>* data){
  if(!root) return;
	data->push_back(root->val);
  preorder(root->left,data);
  preorder(root->right,data);
}

//从这里开始为可写接口

//插入
template<typename T>
void Rbtree<T>::insert(const T& value){
  TreeNode<T>* node = root_;
  root_ = insert(node, value);
	//插入后要保持root_黑色
  root_->color = BLACK;
}

template<typename T>
TreeNode<T>* Rbtree<T>::insert(TreeNode<T>* node, const T& value){
  if(!node) return new TreeNode<T>(value);
  //BST递归插入
  if(node->val > value){
    node->left = insert(node->left, value);
  }
  else if(node->val < value){
    node->right = insert(node->right, value);
  }else{
    node->val = value;
  }
	//红黑树balance
  node = rebalance(node);
  return node;
}

//删除
template<typename T>
void Rbtree<T>::erase(const T& value){
  TreeNode<T>* node = root_;
  root_ = erase(node, value);
  root_->color = BLACK;
}

template<typename T>
TreeNode<T>* Rbtree<T>::erase(TreeNode<T>* node, const T& value){
  if(!node) return node;
  //如果删除的结点在左侧
  if(node->val > value){
    //左边连续两条黑边则需要传递红色边
    if(node->left && !is_red(node->left) && !is_red(node->left->left)){
      node = move_red_left(node);
    }
    node->left = erase(node->left, value);
  }else{
		//如果删除结点找到或在右侧
		//如果是left-leaning则需要转为right-leaning方便传递红色边
    if(is_red(node->left)){
      node = right_rotation(node);
    }
		//如果到bottom直接删除
    if((node->val == value) && !node->right){
			delete node;
      return nullptr;
    }
		//如果右边需要传递红色边
    if(node->right && !is_red(node->right) && !is_red(node->right->left)){
      node = move_red_right(node);
    }
    //regular bst erase
    if(node->val == value){
			TreeNode<T>* search_min = node->right;
			while(search_min->left){
				search_min = search_min->left;	
			}
      T right_minium = search_min->val;
      node->val = right_minium;
      node->right = erase(node->right, right_minium);
    }else{
      node->right = erase(node->right, value);
    }
  }
	//红黑树平衡
  node = rebalance(node);
  return node;
}

//clear,递归后序遍历bottom-up删除结点
template<typename T>
void Rbtree<T>::clear(){
	postorder_clear(root_);
}

template<typename T>
void Rbtree<T>::postorder_clear(TreeNode<T>* node){
	if(node){	
		if(node->left) postorder_clear(node->left);
		if(node->right) postorder_clear(node->right);
		delete node;
	}
}

//辅助函数
template<typename T>
TreeNode<T>* Rbtree<T>::left_rotation(TreeNode<T>* node){
  TreeNode<T>* target = node->right;
  node->right = target->left;
  target->left = node;
  //颜色交换
  target->color = node->color;
  node->color = RED;
  return target;
}

template<typename T>
TreeNode<T>* Rbtree<T>::right_rotation(TreeNode<T>* node){
  TreeNode<T>* target = node->left;
  node->left = target->right;
  target->right = node;
  //颜色交换
  target->color = node->color;
  node->color = RED;
  return target;
}

template<typename T>
TreeNode<T>* Rbtree<T>::flip(TreeNode<T>* node){
	//根左右孩子均上反色
  node->color = !node->color;
  node->left->color = !node->left->color;
  node->right->color = !node->right->color;
  return node;
}

template<typename T>
bool Rbtree<T>::is_red(TreeNode<T>* node) const{
	//空结点是黑色
  if(!node) return BLACK;
  return node->color;
}

template<typename T>
TreeNode<T>* Rbtree<T>::move_red_left(TreeNode<T>* node){
  node = flip(node);
  if(node->right && is_red(node->right->left)){
    node->right = right_rotation(node->right);
  }
  node = left_rotation(node);
  node = flip(node);
  return node;
}

template<typename T>
TreeNode<T>* Rbtree<T>::move_red_right(TreeNode<T>* node){
  node = flip(node);
  if(node->left && is_red(node->left->right)){
    node->left  = left_rotation(node->left);
  }
  node = right_rotation(node);
  node = flip(node);
  return node;
}

template<typename T>
TreeNode<T>* Rbtree<T>::rebalance(TreeNode<T>* node){
	//所有情况最终目的均为解决C问题，A执行后可转化为B情况B执行后可以转化为C情况	
	//A:if node right-leaning  
	if(is_red(node->right) && !is_red(node->left)){
    node = left_rotation(node);
  }
  //B:if node has a temp 4-node situation
  if(node->left && is_red(node->left) && is_red(node->left->left)){
    node = right_rotation(node);
  }
  //C:flip temp 4-node
  if(is_red(node->left) && is_red(node->right)){
    node = flip(node);
  }
  return node;
}

template class Rbtree<int>;
