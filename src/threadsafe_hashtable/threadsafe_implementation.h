#ifndef HASH_TABLE
#include"threadsafe_hashtable.h"
#endif

#ifndef MEMORY_H
#include<memory.h>
#endif

//构造函数，动态分配capacity_个Entry指针,指向词条对象
Hashtable::Hashtable(){
	size_ = 0;
	hashtable_ = new Entry*[capacity_];
	memset(hashtable_, 0, sizeof(Entry*) * capacity_);
	//懒惰删除标记
	lazymark = new bool[capacity_];
	memset(lazymark, 0, sizeof(bool) * capacity_);
}

//冲突解决策略
int Hashtable::probe4Hit(const int& key){
	int index = key % capacity_;
	//如果该位置已经被占据且不为重复值
	//或者带有懒惰删除标记则向后查找
	while((hashtable_[index] && key != hashtable_[index]->GetKey()) || \
				 (!hashtable_[index] && lazymark[index] == true)){
		//线性试探
		index = (index + 1) % capacity_;
	}
	return index;
}

//冲突后查找为空的位置
int Hashtable::probe4Free(const int& key){
	int index = key % capacity_;
	while(hashtable_[index]){
		//线性试探查找一个为空的位置
		index = (index + 1) % capacity_;	
	}
	return index;
}

//当装填因子大于0.5时rehash
void Hashtable::rehash(){
	//备份现有哈希表数据
	int old_capacity = capacity_;
	Entry** old_hashtable = hashtable_;
	//扩容为之前两倍，并清零组中元素数量
	capacity_ = 2 * capacity_;
	size_ = 0;
	//申请新的两倍空间
	hashtable_ = new Entry*[capacity_];;
	memset(hashtable_,0,sizeof(Entry*) * capacity_);
	//清除旧的懒惰标记,并重新申请
	delete [] lazymark;
	lazymark = new bool[capacity_];
	memset(lazymark, 0, sizeof(bool) * capacity_);
	//拷贝旧数据
	for(int i = 0; i < old_capacity; i++){
		if(old_hashtable[i]){
			put(old_hashtable[i]->GetKey(), old_hashtable[i]->GetValue());	
		}	
	}
	//释放旧表
	for(int i = 0; i < old_capacity; i++){
		if(old_hashtable_[i]){
			delete old_hashtable_[i];
		}
	}
	delete [] old_hashtable;
}

//添加(key,value)对
bool Hashtable::put(int key, int value){
	//相同key不重复插入
	if(hashtable_[probe4Hit(key)]) return false;
	int free_to_insert = probe4Free(key);
	//插入新词条,这里有锁保护多线程安全
	Entry* new_entry = new Entry();
	new_entry->WriteEntry(key,value);
	hashtable_[free_to_insert] = new_entry;
	size_++;
	//装填因子大于百分之五十rehash
	if(size_ > capacity_ / 2) rehash();
	return true;
}

//查询为key的value,若存在则返回指向value的指针，若不存在则返回NULL
shared_ptr<int> Hashtable::get(int key){
	int index = probe4Hit(key);
	if(hashtable_[index]){
		shared_ptr<int> value(new int(hashtable_[index]->GetValue()));
		return value;
	}
	return NULL;
}

//删除为key的词条
bool Hashtable::remove(int key){
	int index = probe4Hit(key);
	//不存在则无法删除
	if(!hashtable_[index]) return false;
	delete hashtable_[index];
	hashtable_[index] = NULL; 
	lazymark[index] = true;
	size_--;
	return true;
}

//析构函数释放哈希表中的对象、哈希表以及懒惰删除标记
Hashtable::~Hashtable(){
	for(int i = 0; i < capacity_; i++){
		if(hashtable_[i]){
			delete hashtable_[i];
		}
	}
	delete [] hashtable_;
	delete [] lazymark;
}





