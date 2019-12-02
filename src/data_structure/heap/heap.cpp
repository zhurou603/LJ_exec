#include"heap.h"
template<class T, typename Cmp>
Heap<T,Cmp>::Heap(size_t capacity) : size_(0), cmp_(Cmp()){
	heap_array_.resize(capacity+1);
}

//从index开始向下调整
//时间复杂度:O(logn)
template<class T, typename Cmp>
void Heap<T,Cmp>::sink(size_t index){
	while(2*index <= size_){
		//第一个孩子的索引		
		size_t child = 2*index;
		//找到更大/更小的孩子
		if(child < size_ && cmp_(heap_array_[child], heap_array_[child+1])) child++;
		if(!cmp_(heap_array_[index],heap_array_[child])) break;
		swap(heap_array_[index], heap_array_[child]);
		index = child;
	} 
}

//从index开始向上调整
//时间复杂度：O(logn)
template<class T, typename Cmp>
void Heap<T,Cmp>::swim(size_t index){
	while(index > 1 && cmp_(heap_array_[index/2], heap_array_[index])){
		swap(heap_array_[index/2], heap_array_[index]);
		index /= 2;
	}
}

//加入元素后调整堆
template<class T, typename Cmp>
void Heap<T,Cmp>::push(const T& value){
	heap_array_[++size_] = value;
	//对vector末尾元素调整堆
	swim(size_);
}

//从index为1出开始储存数据，所以heap_array_[1]为top
template<class T, typename Cmp>
const T& Heap<T,Cmp>::top() const{
	return heap_array_[1];
}

//top与末尾元素交换后调整堆
template<class T, typename Cmp>
void Heap<T,Cmp>::pop(){
	swap(heap_array_[1], heap_array_[size_--]);
	//置空防止越界访问	
	heap_array_[size_+1] = T();
	sink(1); 
}

template class Heap<float,greater<float>>;






