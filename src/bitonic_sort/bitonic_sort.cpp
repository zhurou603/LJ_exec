#include<iostream>
#include<algorithm>

using namespace std;

void comp_and_swap(int a[], int i, int j, int dir){
	if(dir == (a[i] > a[j]))
		swap(a[i], a[j]);
}

void bitonicMerge(int a[], int low, int cnt, int dir){
	if(cnt > 1){
		int k = cnt / 2;
		for(int i = low; i < low + k; i++){
			comp_and_swap(a, i, i+k, dir);
		}
		bitonicMerge(a, low, k, dir);
		bitonicMerge(a, low+k, k, dir);
	}
}

void bitonicSort(int a[], int low, int cnt, int dir){
	if(cnt > 1){
		int k = cnt / 2;
		bitonicSort(a, low, k, 1);
		bitonicSort(a, low+k, k, 0);

		bitonicMerge(a, low, cnt, dir);
	}
}

void sort(int a[], int N, int up){
	bitonicSort(a, 0, N, up);
}

int main(){
	int a[] = {3,7,4,8,6,2,1,5};
	int N = sizeof(a) / sizeof(int);
	int up = 1;
	sort(a, N, up);
	for(int i = 0; i < N; i++){
		cout << a[i] << " ";
	}
	return 0;
}
