#include<bits/stdc++.h>

using namespace std;

struct node{
	char data;
	node* left;
	node* right;
};

int search(char arr[], int strt, int end, char value){
	for(int i = strt; i <= end; i++){
		if(arr[i] == value) return i;
	}
	return -1;
}

node* newNode(char data){
	node* n = new node();
	n->data = data;
	n->left = nullptr;
	n->right = nullptr;
	return (n);
}

node* buildTree(char in[], char pre[], int inStrt, int inEnd){
	static int preIndex = 0;
	if(inStrt > inEnd) return NULL;
	//对当前结点进行创建,创建后往前序遍历后遍历
	node* tNode = newNode(pre[preIndex++]);
	
	//如果当前结点没有左右孩子了
	if(inStrt == inEnd) return tNode;
	
	//如果有左或右就要继续对左右进行建树；但要先找出左边和右边有哪些结点
	int inIndex = search(in, inStrt, inEnd, tNode->data);

	tNode->left = buildTree(in, pre, inStrt, inIndex - 1);
	tNode->right = buildTree(in, pre, inIndex + 1, inEnd);
	return tNode;
}

void printPreorder(node* root){
	if(root == nullptr) return;
	cout << root->data << " ";
	printPreorder(root->left);
	printPreorder(root->right);
}


int main(){
	char in[] = {'D','H','B','E','A','F','C','G'};
	char pre[] = {'A', 'B', 'D', 'H', 'E', 'C', 'F', 'G'};
	int len = 8;
	node* root = buildTree(in, pre, 0, len-1);
	printPreorder(root);
	return 0;
}
