#include"basic_algorithm.h"
#include<gtest/gtest.h>
#include<random>
#include<algorithm>

//测试
TEST(sort, three_algorithm){
	//data	
	vector<int64_t> data;
	default_random_engine random;
	uniform_int_distribution<signed> range(-100000,100000);
	int64_t number = 0;	
	for(int i = 0; i < 50000; i++){
		number = range(random);
		data.push_back(number);
	}
	//answer;
	vector<int64_t> answer(data.begin(), data.end());
	sort(answer.begin(),answer.end());
	//merge sort
	BasicAlgorithm sorting;
	vector<int64_t> merge_test(data.begin(), data.end());
	sorting.merge_sort(&merge_test);
	ASSERT_EQ(merge_test, answer);
	//quick sort
	vector<int64_t> quick_test(data.begin(), data.end());
	sorting.quick_sort(&quick_test);
	ASSERT_EQ(quick_test, answer);
	//insertion sort
	vector<int64_t> insertion_test(data.begin(), data.end());
	sorting.insertion_sort(&insertion_test);
	ASSERT_EQ(insertion_test, answer);
}

TEST(topk, legal_input){
	//data	
	vector<int64_t> data;
	default_random_engine random;
	uniform_int_distribution<signed> range(-100000,100000);
	int64_t number = 0;	
	for(int i = 0; i < 10000; i++){
		number = range(random);
		data.push_back(number);
	}
	//answer;
	vector<int64_t> answer(data.begin(), data.end());
	sort(answer.begin(),answer.end());
	//test k
	int size = 6;
	//每个数字代表找到第k小的数字，例：301代表找到第301小
	int test_k[size] = {3,301,4509,5369,7894,9563};
	BasicAlgorithm sorting;
	for(int i = 0; i < size; i++){
		sorting.top_k(&data, test_k[i]);
		ASSERT_EQ(sorting.top_k(&data, test_k[i]), answer[test_k[i]-1]);	
	}
}

int main(int argc, char** argv){
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
