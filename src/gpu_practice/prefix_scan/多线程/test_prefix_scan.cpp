#include"prefix_scan.h"

#include<gtest/gtest.h>
#include<random>


vector<int> single_thread_prefix(const vector<int>& data){
	vector<int> result;
	result.resize(data.size());
	for(int i = 1; i < result.size(); i++){
		result[i] = data[i-1] + result[i-1];
	}
	return result;
}

TEST(multithread, check){
	for(int i = 5; i < 25; i++){
		const int size = pow(2,i);
		vector<int> test_data(size);
		vector<int> data(size);
		default_random_engine random;
		uniform_int_distribution<int> range(-100,100);
		for(int i = 0; i < size; i++){
			int number = range(random);
			test_data[i] = number;
			data[i] = number;
		}
		multithread_prefix_scan(test_data,16);
		ASSERT_EQ(test_data, single_thread_prefix(data));
	}
}


int main(int argc, char** argv){
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
