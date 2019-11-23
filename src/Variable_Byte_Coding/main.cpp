#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<gtest/gtest.h>
#include<random>

using namespace std;

//对单个uint32_t进行variable Byte coding/home/zhurou603/桌面/practice/LJ_exec/src/bst_serialize/build.cpp
//从低位向高位每次取7位push_back至result中
//第一个Byte的第八位为１,作为标志位
string encode_number(uint32_t n){
	char current_byte;
	string byte;
	while (1) {
		current_byte = n & 0x7f;
		byte = current_byte + byte;
		if (n < 128) break;
		n = n >> 7;
	}
	byte[byte.size()-1] += 128;
	//将每个char(8位)倒序放入string容器中
	return byte;
}

//将vector<uint32_t>整数流序列化
//返回string,string中每一个char代表一个Byte
string encode(const vector<uint32_t>& in_sequence){
	string serialized_integers;
	const int size = in_sequence.size();
	for (int i = 0; i < size; i++) {
		serialized_integers += encode_number(in_sequence[i]);
	}
	return serialized_integers;
}

//将序列化后的string解码为若干整数
//从高位向低位按字节处理,直到遇到某一Byte最高位为１，判定为一个整数
vector<uint32_t> decode(const string& serialized_integers){
	vector<uint32_t> numbers;
	uint32_t current_number = 0;
	int index = 0;
  while (index < serialized_integers.length()) {
		//用unsigned char而不是char
		//因为char(-128~128),unsigned char(0~255),与无符号整数相对应
		unsigned char current_byte = serialized_integers[index];
		uint32_t part = (uint32_t)current_byte;
		if (part < 128) {
			current_number = (current_number << 7) + part;
		}else {
			current_number = (current_number << 7) + (part - 128);
			numbers.push_back(current_number);
			current_number = 0;
		}
		index++;
	}
	return numbers;	
}

//测试单个uint32_t能否进行variable Byte coding
TEST(encode_number,case1){
	//五个测试的整数
	vector<uint32_t> test = {226,65,78675,0,1231};
	//编码后的char数据，如226编码后需要两个字节
	//高八位(第一个char)为1,低八位(第二个char)为-30
	vector<vector<int>> test_ans = {{1,-30},{-63},{4,102,-45},{128},{9,-49}};
	for (int i = 0; i < test.size(); i++) {
		string ans = "";		
		for (int j = 0; j < test_ans[i].size(); j++) {
			ans += (char)test_ans[i][j];
		}
		ASSERT_EQ(encode_number(test[i]), ans) 
		<< "an uint32_t to string wrong at index " << i; 
	}
}

//测试uint32_t数据流能否完成VB coding
TEST(encode,case2){
	vector<uint32_t> test = {226,65,0,1231,78675};
	vector<vector<int>> test_ans = {{1,-30},{-63},{128},{9,-49},{4,102,-45}};
	string ans = "";
	for (int i = 0; i < test.size(); i++) {		
		for (int j = 0; j < test_ans[i].size(); j++) {
			ans += (char)test_ans[i][j];
		}
	}
	ASSERT_EQ(encode(test), ans) 
		<< "a vector to string wrong"; 
}

//测试string能否decode成对应的vector<uint32_t>
TEST(decode,case3){
	vector<vector<int>> test = {{9,-49},{1,-30},{-63},\
																	{128},{9,-49},{4,102,-45}};
	//生成测试string
	string test_string = "";
	for (int i = 0; i < test.size(); i++) {		
		for (int j = 0; j < test[i].size(); j++) {
			test_string += (char)test[i][j];
		}
	}
	//对应vector
	vector<uint32_t> ans = {1231,226,65,0,1231,78675};
	ASSERT_EQ(decode(test_string), ans);
}

//产生100000的(0,100000000)的随机整数进行测试
TEST(decode,random){
	default_random_engine random;
	uniform_int_distribution<unsigned> range(0,100000000);
	vector<uint32_t> test;
	uint32_t number = 0;
	for(int i = 0; i < 100000; i++){
		number = range(random);
		test.push_back(number);
	}
	ASSERT_EQ(test, decode(encode(test)));
}

int main(int argc, char** argv){
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
