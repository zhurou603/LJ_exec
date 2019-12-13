#include<gtest/gtest.h>
#include"GTEST.h"
#include"heap.h"

TEST(Heap, all_three_function){
	vector<float> data = {56,-45,1,83,0,68,-6};
	Heap<float, greater<float>> test = Heap<float, greater<float>>();
	for(size_t i = 0; i < data.size(); i++){
		test.push(data[i]);
	}
	vector<float> test_result = {0,-45,0,-6,83,56,68,1};
	ASSERT_EQ(test.heap_array_, test_result);
	test.pop();
	vector<float> pop_result = {0,-6,0,1,83,56,68};
	test.push(-900);
	ASSERT_EQ(test.top(),-900);
}

int main(int argc, char** argv){
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
