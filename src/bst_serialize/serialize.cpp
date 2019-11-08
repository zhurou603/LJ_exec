#include"serialize.h"

void encode_node(string& order, int64_t value){
	vector<char> result;
	char current_byte;
	while (1) {
		current_byte = value % 128;
		result.push_back(current_byte);
		if (value < 128) break;
		value= value / 128;
	}
	result[0] += 128;
	//将每个char(8位)倒序放入string容器中
	string byte = "";
  for (int i = result.size() - 1; i >= 0; i--) {
		byte += result[i];
	}
	order += byte;
}

void preorder(string& order, TreeNode* root){
	if(nullptr == root) return;
  encode_node(order, root->val);
	preorder(order, root->left);
	preorder(order, root->right);
}

void inorder(string& order, TreeNode* root){
	if(nullptr == root) return;
	inorder(order, root->left);
  encode_node(order, root->val);
	inorder(order, root->right);
}

//序列化
string serialize(TreeNode* root){
	string pre = "";
	preorder(pre, root);
	string in = "";
	inorder(in, root);
	return (pre+in);
}

vector<int64_t> decode(const string& serialized_integers){
	vector<int64_t> numbers;
	int64_t current_number = 0;
	int index = 0;
  while (index < serialized_integers.length()) {
		//用unsigned char而不是char
		//因为char(-128~128),unsigned char(0~255),与无符号整数相对应
		unsigned char current_byte = serialized_integers[index];
		int64_t part = (int64_t)current_byte;
		if (part < 128) {
			current_number = 128*current_number + part;
		}else {
			current_number = 128*current_number + (part - 128);
			numbers.push_back(current_number);
			current_number = 0;
		}
		index++;
	}
	return numbers;	
}

TreeNode* rebuild(const  vector<int64_t>& decoding, int inStrt, int inEnd){
	static int preIndex = 0;
	if(inStrt > inEnd) return NULL;
	//对当前结点进行创建,创建后往前序遍历后遍历
	TreeNode* tNode = new TreeNode(decoding[preIndex++]);
	
	//如果当前结点没有左右孩子了
	if(inStrt == inEnd) return tNode;
	
	//如果有左或右就要继续对左右进行建树；但要先找出左边和右边有哪些结点
	int inIndex = search(decoding, inStrt, inEnd, tNode->val);

	tNode->left = rebuild(decoding, inStrt, inIndex - 1);
	tNode->right = rebuild(decoding, inIndex + 1, inEnd);
	return tNode;
}

//反序列化
TreeNode* deserialize(const string& data){
  vector<int64_t> decoding = decode(data);
  int instart = decoding.size() / 2;
  int inend = decoding.size() - 1;
  TreeNode* rebuild_root = rebuild(decoding, instart, inend);
	return rebuild_root; 
}

//以下为检验代码
void printpre(TreeNode* root){
  if(nullptr == root) return;
  cout << (char)root->val << endl;
  printpre(root->left);
  printpre(root->right);
}


TreeNode* build(int64_t data[], int length, int index){
	if(index >= length || data[index] == -1) return nullptr;
	TreeNode* node = new TreeNode(data[index]);
	node->left = build(data, length, 2*index + 1);
	node->right = build(data, length, 2*index + 2);
	return node;
}

int main(){
	//建造二叉树
	int64_t data[] = {51,49,50,53,55,56,57,-1,-1,54,-1,-1,52};
	TreeNode* root = build(data, 13, 0);
	string result = serialize(root);
	TreeNode* re = deserialize(result);
  printpre(re);
	return 0;
}


