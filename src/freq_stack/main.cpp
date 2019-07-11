#include<gtest/gtest.h>
#include"GTEST.h"
#include"FreqStack.h"

//在push之前先更新x的出现频率
//压入栈后判断最大频率是否发生变化并更新

void FreqStack::push(int x){
	freq_[x]++;
  group_[freq_[x]].push(x);
  if (freq_[x] > max_freq_) max_freq_ = freq_[x];
}

//取出最大频率下最靠近栈顶的整数,并更新该整数的频率
//若该最大频率已经无数据，则最大频率减１

int FreqStack::pop(){
	int current_int;
	if (group_[max_freq_].empty()) return -1;
  current_int = group_[max_freq_].top();
  group_[max_freq_].pop();
  freq_[current_int]--;
  if (group_[max_freq_].empty()) max_freq_--;
  return current_int;
}

TEST(FreqStack,push_and_pop){
	FreqStack fstack = FreqStack();
	//测试pop空栈，应返回-1
	ASSERT_EQ(fstack.pop(), -1);
	int data[10] = {65, 546, 1, 5556, 546, 65, 4657, 65, 45, 4657};
	for(int i = 0; i < 10; i++){
		fstack.push(data[i]);
	}
	//push后最大频率应为出现次数最多的元素频率
	ASSERT_EQ(fstack.max_freq_, 3) << "max freq doesn't match";
	//频率为１的栈
	vector<int> freq_1_vector = {65,546,1,5556,4657,45};	
	stack<int> freq_1;
	for(int i = 0; i < freq_1_vector.size(); i++){
		freq_1.push(freq_1_vector[i]);
	}
	//频率为2的栈
	vector<int> freq_2_vector = {546,65,4657};	
	stack<int> freq_2;
	for(int i = 0; i < freq_2_vector.size(); i++){
		freq_2.push(freq_2_vector[i]);
	}
	//频率为3的栈
	stack<int> freq_3;
	freq_3.push(65);
	//测试FreqStack各频率栈是否正确
	ASSERT_EQ(fstack.group_[1], freq_1) << "freq1 wrong";
	ASSERT_EQ(fstack.group_[2], freq_2) << "freq2 wrong";
	ASSERT_EQ(fstack.group_[3], freq_3) << "freq3 wrong";
	//测试pop操作后是否正确
	fstack.pop();
	freq_3.pop();
  fstack.pop();
	freq_2.pop();
	ASSERT_EQ(fstack.group_[2], freq_2) << "pop2 wrong";
	ASSERT_EQ(fstack.group_[3], freq_3) << "pop3 wrong";
}

int main(int argc, char** argv){
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

