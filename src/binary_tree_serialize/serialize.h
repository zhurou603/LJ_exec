#ifndef SERIALIZE_H
#define SERIALIZE_H
#include<string>
#include<vector>
#include<iostream>

using namespace std;

struct TreeNode{
	int64_t val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int64_t v) : val(v), left(nullptr), right(nullptr) {}
};

int search(const vector<int64_t>& decoding, int low, int high, int64_t value){
  while(low < high){
    int mid = low + (high - low) / 2;
    if(decoding[mid] < value){
      low = mid + 1;
    }else{
      high = mid;
    }
  }
	return low;
}

string serialize(TreeNode* root);

TreeNode* deserialize(const string& data);

#endif
