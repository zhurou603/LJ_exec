#ifndef ENTRY
#include"entry.h"
#endif

//多线程哈希表结构
class Hashtable{
 public:
	Hashtable();
	int size() const {return size_;}
	bool put(int,int);
	shared_ptr<int> get(int key);
	bool remove(int key);
	~Hashtable();
 
 protected:
	int probe4Hit(const int& key);
	int probe4Free(const int& key);
	void rehash();

 private:
	Entry** hashtable_;
	//先定一个素数
	int capacity_ = 113;
	int size_;
	bool* lazymark;
};
