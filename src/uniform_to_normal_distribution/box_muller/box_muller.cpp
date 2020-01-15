#include<cmath>
#include<random>
#include<ctime>
#include<iostream>
#include<map>
#include<iomanip>

using namespace std;

const double PI  = 3.141592653589793238463;

template<typename T>
class my_normal_distribution{
 public:
	my_normal_distribution(const T& a = 0.0, const T& b = 1.0) : u_(a), v_(b) {}
	T operator () (default_random_engine& engine) const;

 private:
	T u_;
	T v_;
};

template<typename T>
T my_normal_distribution<T>::operator ()(default_random_engine& engine) const{
	//u1,u2
	static uniform_real_distribution<double> range1(0,1);
	static uniform_real_distribution<double> range2(0,1);
	double u1 = range1(engine);
	double u2 = range2(engine);
	double z0 = sqrt(-2*log(u1))*cos(2*PI*u2);
	double z1 = sqrt(-2*log(u1))*sin(2*PI*u2);
	return v_*z0 + u_;
}

int main(){
	static default_random_engine random(time(0));
	static normal_distribution<double> d(5,2);
	static my_normal_distribution<double> test(5,2);
	//test
	map<int,int> hist{};
	for(int n = 0; n < 10000; n++){
		++hist[round(test(random))];
	}
	for(auto p : hist){
		cout << setw(2) << p.first << " " << string(p.second/200, '*') << endl;
	}
	//answer
	map<int,int> hist1{};
	for(int n = 0; n < 10000; n++){
		++hist1[round(d(random))];
	}
	for(auto p : hist){
		cout << setw(2) << p.first << " " << string(p.second/200, '*') << endl;
	}
	return 0;
}

