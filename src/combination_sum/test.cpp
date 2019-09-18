#include"combination_sum.h"
#include<gtest/gtest.h>

TEST(combination_sum,  regular){
  //k = 2, n = 7;
  vector<vector<int>> test1 = {{1,6}, {2,5}, {3,4}};
  ASSERT_EQ(combination_sum(2,7), test1);
  //k = 3, n = 9; 
  vector<vector<int>> test2 = {{1,2,6}, {1,3,5}, {2,3,4}};
  ASSERT_EQ(combination_sum(3,9), test2);
}

int main(int argc, char** argv){
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}