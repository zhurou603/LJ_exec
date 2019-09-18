#include<gtest/gtest.h>
#include"minimum_path_sum.h"

//测试空数组
TEST(min_path_sum, empty){
  vector<vector<int>> test = {};
  ASSERT_EQ(min_path_sum(test), 0);
}

//测试点1: 3*3 grid
//测试点2: 4*4 grid
TEST(min_path_sum, regular){
  vector<vector<int>> test1 = {{1,3,1}, {4,5,1}, {4,2,1}};
  vector<vector<int>> test2 = {{13,4,13,6}, {12,64,3,6}, {86, 3,7,4}, {7,2,6,1}};
  ASSERT_EQ(min_path_sum(test1), 7);
  ASSERT_EQ(min_path_sum(test2), 44);
}

int main(int argc, char** argv){
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}