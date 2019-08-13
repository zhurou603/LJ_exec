#include<mutex>
#include<memory>
#include<queue>
#include<condition_variable>

using namespace std;

template<typename T>
class ThreadsafeQueue{
 public:
	ThreadsafeQueue(){};
	ThreadsafeQueue(const ThreadsafeQueue&);
	ThreadsafeQueue& operator=(const ThreadsafeQueue&) = delete;
	void push(T new_value);
	shared_ptr<T> try_pop();
	shared_ptr<T> wait_and_pop();
	bool empty() const;
 
 private:
	mutable mutex mut;
	queue<T> data_queue;
	condition_variable data_cond;
};
