#include<fstream>
#include<random>
#include<string>

using namespace std;

const string best_file = "best_case.txt";
const string worst_file = "worst_case.txt";
const string random_file = "random_case.txt";
const int size = 134217728;

//create three files corresponding to three cases:
//best case,worst case,random case
//every file size: 1GB(134217728 int64_t)
//range from:-100000~100000

//random case
bool random_case(){
	ofstream out;
	out.open(random_file, ios::out);
	if(!out){
		return false;
	}
	default_random_engine random;
	uniform_int_distribution<signed> range(-100000,100000);
	int64_t number = 0;
	for(int i = 0; i < size; i++){
		number = range(random);
		out << number << endl;
	}
	return true;
}

/*bool best_case(){
	ofstream out;
	out.open(best_file, ios::out);
}*/

int main(){
	random_case();
}
