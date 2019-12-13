#include"heap.h"

template<class T, class Cmp>
Heap<T,Cmp>::Heap() : size_(0), cmp_(Cmp()){
	heap_array_.push_back(0);
}

//从index开始向下调整
//时间复杂度:O(logn)
template<class T, class Cmp>
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
template<class T, class Cmp>
void Heap<T,Cmp>::swim(size_t index){
	while(index > 1 && cmp_(heap_array_[index/2], heap_array_[index])){
		swap(heap_array_[index/2], heap_array_[index]);
		index /= 2;
	}
}

//加入元素后调整堆
//push_back加入新数据
template<class T, typename Cmp>
void Heap<T,Cmp>::push(const T& value){
	heap_array_.push_back(value);
	size_++;
	swim(size_);
}

//从index为1出开始储存数据，所以heap_array_[1]为top
template<class T, typename Cmp>
const T& Heap<T,Cmp>::top() const{
	if(heap_array_.size() <= 1){
		throw "heap is empty";
	}
	return heap_array_[1];
}

//top与末尾元素交换后删除尾部元素，size_减小
template<class T, typename Cmp>
void Heap<T,Cmp>::pop(){
	if(heap_array_.size() <= 1){
		throw "heap is empty";
	}
	swap(heap_array_[1], heap_array_[size_]);
	//删去尾部元素	
	heap_array_.pop_back();
	size_--;
	sink(1); 
}

template class Heap<float,greater<float>>;

