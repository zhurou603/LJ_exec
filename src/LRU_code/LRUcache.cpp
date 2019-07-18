#include<iostream>
#include<vector>
#include<gtest/gtest.h>
#include"GTEST.h"
#include"LRUCache.h"

//构造函数创建容量为capacity的cache；
template <class T>
LRUCache<T>::LRUCache(T capacity){
	capacity_ = capacity;
}

//O(1)时间返回hash table中的（key）；
//如果key不存在，那么查询失败
//如果存在那么要将该值从list中的任意位置移动到首部
template <class T>
T LRUCache<T>::get(T key){
	const auto it = m_.find(key);
	if(it == m_.cend()) return -1;
	cache_.splice(cache_.begin(), cache_, it->second);
	return it->second->second;
}

//如果key已经在hash table中，那么要对value进行更新,并且移动到首部
//如果key不在且已经达到capacity，要删除最末尾的k-v对
//以上情况均不是则将此k-v插入到cache最前端,经过上述步骤，一定有剩余容量
template <class T>
void LRUCache<T>::put(T key, T value){
	const auto it = m_.find(key);
	if(it != m_.cend()){
		it->second->second = value;
		cache_.splice(cache_.begin(), cache_, it->second);
		return;
	}
	if(cache_.size() == capacity_){
		const auto& node = cache_.back();
		m_.erase(node.first);
		cache_.pop_back();
	}
	cache_.emplace_front(key,value);
	m_[key] = cache_.begin();
}

//测试LRUCache put函数
TEST(LRUCache, put){
	int capacity = 7;
	int key[capacity] = {3,6,1,2,4,10,5};
	int value[capacity] = {2,6,4,5,8,1,11};	
	LRUCache<int> l = LRUCache<int>(capacity);
	for (int i = 0; i < capacity; i++) {
		l.put(key[i],value[i]);
	}
	list<pair<int,int>>::iterator it;
	int index = capacity - 1;
	//测试put函数是否将(key,value)对存入cache;
	for (it = l.cache_.begin(); it != l.cache_.end(); it++) {
		ASSERT_EQ((*it).first,key[index]);
		ASSERT_EQ((*it).second,value[index]);
		index--;	
	}
}

//测试LRUCache get函数
TEST(LRUCache, get){
	int capacity = 7;
	int key[capacity] = {123,6,1,2,4,10,5};
	int value[capacity] = {2,566,4,5,8,1,11};	
	LRUCache<int> l = LRUCache<int>(capacity);
	for (int i = 0; i < capacity; i++) {
		l.put(key[i],value[i]);
	}
	l.put(323,5456);
	int result_key[capacity] =   {6,1,2,4,10,5,323};
	int result_value[capacity] = {566,4,5,8,1,11,5456};
	//测试cache满后是否置换出最久未用的元素
	ASSERT_EQ(l.get(123), -1) << "when cache is full, result wrong";
	//测试cache中的值是否符合预期
	list<pair<int,int>>::iterator it;
	int index = capacity - 1;
	for (it = l.cache_.begin(); it != l.cache_.end(); it++) {
		ASSERT_EQ((*it).first,result_key[index]);
		ASSERT_EQ((*it).second,result_value[index]);
		index--;	
	}
}

int main(int argc, char** argv){
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
