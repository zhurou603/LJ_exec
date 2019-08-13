#include<iostream>
#include"thread_safe_stack.h"

template<typename T>
ThreadsafeStack<T>::ThreadsafeStack() {}

template<typename T>
ThreadsafeStack<T>::ThreadsafeStack(const ThreadsafeStack& other){
	lock_guard<mutex> lock(other.m_);
	data_ = other.data_;
}

template<typename T>
void ThreadsafeStack<T>::push(T new_value){
	lock_guard<mutex> lock(m_);
	data_.push(new_value);
}

template<typename T>
shared_ptr<T> ThreadsafeStack<T>::pop(){
	lock_guard<mutex> lock(m_);
	if(data_.empty()) throw empty_stack();
	shared_ptr<T> const res(make_shared<T>(data_.top()));
	data_.pop();
	return res;
}

template<typename T>
void ThreadsafeStack<T>::pop(T& value){
	lock_guard<mutex> lock(m_);
	if(data_.empty()) throw empty_stack();
	value = data_.top();
	data_.pop();
}

template<typename T>
bool ThreadsafeStack<T>::empty() const{
	lock_guard<mutex> lock(m_);
	return data_.empty();
}

int main(){
	return 0;
}
