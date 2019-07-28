#include<iostream>
#include<thread>
#include<cstdlib>
#include<ctime>
#include<algorithm>
#include<future>
#include<chrono>
#include<limits>

using namespace std;

const int thread_num = 3;
int data[10000];
int length = sizeof(data) / sizeof(int);

void create_data(int* data, int length){
	srand((int)time(0));
	for (int i = 0; i < length; i++) {
		data[i] = rand()%10000;
	}
}

void multithread_sort(int* data, int length, int thread_num){
	if (length <= 1 || length < (thread_num+1)*(thread_num+1)) {
		sort(data,data+length);
		return;
	}

	int chunk_size = length / (thread_num + 1);
	if (length % (thread_num + 1) != 0) chunk_size++;
	
	auto sort_promise = new promise<void>[thread_num];
	auto sort_future = new future<void>[thread_num];
	for(int i = 0; i < thread_num; i++){
		sort_future[i] = sort_promise[i].get_future();
	}

	for(int i = 0; i < thread_num; i++){
		thread sort_thread([=]{
			sort(data + i*chunk_size, data + (i+1)*chunk_size);
			sort_promise[i].set_value();
		});
		sort_thread.detach();
	}
	
	sort(data + chunk_size*thread_num, data + length);
	
	int* result = new int[length];
	int* index = new int[thread_num + 1];
	for(int i = 0; i < thread_num + 1; i++){
		index[i] = i * chunk_size;
	}
	
	for(int i = 0; i < thread_num; i++){
		sort_future[i].wait();	
	}

	delete[] sort_future;
	delete[] sort_promise;

	for(int i = 0; i < length; i++){
		int min_index;
		int min_num = numeric_limits<int>::max();
		
		for(int j = 0; j < thread_num; j++){
			if((index[j] < (j+1)*chunk_size) && (data[index[j]] < min_num)){
				min_index = j;
				min_num = data[index[j]];
			}			
		}
		if (index[thread_num] < length && (data[index[thread_num]] < min_num)){
			min_index = thread_num;
		}

		result[i] = data[index[min_index]];
		index[min_index]++;
	}
	copy(result, result + length, data);
	delete[] result;
}

int main(){
	int thread_num = 3;
	create_data(data, length);
	multithread_sort(data, length, thread_num);
	for (int i = 0; i < length; i++) {
		cout << data[i] << " ";
	}
	return 0;
}
