#include"big_int.h"
#include<gtest/gtest.h>

TEST(add, all_case){
	//five cases:空，0相加,后操作数位数多且最高位进位，前操作数长，两数等长
	vector<vector<string>> test = {{"",""},{"0","0"},{"909878","99999999"},\
				{"1230904","4723"},{"64324345","81276893"}};

	vector<string> answer = {"","0","100909877","1235627","145601238"};
	for(int i = 0; i < test.size(); i++){
		ASSERT_EQ((BigInt(test[i][0]) + BigInt(test[i][1])).get_val(), answer[i]);
	}
}

int main(int argc, char** argv){
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
