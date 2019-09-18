#include"longest_increasing_subsequence.h"

//二分查找思想
//找到subsequence中第一个大于等于的元素的index,如果都比它小则返回-1  
int search(const vector<int>& subsequence, int num){
  int low = 0, high = subsequence.size() - 1;
  if(num > subsequence[high]) return -1;
  while(low < high){
    int mid = low + (high - low) / 2;
    if(subsequence[mid] < num){
      low = mid + 1;
    }else{
      high = mid;
    }
  }
  return low;
}

//返回vector中的最长上升子序列的长度
//如[10,9,2,5,3,7,101,18]
//其中[2,5,7,101],[2,3,7,101]均为最长上升序列，因此return 4
int length_of_LIS(const vector<int>& nums) {
	if(0 == nums.size()) return 0;
	vector<int> subsequence = {};
	subsequence.push_back(nums[0]);
	for(int i = 1; i < nums.size(); i++){
		//找出有没有第一个大于等于nums[i]大的元素
		//如果没有说明都比他小,如果有那么替换他
		int first_bigger = search(subsequence, nums[i]);
		if(first_bigger != -1){
			subsequence[first_bigger] = nums[i];
		}else{
			subsequence.push_back(nums[i]);
		}
	}
	return subsequence.size();
}
