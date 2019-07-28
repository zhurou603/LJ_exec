#include<algorithm>
#include<iostream>

using namespace std;

//AVL结点
struct Node{
	int64_t key;
	Node* left;
	Node* right;
	int height;
	//以此根为节点子树结点总和
	int count;
	Node(int64_t k) : key(k), left(NULL), right(NULL), height(1), count(1){}
};

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
	return y;
}

//获取平衡因子
int getBalance(Node* n){
	if(n == NULL) return 0;
	return (getHeight(n->left) - getHeight(n->right));
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

//寻找以node为根子树的最小结点
Node* minValueNode(Node* node){
	Node* current = node;
	while(current->left != nullptr) current = current->left;
	return current;
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

//中位数,未完成
double getMedian(Node* root){
	int leftcount = getCount(root->left);
	int rightcount = getCount(root->right);
	if(leftcount == rightcount){
		return root->key;
	}else{
		bool flag = leftcount  rightcount;
		Node* tmp;
		if(flag){
			tmp = root->left;
			while(tmp->right != NULL) tmp = tmp->right;
		}else{
			tmp = root->right;
			while(tmp->right != NULL) tmp = tmp->left;
		}
		return (double)(root->key + tmp->key) / 2.0;
	}
}

//前序遍历，用于检验操作
void preOrder(Node* root){
	if(root != NULL){
		cout << root->key << " ";
		preOrder(root->left);
		preOrder(root->right);
	}
}

int main(){
	Node* root = NULL;
	int64_t data[8] = {1,2,3,4,5,6};
	for(int i = 0; i < 6; i++){
		root = insert(root,data[i]);
	}
	preOrder(root);
	double even = getMedian(root);
	cout << "even double :" << even << endl;

	cout << "----------------" << endl;
	root = deleteNode(root, 6);
	preOrder(root);
	double odd = getMedian(root);
	cout << "odd double :" << even << endl;

	root = deleteNode(root, 5);
	preOrder(root);
	return 0;
}



