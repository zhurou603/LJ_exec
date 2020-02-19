#ifndef BARRIER_H
#define BARRIER_H

#include<mutex>
#include<condition_variable>
#include<iostream>
#include<atomic>

using namespace std;

class Barrier{
 public:
	explicit Barrier(int count){
		count_ = count;
	}
	void wait(){
		unique_lock<mutex> lock(mutex_);
		count_ = count_ - 1;
		if(!count_){
			cv_.notify_all();	
		}else{
			cv_.wait(lock, [this] {return count_ == 0;});
		}
	}

 private:
	mutex mutex_;
	condition_variable cv_;
	atomic<int> count_;
};

#endif
