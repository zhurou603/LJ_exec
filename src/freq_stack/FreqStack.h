#include<unordered_map>
#include<stack>
using namespace std;

//模拟一个类似栈的数据结构
//支持两个操作
//push(int x) 将整数推入栈中
//pop()　移除并返回出现最频繁的元素，若频率相同，则返回最接近栈顶的元素
//三个private成员变量。freq_维护某一整数出现的频率，group_表示某一频率下有哪些整数
//max_freq_表示当前出现的最大频率为多少

class FreqStack {
 public:
  void push(int x);
  int pop();
	FreqStack() : max_freq_(0) {}

 private:
  unordered_map<int, int> freq_;
  unordered_map<int,stack<int>> group_;
  int max_freq_;
};
