#include"kernel.cuh"

__global__ void prefix_sum(int *input, int *output, int *block_sum, size_t data_per_block){
  //copy correspoding data from global memory to shared memory
  //block中threadIdx.x的范围在[0,data_per_block/2 - 1]
  const size_t data_offset = blockIdx.x *data_per_block;
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
    block_sum[blockIdx.x+1] = block_data[data_per_block - 1];
    block_data[data_per_block - 1] = 0;
  }

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

/*__global__ void add(int *output, const int *block_sum, const int* input){
  output[blockDim.x * blockIdx.x + threadIdx.x] += input[blockDim.x * blockIdx.x + threadIdx.x];
  __syncthreads();
  if(blockIdx.x >= 1){
    output[blockDim.x * blockIdx.x + threadIdx.x] += block_sum[blockIdx.x - 1];
  }
}*/

__global__ void add(int *output, const int *block_sum, const int* input){
  extern __shared__ int out [];
  out[threadIdx.x] = output[blockDim.x * blockIdx.x + threadIdx.x];
  __syncthreads();
  out[threadIdx.x] += input[blockDim.x * blockIdx.x + threadIdx.x] + block_sum[blockIdx.x];
  __syncthreads();
  output[blockDim.x * blockIdx.x + threadIdx.x] = out[threadIdx.x];
}

void block_scan(int* block_sum, size_t num_blocks){
  for(size_t i = 1; i < num_blocks; i++){
    block_sum[i] += block_sum[i-1];
  }
}