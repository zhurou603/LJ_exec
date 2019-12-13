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








