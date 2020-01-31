#include<iostream>
#include<vector>
#include<pybind11/pybind11.h>
#include<pybind11/stl.h>

using namespace std;

vector<vector<double>> dot(const vector<vector<double>>& a, const vector<vector<double>>& b){
	const int row_a = a.size();
	const int column_a = a[0].size();
	const int row_b = b.size();
	const int column_b = b[0].size();
	vector<vector<double>> result;
	if(row_a != column_b) return {};
	result.resize(row_a,vector<double>(column_b));
	for(int i = 0; i < row_a; i++){
		for(int j = 0; j < column_b; j++){
			for(int k = 0; k < row_b; k++){
				result[i][j] += a[i][k] * b[k][j];
			}
		}
	}
	return result;
}

PYBIND11_MODULE(my_c_matrix,m){
	m.def("dot",&dot,"matrix multiply");
}

