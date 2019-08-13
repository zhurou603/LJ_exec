#include<exception>
#include<memory>
#include<stack>
#include<mutex>

using namespace std;

struct empty_stack:exception{
	const char* what() const throw();
};

//多线程安全栈,对std::stack中的push,pop,empty操作提供多线程安全的保护
template<typename T>
class ThreadsafeStack{
 public:
	ThreadsafeStack();
	//拷贝构造函数，在进行拷贝时进行互斥保护
	ThreadsafeStack(const ThreadsafeStack&);
	//用=进行赋值操作不被允许
	ThreadsafeStack& operator=(const ThreadsafeStack&) = delete;
	//push时保护data_栈互斥
	void push(T new_value);
	//进行pop操作时保护data_互斥
	//为空时不能进行pop操作
	//返回被pop()元素的指针
	//合并了top()和pop()接口，防止top()的元素被处理多次
	shared_ptr<T> pop();
	void pop(T& value);
	//查询栈是否为空时确保其被保护
	bool empty() const;
 
 private:
	stack<T> data_;
	mutable mutex m_;		
};
