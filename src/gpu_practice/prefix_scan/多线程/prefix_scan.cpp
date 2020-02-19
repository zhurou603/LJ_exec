#include"prefix_scan.h"

void prefix_scan_thread(vector<Barrier*>& barriers, vector<int>& output, int id, int epochs, int num_threads, int size){
	int every_thread_step = num_threads << 1;
	int offset = id << 1;
	int base_index = 1;
	int stride = 1;
	 
	//up-sweep
	for(int i = 0; i < epochs; i++){
		int write_pos = base_index + (stride * offset);
		while(write_pos < size){
			output[write_pos] += output[write_pos - stride];
			write_pos += every_thread_step;
		}
		stride <<= 1;
		base_index += stride;
		//跨度
		every_thread_step <<= 1;
		(*barriers[i]).wait();
	}
	
	//down-sweep
	every_thread_step >>= 1;
	base_index -= stride;
	stride >>= 1;
	output[size-1] = 0;
	
	//set-barrier
	(*barriers[barriers.size()-1]).wait();
	
	for(int i = barriers.size() >> 1; i < barriers.size()-1; i++){
		int write_pos = base_index + (stride * offset);
		while(write_pos < size){
			int tmp = output[write_pos];
			int read_value = output[write_pos - stride];
			output[write_pos] += read_value;
			output[write_pos - stride] = tmp;
			write_pos += every_thread_step;
		}
		base_index -= stride;
		stride >>= 1;
		every_thread_step >>= 1;
		(*barriers[i]).wait();
	}
}

//接口设计
void multithread_prefix_scan(vector<int>& input, int num_threads){
	//创建线程组
	thread threads[num_threads];
	const int size = input.size();
	const int epochs = log(size) / log(2);
	vector<Barrier*> barriers;
	for(int i = 0; i < 2*epochs+1; i++){
		Barrier* element = new Barrier(num_threads);
		barriers.push_back(element);
	}
	//对于每个线程执行对应prefix scan
	for(int i = 0; i < num_threads; i++){
		//参数待定
		threads[i] = thread(prefix_scan_thread, ref(barriers), ref(input), i, epochs, num_threads, size);
	}
	for(int i = 0; i < num_threads; i++){
		threads[i].join();
	}
}
