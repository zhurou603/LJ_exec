#include"scan.cuh"
#include"kernel.cuh"

#include<iostream>

using namespace std;

//用户只需要传进来主机的input和output数组
void gpu_prefix_scan(const int* input, int* output, size_t size){
  //block_sum为每个block的reduction结果,因此需要先设定block和grid
  //只需要一维的grid和一维的block
  const int threads_per_block = 512;
  //每个线程处理两个数据因此
  const int elements_per_block = 2 * threads_per_block;
  const size_t num_blocks = (size + elements_per_block - 1) / elements_per_block;
  //set dim3
  dim3 blocks(threads_per_block);
  dim3 grids(num_blocks);


  int* block_sum = new int[num_blocks+1];
  //device data
  int* dev_input_data;
  int* dev_output_data;
  int* dev_block_sum;

  //分配内存
  const size_t data_bytes = size * sizeof(int);

  cudaMalloc((void**)&dev_input_data, data_bytes);
  cudaMalloc((void**)&dev_output_data, data_bytes);
  cudaMalloc((void**)&dev_block_sum, num_blocks*sizeof(int));

  //copy data to device
  cudaMemcpy(dev_input_data, input, data_bytes, cudaMemcpyHostToDevice);
  //launch kernel to compute every block prefix sum
  prefix_sum<<<grids, blocks,elements_per_block*sizeof(int)>>>(dev_input_data, dev_output_data, dev_block_sum, elements_per_block);
  cudaMemcpy(block_sum, dev_block_sum, num_blocks*sizeof(int), cudaMemcpyDeviceToHost);
  block_scan(block_sum, num_blocks);
  cudaMemcpy(dev_block_sum, block_sum, num_blocks*sizeof(int), cudaMemcpyHostToDevice);

  //对每个元素加上对应前一个block的和
  //add<<<grids,elements_per_block>>>(dev_output_data, dev_block_sum,dev_input_data);
  add<<<grids,elements_per_block,elements_per_block*sizeof(int)>>>(dev_output_data, dev_block_sum,dev_input_data);
  //copy data from device
  cudaMemcpy(output, dev_output_data, data_bytes, cudaMemcpyDeviceToHost);
  cudaFree(dev_input_data);
  cudaFree(dev_output_data);
  cudaFree(dev_block_sum);
  delete [] block_sum;
}

void cpu_prefix_sum(int* input, int* output, size_t n){
  output[0] = input[0];
  for(size_t i = 1; i < n; i++){
    output[i] = output[i-1] + input[i];
  }
}

void check(int* answer, int* test, size_t size){
  for(size_t i = 0; i < size; i++){
    if(answer[i] != test[i]){
      cout << "计算失败" << endl;
      return;
    }
  }
  cout << "计算成功" << endl;
}