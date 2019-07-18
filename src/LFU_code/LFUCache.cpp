#include<iostream>
#include<gtest/gtest.h>
#include"GTEST.h"
#include"LFUCache.h"

//get函数查询LFU中key的value，不存在返回-1
//若存在则需要访问Node,并返回value
//时间复杂度O(1)
template<typename T>
T LFUCache<T>::get(T key){
	auto it = cache_.find(key);
	if(it == cache_.cend())	return -1;
	visit(it->second);
	return (it->second).value;
}

//put函数将(key,value)对存入LFUCache
//时间复杂度O(1)
template<typename T>
void LFUCache<T>::put(T key, T value){
	if(capacity_ == 0) return;
	auto it = cache_.find(key);
	//若已经存在当前key则更新值，并访问Node	
	if(it != cache_.cend()){
		it->second.value = value;
		visit(it->second);
		return;
	}
	//如果cache满
	if(cache_.size() == capacity_){
		//删除最少使用频率中最久未被使用node
		const T key_should_del = freq_list_[min_freq_].back();
		freq_list_[min_freq_].pop_back();
		cache_.erase(key_should_del);
	}
	//添加一个node
	min_freq_ = 1;
	freq_list_[min_freq_].push_front(key);
	cache_[key] = {key, value, 1, freq_list_[1].cbegin()};
}

//访问Node
//时间复杂度O(1)
template<typename T>
void LFUCache<T>::visit(Node& node){
	const T pre_freq = node.freq;
	const T freq = ++(node.freq);
	//将访问前的频率记录删除
	freq_list_[pre_freq].erase(node.it);
	//若删除后当前频率链表为空，且为最小频率则删除该链表,并更新最小频率
	if(freq_list_[pre_freq].empty() && pre_freq == min_freq_){
		freq_list_.erase(pre_freq);
		++min_freq_;
	}
	//同时更新Node以及链表
	freq_list_[freq].push_front(node.key);
	node.it = freq_list_[freq].cbegin();
}

//同时测试put和get函数
TEST(LFUCache, put_and_get){
	LFUCache<int> lfu = LFUCache<int>(6);
	int key[6] = {157,56,45,4,3,7898};
	int value[6] = {56,44,78,56,341,6};
	for(int i = 0; i < 6; i++){
		lfu.put(key[i], value[i]);
	}
	//put六对值后，访问频率均应为１且最后一个key为最早访问的key
	ASSERT_EQ(lfu.freq_list_[1].back(),157);
	ASSERT_EQ(lfu.min_freq_, 1);
	//LFUCache满后，put元素，应删除最小频率中最末尾元素
	lfu.put(2,10);
	ASSERT_EQ(lfu.get(157), -1);
	//get操作对key的频率进行自增,查看增加后对应频率的key是否正确
	lfu.get(45);
	lfu.get(56);
	lfu.get(45);
	ASSERT_EQ(lfu.freq_list_[3].back(),45);
	ASSERT_EQ(lfu.freq_list_[2].back(),56);
}

int main(int argc, char** argv){
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
