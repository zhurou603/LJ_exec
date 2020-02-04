#include<cstdio>
#include<cstdlib>
#include<random>

using namespace std;

const int threads_per_block = 1024;

//将当前block利用共享内存进行reduction
__global__ void reduce(float* input, float* output){
  //共享内存申请
  __shared__ float shrared[threads_per_block];
  //坐标
  int id = threadIdx.x + blockDim.x * blockIdx.x;
  int tid = threadIdx.x;
  //从global memory读取数据到共享内存
  shrared[tid] = input[id];
  __syncthreads();

  //归约
  for(int s = blockDim.x / 2; s > 0; s >>= 1){
    if(tid < s){
      shrared[tid] += shrared[tid + s];
    }
    __syncthreads();
  }

  //将首元素填充到output;
  output[blockIdx.x] = shrared[0];
}

void reduction(float* data, float* result, float* part_result, int data_size){
  //计算需要多少block
  int num_blocks = (data_size + threads_per_block -1) / threads_per_block;
  //调用归约函数
  reduce<<<num_blocks,threads_per_block>>>(data, part_result);
  //现在得到part_result为每个block的和,归约该数组
  int final_step_num_threads = num_blocks;
  reduce<<<1,final_step_num_threads>>>(part_result,result);
}

int main(int argc, char** argv){
  //生成输入数据,1GB的float
  const int data_size = 1 << 20;
  float data[data_size];
  default_random_engine random;
  uniform_real_distribution<float> range(-2.0,2.0);
  float result = 0.0;
  for(int i = 0; i < data_size; i++){
    data[i] = range(random);
    result += data[i];
  }
  printf("数据完成");
  
  //gpu part
  float* dev_input;
  float* dev_output;
  float* dev_part;

  //分配内存
  cudaMalloc((void**)&dev_input, data_size*sizeof(float));
  cudaMalloc((void**)&dev_output, sizeof(float));
  int num_blocks = (data_size + threads_per_block -1) / threads_per_block;
  cudaMalloc((void**)&dev_part, num_blocks*sizeof(float));

  //拷贝数据到设备
  cudaMemcpy(dev_input, data, data_size*sizeof(float), cudaMemcpyHostToDevice);
  //计算
  reduction(dev_input,dev_output,dev_part,data_size);
  //拷贝结果
  float dev_result = 0.0;
  cudaMemcpy(&dev_result, dev_output, sizeof(float), cudaMemcpyDeviceToHost);
  printf("cpu calculate:  %f,  cuda result:  %f", result, dev_result);

  cudaFree(dev_input);
  cudaFree(dev_output);
  cudaFree(dev_part);
  return 0;
}