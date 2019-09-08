#ifndef AVL_H
#define AVL_H
#endif

#include<algorithm>
#include<iostream>
#include<math.h>
#include<vector>

using namespace std;

struct Node{
	int64_t key;
	Node* left;
	Node* right;
	int height;
	//以此根为节点子树结点总和
	int count;
	Node(int64_t k) : key(k), left(NULL), right(NULL), height(1), count(1){}
};

int max(int a, int b);

Node* newNode(int64_t key);

int getHeight(Node* n);

int getCount(Node* n);

Node* rightRotate(Node* y);

Node*	leftRotate(Node* x);

int getBalance(Node* n);

void preOrder(Node* root, vector<int64_t>& result);

Node* minValueNode(Node* node);

Node* insert(Node* node, int64_t key);

Node* deleteNode(Node* root, int64_t key);

int64_t select(Node* root, int k);

double getMedian(Node* root);
