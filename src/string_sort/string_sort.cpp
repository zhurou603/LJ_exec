#include"string_sort.h"

//判断字符串a是否小于等于b
bool is_small_equal(const string& a, const string& b){
	//判断a长度是否大于b	
	bool flag = false;
	int len = a.length();
	if(b.length() < len){
		len = b.length();
		flag = true;
	}
	//遍历更短字符串
	for(int i = 0; i < len; i++){
		if(a[i] < b[i]){
			return true;
		}
		else if(a[i] > b[i]){
			return false;
		}
	}
	//若比较完len长度还是相等，那么长度短的小
	if(flag) return false;
	return true;
}

//归并排序
void merge_string_sort(vector<string>* data){
	vector<string> help;
	help.resize(data->size());
	merge_string_sort(data, &help, 0, data->size()-1);	
}

void merge_string_sort(vector<string>* data, vector<string>* help, int low, int high){
	if(low >= high) return;
	int mid = low + (high-low)/2;
	merge_string_sort(data,help,low,mid);
	merge_string_sort(data,help,mid+1,high);
	merge(data,help,low,mid,high);
}

void merge(vector<string>* data, vector<string>* help, int low, int mid, int high){
	for(int i = low; i <= high; i++){
		(*help)[i] = (*data)[i];
	}
	int left = low;
	int right = mid+1;
	int current = low;
	while(left <= mid && right <= high){
		if(is_small_equal((*help)[left], (*help)[right])){
			(*data)[current++] = (*help)[left++];
		}else{
			(*data)[current++] = (*help)[right++];	
		}
	}
	while(left <= mid){
		(*data)[current++] = (*help)[left++];
	}
}
