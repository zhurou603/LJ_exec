#include<vector>
#include<string>
#include"MurmurHash3.h"

using namespace std;

//设定查询字符串是否在bloom filter
class BloomFilter{
 public:
  //构造函数
  //size_  有多少个bit
  //num_hash哈希函数数量
  BloomFilter(int size, int num);

  //add
  void add(const string& input);

  //query
  bool possibly_exist(const string& input);

 private:
  uint64_t* hash(const string& input);
  int64_t nth_hash(int n, const uint64_t result[]);
  int num_hash_;
  int capacity_;
  vector<bool> bits_;
};