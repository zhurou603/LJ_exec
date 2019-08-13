#include<iostream>
#include<vector>
#include<thread>
#include<random>
#include<ctime>
#include<future>
#include<chrono>

using namespace std;
using namespace chrono;

//合并vector中[left,mid],[mid+1,right]数据
void merge(vector<int>& data, int left, int mid, int right){
	int i = left;
	int j = mid + 1;
	vector<int> temp;
	while(i <= mid && j <= right){
		if(data[i] <= data[j]){
			temp.push_back(data[i++]);
		}else{
			temp.push_back(data[j++]);
		}
	}
	while(i <= mid){
		temp.push_back(data[i++]);
	}
	while(j <= right){
		temp.push_back(data[j++]);	
	}
	copy(temp.begin(), temp.end(), data.begin() + left);
}

//cpu核数量
int hardware = thread::hardware_concurrency();

//多线程mergesort
void mergesort(vector<int>& data, int left, int right){
	if(left >= right) return;
	//防止溢出
	int mid = left + (right - left) / 2;
	//控制线程数量(更好的方式应该将可用核数量用mutex保护起来)
	if(hardware > 2){
		//异步方式
		auto fn = async(mergesort, ref(data), left, mid);
		cout << "thread" << hardware-- << "launch" << endl;
		mergesort(data, mid + 1, right);
		fn.wait();
	}else{
		mergesort(data, left, mid);
		mergesort(data, mid + 1, right);
	}
	merge(data, left, mid, right);
}

int main(){
	vector<int> data;
	default_random_engine random;
`	//随机数取值范围
	uniform_int_distribution<unsigned> range(1,500);
	int a = 0;
	//创建size为100000000的随机vector
	for(int i = 0; i < 100000000; i++){
		a = range(random);
		data.push_back(a);
	}
	//计时
	time_point<system_clock> t0, t1;
  t0 = system_clock::now();
  mergesort(data, 0, data.size() - 1);
  t1 = system_clock::now();
  cout << "花费时间：" << duration_cast<milliseconds>(t1-t0).count() << "ms\n";
}
