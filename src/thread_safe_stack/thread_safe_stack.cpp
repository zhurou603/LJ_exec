#include<iostream>
#include"thread_safe_stack.h"

template<typename T>
threadsafe_stack<T>::threadsafe_stack() {}

template<typename T>
threadsafe_stack<T>::threadsafe_stack(const threadsafe_stack& other){
	lock_guard<mutex> lock(other.m_);
	data_ = other.data_;
}

template<typename T>
void threadsafe_stack<T>::push(T new_value){
	lock_guard<mutex> lock(m_);
	data_.push(new_value);
}

template<typename T>
shared_ptr<T> threadsafe_stack<T>::pop(){
	lock_guard<mutex> lock(m_);
	if(data_.empty()) throw empty_stack();
	shared_ptr<T> const res(make_shared<T>(data_.top()));
	data_.pop();
	return res;
}

template<typename T>
void threadsafe_stack<T>::pop(T& value){
	lock_guard<mutex> lock(m_);
	if(data_.empty()) throw empty_stack();
	value = data_.top();
	data_.pop();
}

template<typename T>
bool threadsafe_stack<T>::empty() const{
	lock_guard<mutex> lock(m_);
	return data_.empty();
}
