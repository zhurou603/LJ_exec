#include"scan.cuh"
#include"cuda_runtime.h"

#include<chrono>
#include<random>
#include<iostream>
#include<math.h>

using namespace std;
using namespace chrono;

int main(){
  for(int i = 5; i <= 28; i++){
    size_t size = pow(2,i);
    int* input = new int[size];
    int* gpu_output = new int[size];
    int* cpu_output = new int[size];
    default_random_engine random;
    uniform_int_distribution<> range(-5,5);
    for(size_t i = 0; i < size; i++){
      input[i] = range(random);
    }
    time_point<system_clock> start, end;
    start = system_clock::now();
    gpu_prefix_scan(input, gpu_output, size);
    cudaDeviceSynchronize();
    end = system_clock::now();
    float gpu_time = duration_cast<microseconds>(end - start).count();
    cout << "gpu: " << i << " " << gpu_time/1000 << " ms" << endl;

    start = system_clock::now();
    cpu_prefix_sum(input, cpu_output, size);
    end = system_clock::now();
    float cpu_time = duration_cast<microseconds>(end - start).count();
    cout << "cpu: " << i << " " << cpu_time/1000 << " ms" << endl;
    cout << endl;
    check(gpu_output, cpu_output, size);
    delete [] input;
    delete [] gpu_output;
    delete [] cpu_output;
  }
  return 0;
}

