#ifndef BST_SERIALIZE_V1_H
#define BST_SERIALIZE_V1_H
#include<memory>
#include<utility>
#include<string>
#include<iostream>
#include<vector>

using namespace std;

//二叉树结点
struct TreeNode{
	int64_t val;
	shared_ptr<TreeNode> left;
	shared_ptr<TreeNode> right;
	TreeNode(int64_t v) : val(v), left(nullptr), right(nullptr) {} 
};

//返回信息对，返回结点信息和前续遍历下一结点的index
struct Tpair{
	shared_ptr<TreeNode> node;
	int startIndex;
	Tpair(shared_ptr<TreeNode> n, int s) : node(n), startIndex(s) {} 
};

//序列化函数
string serialize(shared_ptr<TreeNode> root);

void preorder(shared_ptr<TreeNode> root, int64_t& stat_bits,
						 vector<int64_t>& value, vector<int64_t>& stat, int64_t& count_node);

//反序列化二叉树函数
shared_ptr<TreeNode> deserialize(const string& serialized);

shared_ptr<Tpair> recursive_deserialize(const string& stat_string,
						 const vector<int64_t>& value, int& value_index, int start);


//序列化反序列化整数
string encode_int(int64_t n);

string encode_vector(const vector<int64_t>& numbers);

int64_t decode_int(const char* serialized);

vector<int64_t> decode_vector(const char* serialized, size_t length);

//构造二叉树，以及检验二叉树的前序遍历
shared_ptr<TreeNode> build(int64_t data[], int length, int index);

void printpre(vector<int64_t>& test, shared_ptr<TreeNode> root);

#endif
