#include"avl.h"

using namespace std;

//比较两值大小
int max(int a, int b){
	return (a > b) ?a :b;
}

//创建一个新结点
Node* newNode(int64_t key){
	Node* node = new Node(key);
	return node;
}

//获取结点高度
int getHeight(Node* n){
	if(n == NULL) return 0;
	return n->height;
}

//获取以该结点为根的子树的结点数目 
int getCount(Node* n){
	if(n == NULL) return 0;
	int sum = 1;
	sum += getCount(n->left) + getCount(n->right);
	return sum;
}

//右旋
Node* rightRotate(Node* y){
	Node* x = y->left;
	Node* T2 = x->right;
	//右旋操作
	x->right = y;
	y->left = T2;
	//更新高度
	y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
	x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
	y->count = getCount(y);
	x->count = getCount(x);	
	return x;
}

//左旋
Node*	leftRotate(Node* x){
	Node* y = x->right;
	Node* T2 = y->left;
	//左旋操作
	y->left = x;
	x->right = T2;
	//更新高度
	y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
	x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
	y->count = getCount(y);
	x->count = getCount(x);
	return y;
}

//获取平衡因子
int getBalance(Node* n){
	if(n == NULL) return 0;
	return (getHeight(n->left) - getHeight(n->right));
}

//前序遍历，用于检验操作
void preOrder(Node* root, vector<int64_t>& result){
	if(root != NULL){
		result.push_back(root->key);
		preOrder(root->left, result);
		preOrder(root->right, result);
	}
}

//寻找以node为根子树的最小结点
Node* minValueNode(Node* node){
	Node* current = node;
	while(current->left != nullptr) current = current->left;
	return current;
}

//插入
Node* insert(Node* node, int64_t key){
	//通常ＢＳＴ插入
	if(node == NULL) return newNode(key);
	if(key < node->key){
		node->left = insert(node->left, key);
	}
	else if(key >node->key){
		node->right = insert(node->right, key);
	}else{
		return node;
	}
	//以下为AVL调整平衡
	//更新高度
	node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
	node->count = getCount(node);
	
	int balance = getBalance(node);

	//left left case
	if(balance > 1 && key < node->left->key){
		return rightRotate(node);
	}
	//right right case
	if(balance < -1 && key > node->right->key){
		return leftRotate(node);
	}
	//right left case
	if(balance < -1 && key < node->right->key){
		node->right = rightRotate(node->right);
		return leftRotate(node);
	}
	if(balance > 1 && key > node->left->key){
		node->left = leftRotate(node->left);
		return rightRotate(node);	
	}
	return node;
}

//删除结点
Node* deleteNode(Node* root, int64_t key){
	//先进行BST通常删除操作
	if(root == nullptr) return root;
	
	//search
	if(root->key > key){
		root->left = deleteNode(root->left, key);	
	}
	else if(root->key < key){
		root->right = deleteNode(root->right, key);
	}
	else{
		if(root->left == nullptr || root->right == nullptr){
			Node* temp = root->left ? root->left : root->right;
			if(temp == nullptr){
					root = nullptr;			
			}else{
				*root = *temp;
				free(temp);
			}	
		}
		else{
			Node* temp = minValueNode(root->right);
			root->key = temp->key;
			root->right = deleteNode(root->right, temp->key);		
		}
	}
	if(root == nullptr) return nullptr;

	//调整
	root->height = max(getHeight(root->left), getHeight(root->right)) + 1;
	root->count = getCount(root);

	int balance = getBalance(root);
	//ll
	if(balance > 1 && getBalance(root->left) >= 0){
		return rightRotate(root);
	}
	//lr
	if(balance > 1 && getBalance(root->left) < 0){
		root->left = leftRotate(root->left);
		return rightRotate(root);
	}
	//rr
	if(balance < -1 && getBalance(root->right) <= 0){
		return leftRotate(root); 
	}
	//rl
	if(balance < -1 && getBalance(root->right) > 0){
		root->right = rightRotate(root->right);
		return leftRotate(root);
	}
	return root;		
}

//返回第k大元素
int64_t select(Node* root, int k){
	if(root == NULL) return -1;
	if(root->count == 1) return root->key;
	int rank = root->left->count + 1;
	if(k == rank){
		return root->key;
	}
	else if(k < rank){
		return select(root->left, k);
	}
	else{
		return select(root->right, k - rank);
	}
}


//返回AVL的中位数中位数
//时间复杂度O(logn)
double getMedian(Node* root){
	//树总共元素数量为root的count
	int n = root->count;
	//若元素数量为奇数，则为 ceil(n/2)th element
	//若元素数量为偶数，则为 (n/2)th element 与 (n/2 + 1)th element的平均值
	if((n % 2) != 0){
		return select(root, ceil((double)n / 2));
	}else{
		return ((double)select(root, n/2) + select(root, n/2 + 1)) / 2;
	}
}



