#include"bst.h"

//构造,初始化根结点
template<typename T>
BinarySearchTree<T>::BinarySearchTree(){
	root_ = nullptr;
}

//析构，清空所有结点后析构
template<typename T>
BinarySearchTree<T>::~BinarySearchTree(){	
	clear();
}

//clear,递归后序遍历bottom-up删除结点
template<typename T>
void BinarySearchTree<T>::clear(){
	postorder_clear(root_);
}

template<typename T>
void BinarySearchTree<T>::postorder_clear(TreeNode<T>* node){
	if(node){	
		if(node->left) postorder_clear(node->left);
		if(node->right) postorder_clear(node->right);
		delete node;
	}
}

//插入以value为值的结点
template<typename T>
void BinarySearchTree<T>::insert(const T& value){
	root_ = insert(root_, value);
}

template<typename T>
TreeNode<T>* BinarySearchTree<T>::insert(TreeNode<T>* node, const T& value){
	//若没有找到值为value的结点则创造根结点返回	
	if(!node){
		return (new TreeNode<T>(value));
	}
	//search value的位置
	if(node->val > value){
		node->left = insert(node->left, value);
	}
	else if(node->val < value){
		node->right = insert(node->right, value);
	}
	//如果已经存在则更新
	else{
		node->val = value;	
	}
	return node;
}

//删除,删除以value为值的结点
template<typename T>
void BinarySearchTree<T>::erase(const T& value){
	root_ = erase(root_, value);
}

template<typename T>
TreeNode<T>* BinarySearchTree<T>::erase(TreeNode<T>* node, const T& value){
	if(!node) return nullptr;	
	//search
	if(node->val > value){
		node->left = erase(node->left, value);
	}
	else if(node->val < value){
		node->right = erase(node->right, value);
	}
	//若找到删除结点
	else{
		TreeNode<T>* del_node = node;
		//0 or 1 child
		if(!node->left)return node->right;
		if(!node->right) return node->left;
		//2 children
		TreeNode<T>* current = node;
		//find right mininum
		TreeNode<T>* right_min = current->right;
		while(right_min->left){
			right_min = right_min->left;	
		}
		node = right_min;
		//更新左右子树
		node->right = erase(current->right, right_min->val);
		node->left = current->left;
		delete del_node; 
	}
	return node;
}

//BST中最大值,树中最右值
template<typename T>
T BinarySearchTree<T>::max(){
	if(!root_) throw "without max because tree is empty";
	TreeNode<T>* find_max = root_;
	while(find_max->right){
		find_max = find_max->right;
	}
	return find_max->val;
}

//BST中最小值,树中最左值
template<typename T>
T BinarySearchTree<T>::min(){	
	if(!root_) throw "without min because tree is empty";
	TreeNode<T>* find_min = root_;
	while(find_min->left){
		find_min = find_min->left;
	}
	return find_min->val;
}

//lower_bound,第一个大于等于value结点的值
template<typename T>
T BinarySearchTree<T>::lower_bound(const T& value){
	TreeNode<T>* tree_root = root_;
	TreeNode<T>* result = lower_bound(tree_root, value);
	if(!result) throw "所有结点均小于value";
	return result->val;
}

template<typename T>
TreeNode<T>* BinarySearchTree<T>::lower_bound(TreeNode<T>* node, const T& value){
	if(!node) return nullptr;
	if(node->val == value) return node;
	//如果该结点的值小于value，那么向右搜索
	if(node->val < value) return lower_bound(node->right, value);
	//为第一个比value大的子树的根,有可能是答案,因此要找该树左边check
	TreeNode<T>* check = lower_bound(node->left, value);
	if(!check) return node;
	return check;
}

//upper_bound,第一个大于等于value结点的值
template<typename T>
T BinarySearchTree<T>::upper_bound(const T& value){
	TreeNode<T>* tree_root = root_;
	TreeNode<T>* result = upper_bound(tree_root, value);
	if(!result) throw "所有结点均小于等于value";
	return result->val;
}

template<typename T>
TreeNode<T>* BinarySearchTree<T>::upper_bound(TreeNode<T>* node, const T& value){
	if(!node) return nullptr;
	//如果该结点的值小于value，那么向右搜索
	if(node->val <= value) return upper_bound(node->right, value);
	//为第一个比value大的子树的根,有可能是答案,因此要找该树左边check
	TreeNode<T>* check = upper_bound(node->left, value);
	if(!check) return node;
	return check;
}

//前序遍历，用于test
template<typename T>
vector<T> BinarySearchTree<T>::preorder(){
	vector<T> data;
	if(!root_) return data;	
	stack<TreeNode<T>*> pre;
	TreeNode<T>* current = root_;
	while(current || !pre.empty()){
		while(current){
			data.push_back(current->val);
			pre.push(current);
			current = current->left;
		}
		current = pre.top();
		pre.pop();
		current = current->right;
	}
	return data;
}

template class BinarySearchTree<int>;
