#include<gtest/gtest.h>
#include"rbtree.h"

TEST(Rbtree,all_case){
  Rbtree<int> test = Rbtree<int>();
  vector<int> test_data = {5,1,3,17,13,15,18,12,19};
  for(size_t i = 0; i < test_data.size(); i++){
    test.insert(test_data[i]);
  }
	vector<int> test_preorder = test.preorder();
	vector<int> test_answer = {13,3,1,12,5,17,15,19,18};
	ASSERT_EQ(test_preorder, test_answer);
	ASSERT_EQ(test.min(), 1);
	ASSERT_EQ(test.max(), 19);
	ASSERT_EQ(test.lower_bound(12),12);
	ASSERT_EQ(test.upper_bound(12),13);
	ASSERT_EQ(test.lower_bound(16),17);
	ASSERT_EQ(test.upper_bound(6),12);
}

int main(int argc, char** argv){
	::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
