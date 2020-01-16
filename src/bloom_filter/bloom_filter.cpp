#include"bloom_filter.h"

BloomFilter::BloomFilter(int size, int num) : num_hash_(num), capacity_(0){
  bits_.resize(size);
}

void BloomFilter::add(const string& input){
  //算出哈希值，为两个64bit组成的数组
  const uint64_t* hashvalue = hash(input);
  //用该哈希值映射到num_hash_哈希函数并置1
  for(int i = 0; i < num_hash_; i++){
    bits_[nth_hash(i, hashvalue)] = true;
  }
  capacity_++;
}

bool possibly_exist(const string& input);
//计算哈希值，返回128bit结果存在两个uint64_t中
uint64_t* BloomFilter::hash(const string& input){
  vector<uint64_t> result;
  result.resize(2);
  MurmurHash3_x86_128(input.c_str(), input.length(), 0, result.data());
  return result.data();
}

//double hashing 计算第n个哈希值,返回对应的bit位置
int64_t BloomFilter::nth_hash(int n, const uint64_t result[]){
  return (result[0] + n*result[1]) % bits_.size();
}

bool BloomFilter::possibly_exist(const string& input){
  const uint64_t* hashvalue = hash(input);
  for(int i = 0; i < num_hash_; i++){
    if(!bits_[nth_hash(i, hashvalue)]){
      return false;
    }
  }
  return true;
}