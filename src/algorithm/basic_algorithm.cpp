#include"basic_algorithm.h"
#include<iostream>

//快速排序
void BasicAlgorithm::quick_sort(vector<int64_t>* data){
	quick_sort(data,0,data->size()-1);
}

void BasicAlgorithm::quick_sort(vector<int64_t>* data, int low, int high){
	if(low >= high) return;
	int index = partition(data, low, high);
	quick_sort(data, low, index-1);
	quick_sort(data, index+1, high);
}

//topk算法
int64_t BasicAlgorithm::top_k(vector<int64_t>* data, int k){
	top_k(data,0,data->size()-1,k);
	return (*data)[k-1];
}

void BasicAlgorithm::top_k(vector<int64_t>* data, int low, int high, int k){
	if(low >= high) return;
	int index = partition(data, low, high);
	if(index < k-1){
		top_k(data, index+1, high, k);
	}
	else if(index > k-1){
		top_k(data, low, index-1, k);	
	}
}

int BasicAlgorithm::partition(vector<int64_t>* data, int low, int high){
	//select pivot
	int64_t pivot = (*data)[high];
	int i = low;
	int j = high - 1;
	while(i <= j){
		while(i <= high && (*data)[i] < pivot) i++;
		while(j >= low && (*data)[j] >= pivot) j--;
		if(i < j){
			swap((*data)[i], (*data)[j]);
		}else{
			swap((*data)[i], (*data)[high]);
		}
	}
	return i;
}

//插入排序
void BasicAlgorithm::insertion_sort(vector<int64_t>* data){
	size_t size = data->size();	
	for(size_t i = 0; i < size; i++){
		int j = i;
		while(j > 0 && (*data)[j-1] >= (*data)[j]){
			swap((*data)[j-1], (*data)[j]);			
			j--;
		}
	}
}


//归并排序
void BasicAlgorithm::merge_sort(vector<int64_t>* data){
	vector<int64_t> help;
	help.resize(data->size());
	merge_sort(data, &help, 0, data->size()-1);
}

void BasicAlgorithm::merge_sort(vector<int64_t>* data, vector<int64_t>* help, int low, int high){
	if(low >= high) return;
	int mid = low + (high - low) / 2;
	merge_sort(data, help, low, mid);
	merge_sort(data, help, mid+1, high);
	merge(data, help, low, mid, high);
}

void BasicAlgorithm::merge(vector<int64_t>* data, vector<int64_t>* help, int low, int mid, int high){
	//复制原数组数据
	for(int i = low; i <= high; i++){
		(*help)[i] = (*data)[i];
	}
	int left = low;
	int right = mid+1;
	int current = low;
	while(left <= mid && right <= high){
		if((*help)[left] <= (*help)[right]){
			(*data)[current++] = (*help)[left++];
		}else{
			(*data)[current++] = (*help)[right++];
		}
	}
	//不需要检测右边，如果右边是长边，已经在上面复制过
	while(left <= mid){
		(*data)[current++] = (*help)[left++];
	}
}

//二分查找
//描述为：搜索sorted 升序vector中是否存在target，如果存在则返回其下标index，否则返回-1
int BasicAlgorithm::binary_search(const vector<int64_t>& data, int64_t target){
	return binary_search(data, target, 0, data.size()-1);
}

int BasicAlgorithm::binary_search(const vector<int64_t>& data, int64_t target, int low, int high){
	if(0 == data.size()) return -1;
	while(low < high){
		int mid = low + (high - low) / 2;
		if(data[mid] < target){
			low = mid + 1;
		}else{
			high = mid;
		}
	}
	if(data[low] == target) return low;
	return -1;
}

//exponential search
//原理：从左到右可以在logi次内划分到上界，再在[bound/2,bound]二分搜索
//优点：非常适用于要找的index很小的情况，在O(1)时间就能找到目标而二分搜索依然要花费O(logn)
int BasicAlgorithm::exponential_search(const vector<int64_t>& data, int64_t target){
	int size = data.size();	
	if(0 == size) return -1;
	int bound = 1;
	//划分range
	while(bound < size && data[bound] < target) bound *= 2;	
	//wiki实现的是二分搜索在[low,high),现在改写为[low,high]
	return binary_search(data, target, bound / 2, min(bound, size-1));
}

void BasicAlgorithm::radix_sort(vector<int64_t>* data){
	int64_t pos = 1;
	int64_t max = *(max_element(data->begin(), data->end()));
	while(max){
		counting_sort(data, pos);
		pos *= 10;
		max /= 10;
	}
}

//对单个整数位的桶排序,0-9（need ten buckets）
void BasicAlgorithm::counting_sort(vector<int64_t>* data, int64_t pos){
	//initialization	
	vector<int> buckets;
	//十进制
	buckets.resize(10);
	//用于复制结果
	vector<int64_t> output;
	const int size = data->size();
	output.resize(size);
	//distribution
	for(int i = 0; i < size; i++){
		cout << (*data)[i] << endl;
		buckets[((*data)[i] / pos) % 10]++;
	}
	//collection
	for(int i = 1; i < 10; i++){
		buckets[i] += buckets[i-1];
	}
	for(int i = 0; i < size; i++){
		output[buckets[((*data)[i] / pos) % 10] - 1] = (*data)[i];
		buckets[((*data)[i] / pos) % 10]--;
	}
	for(int i = 0; i < size; i++){
		(*data)[i] = output[i];
	}
}


















