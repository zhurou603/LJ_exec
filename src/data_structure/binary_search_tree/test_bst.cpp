#include"bst.h"
#include<gtest/gtest.h>

//测试insert
TEST(insert, case1){
	BinarySearchTree<int> test = BinarySearchTree<int>();
	vector<int> test_data = {54,-15,0,64,3568,1,347,-63};
	size_t size = test_data.size();	
	for(size_t i = 0; i < size; i++){
		test.insert(test_data[i]);
	}
	vector<int> test_result = test.preorder();
	vector<int> test_answer = {54,-15,-63,0,1,64,3568,347};
	ASSERT_EQ(test_result,test_answer);
}

TEST(erase, case2){
	BinarySearchTree<int> test = BinarySearchTree<int>();
	vector<int> test_data = {54,-15,0,64,3568,1,347,-63};
	size_t size = test_data.size();	
	for(size_t i = 0; i < size; i++){
		test.insert(test_data[i]);
	}
	//two child
	test.erase(-15);
	vector<int> test1 = {54,0,-63,1,64,3568,347};
	ASSERT_EQ(test.preorder(), test1);
	test.erase(54);
	vector<int> test2 = {64,0,-63,1,3568,347};
	ASSERT_EQ(test.preorder(), test2);
}

TEST(rdonly_interface, max_min_lower_upper){
	BinarySearchTree<int> test = BinarySearchTree<int>();
	vector<int> test_data = {54,-15,0,64,3568,1,347,-63};
	size_t size = test_data.size();	
	for(size_t i = 0; i < size; i++){
		test.insert(test_data[i]);
	}
	ASSERT_EQ(test.max(),3568);
	ASSERT_EQ(test.min(),-63);
	ASSERT_EQ(test.lower_bound(1),1);
	ASSERT_EQ(test.upper_bound(1),54);
	ASSERT_EQ(test.lower_bound(55),64);
	ASSERT_EQ(test.upper_bound(200),347);
}

int main(int argc,char** argv){
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
