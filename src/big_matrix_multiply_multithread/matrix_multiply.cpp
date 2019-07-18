#include<iostream>
#include<cstdlib>
#include<memory.h>
#include"Matrix.h"
#include<thread>
#include<ctime>

using namespace std;

//控制线程数量
const int THREADS_NUMBER = 4;

//将矩阵元素初始化为0
//problem:内存不够放
void Matrix::Init(){
	matrix = new long long*[max_size];
	for(int i = 0; i < max_size; i++){
		matrix[i] = new long long[max_size];
		for(int j = 0; j < max_size; j++){
			matrix[i][j] = 0;		
		}	
	}
}

//随机赋值
void Matrix::Init_random(){
	for(int i = 0; i < row_; i++){
		for(int j = 0; j < column_; j++){
			matrix[i][j] = rand() % 20;
		}		
	}
}

//多线程矩阵相乘计算
void multiply_threading(Matrix& result, const int thread_number, \
												const Matrix& m1, const Matrix& m2){
	//计算工作负载部分	
	//矩阵元素数量
	const int n_elements = max_size * max_size;
	//每部分需要操作多少元素
	const int n_operations = n_elements / THREADS_NUMBER;
	//不能平分余下的元素
	const int rest_operations = n_elements % THREADS_NUMBER;
	int start_op, end_op;
	//将二维矩阵看成一维
	//主线程的工作index范围，如矩阵为３*3，线程有4个
	//0:[0,3), 1:[3,5), 2:[5,7), 3:[7,9)
	if(thread_number == 0){
		start_op = n_operations * thread_number;
		end_op = (n_operations * (thread_number + 1)) + rest_operations;	
	}else{
		start_op = n_operations * thread_number + rest_operations;
		end_op = (n_operations * (thread_number + 1)) + rest_operations;
	}
	for(int op = start_op; op < end_op; op++){
		const int row = op % max_size;
		const int col = op / max_size;
		long long value = 0;
		for(int i = 0; i < max_size; i++){
			long long m1_val = m1.matrix[row][i];
			long long m2_val = m2.matrix[i][col];
			value += m1_val * m2_val;		
		}
		result.matrix[row][col] = value;		
	}
}

//创建多个计算线程
void multhreading_execution(Matrix& result, const Matrix& m1, const Matrix& m2){
	cout << "开始多线程计算" << endl;	
	//创建线程组	
	thread threads[THREADS_NUMBER];
	for(int i = 0; i < THREADS_NUMBER; i++){
		//线程启动		
		threads[i] = thread(multiply_threading, ref(result), i, ref(m1), ref(m2));
		cout << "线程" << i << "已经启动" <<endl;
	}
	for(int i = 0; i < THREADS_NUMBER; i++){
		threads[i].join();
	}
}

//单线程计算矩阵相乘.
void multiply(Matrix& result, const Matrix& m1, const Matrix& m2) {
  for (int i = 0; i < max_size; ++i) {
    for (int j = 0; j < max_size; ++j) {
      long long value = 0;
      for (int k = 0; k < max_size; ++k) {
        const long long m1_val = m1.matrix[i][k];
        const long long m2_val = m2.matrix[k][j];
        value += m1_val * m2_val;
      }
      result.matrix[i][j] = value;
    }
  }
}

int main(){
	cout << "矩阵规模：" << max_size << endl;
	//测试矩阵初始化
	Matrix m1 = Matrix(max_size,max_size);
	Matrix m2 = Matrix(max_size,max_size);
	Matrix result = Matrix(max_size,max_size);
	Matrix multithread_result = Matrix(max_size,max_size);
	m1.Init();
	m2.Init();
	multithread_result.Init();
	result.Init();
	m1.Init_random();
	m2.Init_random();

	//多线程计算	
	clock_t start,stop;
	start = clock();
	multhreading_execution(multithread_result, m1, m2);
	stop = clock();
	cout << "4个线程花费时间：" 
			 << (float)(stop - start)*1000/CLOCKS_PER_SEC << " ms" << endl; 
	//单线程计算
	start = clock();	
	multiply(result, m1, m2);
	stop = clock();
	cout << "单线程花费时间：" 
			 << (float)(stop - start)*1000/CLOCKS_PER_SEC << " ms" << endl; 
	return 0;
}
