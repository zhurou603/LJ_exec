#include<fstream>
#include<vector>
#include<random>
#include<string>
#include<iostream>

using namespace std;

const string file_name = "../data.txt";
const uint32_t number = 30000000;
const uint32_t lower = 0;
const uint32_t upper = 20000000;

//产生10000000个uint32_t范围在(0~20000000)
bool create_data(const string& file_name){
	ofstream out;
	out.open(file_name, ios::out);
	if(!out){
		cout << "open failed" << endl;
		return false;
	}
	default_random_engine random;
	uniform_int_distribution<unsigned> range(lower,upper);
	uint32_t data = 0;	
	for(int i = 0; i < number; i++){
		data = range(random);
		out << data << endl;
	}
	out.close();
	return true;
}

int main(){
	bool success = create_data(file_name);
	return 0;
}
