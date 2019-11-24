#include"bst_serialize_v1.h"
//序列化函数
string serialize(shared_ptr<TreeNode> root){
	//表示一个结点是数字还是NIL结点的值
	int64_t stat_bits = 0x0;
	//stat容器，当结点数量大于64时需要大于64个bits(多个int64_t)来表示
	vector<int64_t> stat;
	//携带实际存在结点的val的容器
	vector<int64_t> values;
	//统计有多少个结点(包括NIL)
	int64_t count_node = 1;
	//前续遍历统计信息
	preorder(root, stat_bits, values, stat, count_node);
  count_node--;
  if(count_node & 0x3f) stat.push_back(stat_bits);
	//序列化(count + stat + values)
	string count_string = encode_int(count_node);
	string stat_string = encode_vector(stat);
	string value_string = encode_vector(values);
	return (count_string + stat_string + value_string);
}

//递归统计序列化信息
void preorder(shared_ptr<TreeNode> root, int64_t& stat_bits, vector<int64_t>& values,
						 vector<int64_t>& stat, int64_t& count_node){
  //判断一个结点是否是NIL结点
  int64_t current_bit = 0x0;
	if(root){
		current_bit++;
	}
  stat_bits = stat_bits | (current_bit << count_node-1);
  //若已经用完一个int64_t则添加到stat容器并重置
	if((count_node & 0x3f) == 0){
		stat.push_back(stat_bits);
		stat_bits = 0x0;
	}
  count_node++;
  //递归
	if(!root){
		return;  
	}
	values.push_back(root->val);
	preorder(root->left, stat_bits, values, stat, count_node);
	preorder(root->right, stat_bits, values, stat, count_node);
}

//反序列化函数
//序列化后结构为index(0,7)为总共节点数目->(8,stat_len)为结点是否为空的stat容器
//剩余为结点的val
shared_ptr<TreeNode> deserialize(const string& serialized){
  //第一部分
	int64_t count = decode_int(serialized.c_str());
  //第二部分
  int stat_len = ((count / 64) + 1)*8;
  string stat_string = serialized.substr(8,stat_len);
  //第三部分
	//第一个参数为数据段开始的首地址，第二个参数为数据段的长度
	vector<int64_t> values = decode_vector((serialized.c_str() + (8 + stat_len)),
																		 (serialized.length()- 8 - stat_len));
  int value_index = 0;
  //递归调用
	shared_ptr<Tpair> p  = recursive_deserialize(stat_string, values, value_index,  0);
	shared_ptr<TreeNode> root = p->node;
	return root;
}

//递归反序列化函数
shared_ptr<Tpair> recursive_deserialize(const string& stat_string,
								 const vector<int64_t>& values, int& value_index, int start){
	//拿当前结点的stat
  bool current_bit = (stat_string[(start/64)*8 + (7 - (start & 0x3f)/8)] 
																					>> ((start & 0x3f) & 7)) & 0x1;
  //为空返回
  if(!current_bit){
    return make_shared<Tpair>(nullptr, start + 1);
  }
  //不为空则建立结点
  shared_ptr<TreeNode> node = make_shared<TreeNode>(values[value_index++]);

  //递归左子树
  shared_ptr<Tpair> p1 = recursive_deserialize(stat_string, values, value_index, start + 1);
  node->left = p1->node;
  
  //递归右子树
  shared_ptr<Tpair> p2 = recursive_deserialize(stat_string, values, value_index, p1->startIndex);
  node->right = p2->node;

	return make_shared<Tpair>(node, p2->startIndex);
}

//以下部分均为整数序列化
string encode_int(int64_t n){
	vector<unsigned char> result;
  unsigned char current_byte = 0;
	string serialized_n;
	for(int i = 0; i < 8; i++){
		current_byte = n & 0xff;
		serialized_n = (char)current_byte + serialized_n;
		n = n >> 8;
	}
  return serialized_n;
}

string encode_vector(const vector<int64_t>& numbers){
	string result;
	for(int i = 0; i < numbers.size(); i++){
		result += encode_int(numbers[i]);
	}
	return result;
}

int64_t decode_int(const char* serialized){
	int64_t result = 0;	
	for(int i = 0; i < 8; i++){
    unsigned char current = serialized[i]; 
		result = result << 8;
		result = (current & 0xff) | result;
	}
	return result;
}

vector<int64_t> decode_vector(const char* serialized, size_t length){
	vector<int64_t> result;
  int index = 0;
	while(index < length){
    result.push_back(decode_int(serialized + index));
		index += 8;
  }
  return result;
}

//以下为二叉树建立及检验
shared_ptr<TreeNode> build(int64_t data[], int length, int index){
	if(index >= length || data[index] == -1) return nullptr;
	shared_ptr<TreeNode> node = make_shared<TreeNode>(data[index]);
	node->left = build(data, length, 2*index + 1);
	node->right = build(data, length, 2*index + 2);
	return node;
}


void printpre(vector<int64_t>& test, shared_ptr<TreeNode> root){
  if(!root) return;
  test.push_back(root->val);
  printpre(test,root->left);
  printpre(test,root->right);
}
