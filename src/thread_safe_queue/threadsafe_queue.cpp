#include"ThreadsafeQueue.h"
#include<iostream>
#include<exception>

template<typename T>
ThreadsafeQueue<T>::ThreadsafeQueue(const ThreadsafeQueue& other){
	lock_guard<mutex> lock(other.mut);
	data_queue = other.data_queue;
}

template<typename T>
void ThreadsafeQueue<T>::push(T new_value){
	lock_guard<mutex> lock(mut);
	data_queue.push(new_value);
	data_cond.notify_one();
}

template<typename T>
shared_ptr<T>  ThreadsafeQueue<T>::try_pop(){
	lock_guard<mutex> lock(mut);
	if(data_queue.empty()) return shared_ptr<T>();
	shared_ptr<T> res(make_shared<T>(data_queue.front()));
	data_queue.pop();
	return res;
}

template<typename T>
shared_ptr<T> ThreadsafeQueue<T>::wait_and_pop(){
	unique_lock<mutex> lock(mut);
	data_cond.wait(lock,[this]{return !data_queue.empty();});
	shared_ptr<T> res(make_shared<T>(data_queue.front()));
	data_queue.pop();
	return res;
}

template<typename T>
bool ThreadsafeQueue<T>::empty() const{
	lock_guard<mutex> lock(mut);
	return data_queue.empty();
}

int main(){
	return 0;
}
