#include<gtest/gtest.h>
#include"group_varint_encode.h"
#include<random>

//测试group_varint_encode(const vector<uint32_t> &original_integers)
//group_varint_decode(const string& encoded_byte_stream)
TEST(group_varint_encode,all_case){
	//空情况
	vector<uint32_t> empty = {};
	ASSERT_EQ(group_varint_decode(group_varint_encode(empty)), empty);
	//产生0～100000000的50000个随机数生成的数组测试
	vector<uint32_t> test = {};
	default_random_engine random;
	uniform_int_distribution<unsigned> range(1,1000000);	
	for(int i = 0; i < 1500000; i++){
		uint32_t number = range(random);
		test.push_back(number);
	}
	vector<uint32_t> result = group_varint_decode(group_varint_encode(test));
	ASSERT_EQ(test, result);
}

int main(int argc, char** argv){
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
