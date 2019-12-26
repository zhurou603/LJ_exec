#include"bplustree.h"
#include<gtest/gtest.h>

TEST(insert, degree_3){
  BplusTree test(3);
  vector<int> insertion{4,10,7,23,5,1,6,3,2,9,11,88};
	vector<Key> inter_test;
  for(int i = 0; i < 12; i++){
    test.insert(insertion[i], 1);
  }
  //深度优先遍历inter_node结果
  vector<Key> inter_answer{-1,7,-1,3,5,-1,10,23};
	test.bfs_key(&inter_test);	
  ASSERT_EQ(inter_answer, inter_test);
}

/*TEST(remove,degree_3){
	BplusTree test(3);
  vector<int> insertion{4,10,7,23,5,1,6,3,2,9,11,88};
  for(int i = 0; i < 12; i++){
    test.insert(insertion[i], 1);
  }
	test.remove(7);
	vector<Key> inter_test;
	vector<Key> inter_answer{-1,7,-1,3,5,-1,10,23};
	ASSERT_EQ(inter_answer, inter_test);
}*/

TEST(search, degree_3){
	BplusTree test(3);
  vector<int> insertion{4,10,7,23,5,1,6,3,2,9,11,88};
  for(int i = 0; i < 12; i++){
    test.insert(insertion[i], 1);
  }
	ASSERT_EQ(test.search(10)->get_value(),1);
	ASSERT_EQ(test.search(4)->get_value(),1);
	ASSERT_EQ(test.search(89),nullptr);
}


int main(int argc, char** argv){
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
