#ifndef MEMORY
#include<memory>
#endif

#ifndef MUTEX
#include<mutex>
#endif

using namespace std;

//词条元素,提供基本的lock_guard保护
//读操作：获取key,value可多人读
//写操作:新增值或修改值提供lock_guard保护
class Entry{
 public:
	//构造函数只做默认初始化
	Entry(){
		key_ = 0;
		value_ = 0;	
	}
	int GetKey() { return key_; }
	int GetValue() { return value_; }
	void WriteEntry(int k, int v){
		lock_guard<mutex> lock(m_);
		key_ = k;
		value_ = v;
	}
		  
 private:	
	int key_;
	int value_;
	mutable mutex m_;	
};
