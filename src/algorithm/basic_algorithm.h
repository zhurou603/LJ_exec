#ifndef BASIC_SORT_H
#define BASIC_SORT_H

#include<vector>
#include<stdint.h>
#include<algorithm>
#include"math.h"
#include"./data_structure/heap.h"

using namespace std;

//default: 升序
class BasicAlgorithm{
 public:
	void merge_sort(vector<int64_t>* data);
	void quick_sort(vector<int64_t>* data);
	void radix_sort(vector<int64_t>* data);
	void insertion_sort(vector<int64_t>* data);
	int64_t top_k(vector<int64_t>* data, int k);
	void intro_sort(vector<int64_t>* data);
	int binary_search(const vector<int64_t>& data, int64_t target);
	int exponential_search(const vector<int64_t>& data, int64_t target);
 	void heap_sort(vector<int64_t>* data);
 private:
	int partition(vector<int64_t>* data, int low, int high);
	void quick_sort(vector<int64_t>* data, int low, int high);
	void merge_sort(vector<int64_t>* data, vector<int64_t>* help, int low, int high);
	void merge(vector<int64_t>* data, vector<int64_t>* help, int low, int mid, int high);
	void top_k(vector<int64_t>* data, int low, int high, int k);
	int binary_search(const vector<int64_t>& data, int64_t target, int low, int high);
	void counting_sort(vector<int64_t>* data, int64_t pos);
	void intro_sort(vector<int64_t>* data, int low, int high, int max_depth);	
};

#endif
