#ifndef KERNEL_CUH
#define KERNEL_CUH

//分block利用work-efficient算法计算每个block的prefix_scan
//例如
//input =    [1,2,3,4,5,6,7,8,9,10,11,12]分成每个block为2的2次方个元素，分成三块
//output = [0,1,3,6,0,5,11,18,0,9,19,30]
//block_sum = [10,26,42]
__global__ void prefix_sum(int *input, int *output, int *block_sum, size_t data_per_block);

//block_sum = [10,26,42]
//output: block_sum = [10,36,78]
//再作一次串行的block_sum前缀和
void block_scan(int* block_sum, size_t num_block);

//每一个元素都加上它本身
//add函数将除了第一个block的元素都加上之前block的block_sum
//output = [0,1,3,6,0,5,11,18,0,9,19,30]
//block_sum = [10,36,78]
//input =    [1,2,3,4,5,6,7,8,9,10,11,12]
//step 1 : output = [1,3,6,10,5,18,26,9,19,30,42]
//step 2 : output = [1,3,6,10,15,28,36,45,66,78]
__global__ void add(int *output, const int *block_sum, const int* input);

//__global__ void block_scan(int* block_sum, int num_block);
#endif