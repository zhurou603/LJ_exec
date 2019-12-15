#include<algorithm>
#include<iostream>
#include"string_sort.h"
#include<gtest/gtest.h>

using namespace std;

TEST(string_sort, small_case){
	vector<string> data{"abc","adv","ASDJ","qnjkl","ab","abc","ASDj"};
	//答案
	vector<string> answer(data);
	sort(answer.begin(),answer.end());
	//待测数据
	vector<string> test(data);
	merge_string_sort(&test);
	ASSERT_EQ(answer, test);
}

int main(int argc, char** argv){
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
