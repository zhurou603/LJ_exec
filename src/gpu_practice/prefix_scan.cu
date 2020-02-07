//suppose 有n = 1 << 20 int data to do prefix sum(exclusive)
//processors is less than data
//1024 blocks, 512 threads/block, every thread can handle 2 int
//then, look at how kernel work

#include<random>
#include<iostream>
#include<cstdlib>
#include<cstdio>

using namespace std;

__global__ void prefix_sum(int *input, int *output, int *block_sum, int data_per_block){
  //copy correspoding data from global memory to shared memory
  //block中threadIdx.x的范围在[0,data_per_block/2 - 1]
  const int data_offset = blockIdx.x *data_per_block;
  extern __shared__ int block_data[];
  block_data[2*threadIdx.x] = input[data_offset + 2*threadIdx.x];
  block_data[2*threadIdx.x + 1] = input[data_offset + 2*threadIdx.x + 1];
  //make sure all data is ready
  __syncthreads();
  //up-sweep
  //step = [0~log(data_per_block)-1]
  //offset控制步伐
  int offset = 1;
  for(int d = data_per_block >> 1; d > 0; d >>= 1){
    //在读写之前设置barrier
    __syncthreads();
    if(threadIdx.x < d){
      int a = (2*threadIdx.x+1)*offset - 1;
      int b = (2*threadIdx.x+2)*offset - 1;
      block_data[b] += block_data[a];
    }
    offset <<= 1;
  }
  __syncthreads();
  //进入down-sweep之前需要保存block sum和清0,交给第一个线程去做
  if(0 == threadIdx.x){
    block_sum[blockIdx.x] = block_data[data_per_block - 1];
    block_data[data_per_block - 1] = 0;
  }

  __syncthreads();

  //进入down_sweep;
  for(int d = 1; d < data_per_block; d <<= 1){
    offset >>= 1;
    __syncthreads();
    if(threadIdx.x <  d){
      int a = (2*threadIdx.x + 1)*offset - 1;
      int b = (2*threadIdx.x + 2)*offset - 1;
      int temp = block_data[b];
      block_data[b] += block_data[a];
      block_data[a] = temp;
    }
  }
  __syncthreads();

  //copy shared memory to global memory
  output[data_offset + 2*threadIdx.x] = block_data[2*threadIdx.x];
  output[data_offset + 2*threadIdx.x + 1] = block_data[2*threadIdx.x + 1];
}

__global__ void add(int *output, const int *block_sum, const int* input){
  output[blockDim.x * blockIdx.x + threadIdx.x] += input[blockDim.x * blockIdx.x + threadIdx.x];
  __syncthreads();
  if(blockIdx.x >= 1){
    output[blockDim.x * blockIdx.x + threadIdx.x] += block_sum[blockIdx.x - 1];
  }
}

void cpu_prefix_sum(int* input, int* output, int n){
  output[0] = input[0];
  for(int i = 1; i < n; i++){
    output[i] = output[i-1] + input[i];
  }
}

void check(int* answer, int* test, int size){
  for(int i = 0; i < size; i++){
    if(answer[i] != test[i]){
      cout << "计算失败" << endl;
      return;
    }
  }
  cout << "计算成功" << endl;
}

const int size = 1 << 28;
//block_sum为每个block的reduction结果,因此需要先设定block和grid
//只需要一维的grid和一维的block
const int threads_per_block = 512;
//每个线程处理两个数据因此
const int elements_per_block = 2 * threads_per_block;
const int num_blocks = (size + elements_per_block - 1) / elements_per_block;

int* input_data = new int[size];
int* output_data = new int[size];
int* block_sum = new int[num_blocks];
int* cpu_output = new int[size];
int main(int argc, char** argv){
  cout << size <<endl;
  //generate input in host
  //填充
  default_random_engine random;
  uniform_int_distribution<signed> range(-10,10);
  for(int i = 0; i < size; i++){
    input_data[i] = range(random);
  }

  //device data
  int* dev_input_data;
  int* dev_output_data;
  int* dev_block_sum;

  //分配内存
  const size_t data_bytes = size * sizeof(int);

  cudaMalloc((void**)&dev_input_data, data_bytes);
  cudaMalloc((void**)&dev_output_data, data_bytes);

  //set dim3
  dim3 blocks(threads_per_block);
  dim3 grids(num_blocks);

  cudaMalloc((void**)&dev_block_sum, num_blocks*sizeof(int));

  //copy data to device
  cudaMemcpy(dev_input_data, input_data, data_bytes, cudaMemcpyHostToDevice);
  //launch kernel to compute every block prefix sum
  prefix_sum<<<grids, blocks,elements_per_block*sizeof(int)>>>(dev_input_data, dev_output_data, dev_block_sum, elements_per_block);

  cudaMemcpy(block_sum, dev_block_sum, num_blocks*sizeof(int), cudaMemcpyDeviceToHost);
  //串行作一次求和
  for(int i = 1; i < num_blocks; i++){
    block_sum[i] += block_sum[i-1];
  }
  cudaMemcpy(dev_block_sum, block_sum, num_blocks*sizeof(int), cudaMemcpyHostToDevice);

  //对每个元素加上对应前一个block的和
  add<<<grids,elements_per_block>>>(dev_output_data, dev_block_sum,dev_input_data);
  cudaDeviceSynchronize();
  //copy data from device
  cudaMemcpy(output_data, dev_output_data, data_bytes, cudaMemcpyDeviceToHost);

  cudaFree(dev_input_data);
  cudaFree(dev_output_data);
  cudaFree(dev_block_sum);
  
  //串行计算
  cpu_prefix_sum(input_data, cpu_output, size);
  check(cpu_output, output_data, size);
  delete [] input_data;
  delete [] output_data;
  delete [] block_sum;
  delete [] cpu_output;
  return 0;
}