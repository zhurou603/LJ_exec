#ifndef HEAP_H
#define HEAP_H
#include<functional>
#include<vector>

using namespace std;

//Heap类
//构造函数指定一个无符号整数作为heap的容量,并且由user指明数据类型以及大顶堆或小顶堆
//Example: Heap<int,less<int>> example_heap = Heap(13);
//创建一个容量为13的数据元素为int的大顶堆(堆顶元素为堆中最大值)
//const T& top()返回堆中元素最大值/最小值的const reference
//void pop() 删除堆中最大值或最小值数据
//void push(const T& value)向堆中加入值为value元素
template<class T, typename Cmp>
class Heap{
 public:
	Heap(size_t capacity);
	Heap();
	const T& top() const;
	void pop();
	void push(const T& value);

 private:
	//以vector为容器存放数据
	vector<T> heap_array_;	
	size_t size_;
	//比较器,指名大顶堆或小顶堆
	//less<T> or greater<T>
	Cmp cmp_;
	void sink(size_t index);
	void swim(size_t index);
};

#endif
