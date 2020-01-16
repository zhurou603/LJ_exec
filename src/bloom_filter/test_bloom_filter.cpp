#include"bloom_filter.h"
#include<gtest/gtest.h>

TEST(false_positive, case1){
  vector<string> test{"hello", "world", "work", "beyond", "output"};
  //1MB,10个哈希函数
  BloomFilter bloom_filter(8388608, 10);
  for(auto s : test){
    bloom_filter.add(s);
  }
  vector<string> query{"yui", "zxc", "qwe", "nc", "twe"};
  for(int i = 0; i < query.size(); i++){
    ASSERT_EQ(bloom_filter.possibly_exist(query[i]), false);
  }
}

int main(int argc, char** argv){
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}