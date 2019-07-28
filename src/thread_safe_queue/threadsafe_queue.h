#include<mutex>
#include<memory>
#include<queue>
#include<condition_variable>

using namespace std;

template<typename T>
class threadsafe_queue{
 public:
	threadsafe_queue(){};
	threadsafe_queue(const threadsafe_queue&);
	threadsafe_queue& operator=(const threadsafe_queue&) = delete;
	void push(T new_value);
	shared_ptr<T> try_pop();
	shared_ptr<T> wait_and_pop();
	bool empty() const;
 
 private:
	mutable mutex mut;
	queue<T> data_queue;
	condition_variable data_cond;
};
