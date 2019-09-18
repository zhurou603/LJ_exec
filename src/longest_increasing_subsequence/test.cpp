#include"longest_increasing_subsequence.h"

#include<gtest/gtest.h>

//测试所有元素均小于target，应返回-1
TEST(search, less_equal){
	vector<int> test = {-45,6,45,87,659,1203};
	int target1 = 1204, target2 = 3021;
	ASSERT_EQ(search(test,target1), -1);
	ASSERT_EQ(search(test,target2), -1);
}

//测试点1:若target存在
//测试点2:target不存在但有大于target的数据
TEST(search, first_bigger_equal){
	vector<int> test = {-23,6,35,721,1235,345346};
	int target1 = 35, target2 = 900;
	ASSERT_EQ(search(test,target1), 2);
	ASSERT_EQ(search(test,target2), 4);
}

//测试数据为空
TEST(length_of_LIS, empty){
	vector<int> test = {};
	ASSERT_EQ(length_of_LIS(test),0);
}

//数据为降序最长长度即为1
TEST(length_of_LIS, decreasing){
	vector<int> test = {156,123,85,15,7,3,-54};
	ASSERT_EQ(length_of_LIS(test),1);
}

//测试随机数列
TEST(length_of_LIS, random){
	vector<int> test = {10,9,2,5,3,7,101,18,6,1};
	vector<int> ans = {2,3,7,101};	
	ASSERT_EQ(length_of_LIS(test), ans.size());
}

int main(int argc, char** argv){
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

