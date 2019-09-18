#include"combination_sum.h"

//返回所有相加之和为n的k个数组的组合，组合数字为1-9
//例:k = 3, n = 9
//返回 [[1,2,6], [1,3,5], [2,3,4]]
vector<vector<int>> combination_sum(int k, int n) {
  if(9*k < n) return {};
  vector<vector<int>> result = {};
  vector<int> part = {};
  //回溯算法
  back_tracking(k, n, 1, part, result);
  return result;
}

//无返回值，若得到某一结果则直接push_back入result
void back_tracking(int k, int n, int num, vector<int> part, 
                                          vector<vector<int>>& result){
  //递归终止条件,若递归到k = 1, n = x,且x <= 9那么完成某一结果part
  if(1 == k){
    if(n >= num && n <= 9){
      part.push_back(n);
      result.push_back(part);
    }
    return;
  }
  //从i到n尝试组合
  for(int i = num; i < 10; i++){
    if(i <n){
      part.push_back(i);
      back_tracking(k-1, n-i, i+1 , part, result);
      part.pop_back();
    }else{
      break;
    }
  }
}