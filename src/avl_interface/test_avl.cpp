#include<gtest/gtest.h>
#include"avl.h"

//测试AVL insert接口
TEST(insert,case1){
	Node* root = NULL;
	int64_t data[6] = {1,2,3,4,5,6};
	for(int i = 0; i < 6; i++){
		root = insert(root, data[i]);
	}
	vector<int64_t> data_result;
	preOrder(root, data_result);
	vector<int64_t> result = {4,2,1,3,5,6};
	ASSERT_EQ(data_result, result);
}

TEST(remove, case1){
	Node* root = NULL;
	int64_t data[6] = {1,2,3,4,5,6};
	for(int i = 0; i < 6; i++){
		root = insert(root, data[i]);
	}
	//含有两个孩子结点
	root = deleteNode(root, 2);
	vector<int64_t> delete_result1;
	preOrder(root, delete_result1);
	vector<int64_t> ans1 = {4,3,1,5,6};
	ASSERT_EQ(delete_result1, ans1);
	//含有一个孩子结点
	root = deleteNode(root, 5);
	vector<int64_t> delete_result2;
	preOrder(root, delete_result2);
	vector<int64_t> ans2 = {4,3,1,6};
	ASSERT_EQ(delete_result2, ans2);
}

TEST(median, case1){
	//奇数个元素
	Node* root = NULL;
	int64_t data[7] = {1,22,3,47,58,623,9};
	for(int i = 0; i < 7; i++){
		root = insert(root, data[i]);
	}
	double ans = 22;
	ASSERT_EQ(getMedian(root), ans);
	//偶数个元素
	root = deleteNode(root, 3);
	double ans2 = 34.5;
	ASSERT_EQ(getMedian(root), ans2);
}


int main(int argc, char** argv){
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
