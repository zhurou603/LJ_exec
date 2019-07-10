#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<bitset>
#include<gtest/gtest.h>
using namespace std;

/*将一个uint32_t数据的二进制表示下，每次从低位向高位取其７位
 * 添加到vector的末端，并将第一个元素加上１２８
 *接下来倒序取出其元素拼接为string
 *至此完成从整数到variable byte coding后的二进制string的转化
 */

string encode_number(uint32_t n){
	vector<uint32_t> result;
	string byte;
	uint32_t current_byte = 0;
	while (1) {
		current_byte = n % 128;
		result.push_back(current_byte);
		if (n < 128) break;
		n = n / 128;
	}
	result[0] += 128;
	string current_byte_to_String;
	for (int i = result.size() - 1; i >= 0; i--) {
		bitset<8> b(result[i]);
		current_byte_to_string = b.to_string();
		byte += current_byte_to_string;
	}
	return byte;
}

/*对vector中的每个元素进行encode
 *将每个元素encoding后的结果拼接成最后的string
 */

string encode(const vector<uint32_t>& in_sequence){
	if (in_sequence.empty()) return "";
	string encode_result;
	for (int i = 0; i < in_sequence.size(); i++) {
		encode_result += encode_number(in_sequence[i]);
	}
	return encode_result;
}

/*将序列化后的整数按字节取出
 * 若其小于１２８则说明不为该数字最后一个字节
 * 大于等于则为最后一个字节，完成解码加入vector
 */

vector<uint32_t> decode(const string& serialized_integers){
	vector<uint32_t> numbers;
	uint32_t current_number = 0;
	int index = 0;
  while(index < serialized_integers.length()){
		bitset<8> current(serialized_integers.substr(index,8));
		uint32_t part = (uint32_t)current.to_ullong();
		if (part < 128) {
			current_number = 128*current_number + part;
		}else{
			current_number = 128*current_number + (part - 128);
			numbers.push_back(current_number);
			current_number = 0;
		}
		index += 8;
	}
	return numbers;	
}

/*对四个数字进行测试
 *测试是否能将单个数字转化为二进制的字符串
 */
TEST(ENCODE_NUMBER,case1){
	vector<uint32_t> test = {65,226,456874,0};
	vector<string> test_ans = {"11000001","0000000111100010",\
								"000110110111000110101010","10000000"};
	for(int i = 0; i < test.size(); i++){
		ASSERT_EQ(encode_number(test[i]), test_ans[i]) 
		<< "uint32_t to variable_byte string failed"
		<< "index " << i << "wrong";
	}
	
}
/*对一个vector中的数字进行测试
 *测试能否将uint32_t流编码成variable_byte的二进制字符串
 */
TEST(ENCODE,case1){
	vector<uint32_t> test = {546,6,156478};
	string test_ans = "000001001010001010000110000010010100011010111110";
	ASSERT_EQ(encode(test), test_ans) << "vector<uint32_t> to VBC string failed";
}

/*对编码后的字符串进行测试
 *测试能否解码为对应的vector
 */
TEST(DECODE,case1){
	string test1 = "000001001010001010000110000010010100011010111110";
	vector<uint32_t> test1_ans = {546,6,156478};
	string test2 = "1111111110100101000000010000101111100110";
	vector<uint32_t> test2_ans = {127,37,17894};
	ASSERT_EQ(decode(test1), test1_ans);
	ASSERT_EQ(decode(test2), test2_ans);
}

int main(int argc, char** argv){
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
