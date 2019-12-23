#include"bplustree.h"
#include<gtest/gtest.h>

TEST(insert, degree_3){
  BplusTree test(3);
  vector<int> insertion{4,10,7,23,5,1,6,3,2,9,11,88};
  for(int i = 0; i < 12; i++){
    test.insert(insertion[i], 1);
  }
  //深度优先遍历inter_node结果
  vector<Key> inter_answer{-1,7,-1,3,5,-1,10,23};
  vector<Key> inter_test;
  test.bfs_key(&inter_test);
  ASSERT_EQ(inter_answer, inter_test);
}

int main(int argc, char** argv){
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
