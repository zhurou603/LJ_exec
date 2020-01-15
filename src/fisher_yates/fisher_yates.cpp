#include<vector>
#include<random>
#include<iostream>
#include<ctime>

using namespace std;

void fisher_yates_shuffle(vector<int> *sequence_to_be_shuffled){
	const int size = sequence_to_be_shuffled->size();
	int random_range = 0;
	static default_random_engine random(time(0));
	for(int current_range = size-1; current_range >= 0; current_range--){
		//产生一个随机index
		static uniform_int_distribution<unsigned> range(0,current_range);
		random_range = range(random);
		swap((*sequence_to_be_shuffled)[random_range], (*sequence_to_be_shuffled)[current_range]);
	}
}

int main(){
	vector<int> test{1,2,3,4,5,6,7,8};
	fisher_yates_shuffle(&test);
	for(int i = 0; i < test.size(); i++){
		cout << test[i] << endl;
	}
	return 0;
}


