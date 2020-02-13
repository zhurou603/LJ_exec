#ifndef SCAN_CUH
#define SCAN_CUH
//用户只需要传进来主机的input和output数组
void gpu_prefix_scan(const int* input, int* output, size_t size);

void check(int* answer, int* test, size_t size);

void cpu_prefix_sum(int* input, int* output, size_t n);
#endif