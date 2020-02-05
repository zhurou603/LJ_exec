#include<iostream>
#include<random>

using namespace std;

__global__ void matrix_mul(float* a, float* b, float* c, int m, int n, int k){
  //计算行和列
  const int row = blockIdx.y * blockDim.y + threadIdx.y;
  const int column = blockIdx.x * blockDim.x + threadIdx.x;
  if(row < m && column < k){
    int temp = 0;
    //每一线程负责一次的向量计算
    for(int i = 0; i < n; i++){
      temp += a[row * n + i] * b[i * k + column];
    }
    c[row * k + column] = temp;
  }
}

void dot(float* a, float* b, float* c, int m, int n, int k){
  //在gpu上分配内存
  float* dev_a;
  float* dev_b;
  float* dev_c;
  cudaMalloc((void**)&dev_a, m*n*sizeof(float));
  cudaMalloc((void**)&dev_b, n*k*sizeof(float));
  cudaMalloc((void**)&dev_c, m*k*sizeof(float));
  //copy
  cudaMemcpy(dev_a, a, m*n*sizeof(float), cudaMemcpyHostToDevice);
  cudaMemcpy(dev_b, b, n*k*sizeof(float), cudaMemcpyHostToDevice);
  cudaMemcpy(dev_c, c, m*k*sizeof(float), cudaMemcpyHostToDevice);
  //设置线程
  const int thread_size = 32;
  const int row_block_size = (m + thread_size - 1) / thread_size;
  const int column_block_size = (k + thread_size - 1) / thread_size;
  dim3 blocks(thread_size, thread_size);
  dim3 grids(column_block_size, row_block_size);
  //进入kernel
  matrix_mul<<<grids,blocks>>>(dev_a, dev_b, dev_c, m, n, k);
  //拷贝dev_c到host端
  cudaMemcpy(c, dev_c, m*k*sizeof(float), cudaMemcpyDeviceToHost);
  cout << "矩阵乘法计算完成" << endl;
}

void init_data(float* matrix, int size){
  default_random_engine random;
  uniform_int_distribution<int> range(0,10.0);
  for(int i = 0; i < size; i++){
    matrix[i] = (float)range(random);
  }
}

void cpu_dot(float* a, float* b, float* c, int m , int n, int k){
  for(int i = 0; i < m; i++){
    for(int j = 0; j < k; j++){
      int temp = 0;
      for(int l = 0; l < n; l++){
        temp += a[i * n + l] * b[l * k + j];
      }
      c[i * k + j] = temp;
    }
  }
}

void print_matrix(float* matrix, int m, int n){
  for(int i = 0; i < m; i++){
    for(int j = 0; j < n; j++){
      cout << matrix[i * n + j] << "  ";
    }
    cout << endl;
  }
}

int main(){
  int m = 10, n = 3, k = 3;
  //有两个host matrix
  float host_a[m*n];
  float host_b[n*k];
  float host_c[m*k];
  float answer[m*k];
  //初始化数据
  init_data(host_a, m*n);
  init_data(host_b, n*k);
  cout << "初始化完成" << endl;
  print_matrix(host_a, m,n);
  print_matrix(host_b, n,k);
  //给dot函数计算矩阵相乘, m, n, k为矩阵size,结果存放在host_c
  dot(host_a, host_b, host_c, m, n, k);
  cout << "kernel完成" << endl;
  cpu_dot(host_a, host_b, answer, m, n, k);
  cout << "cpu完成" << endl;
  return 0;
}