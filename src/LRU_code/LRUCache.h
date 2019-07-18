#include<unordered_map>
#include<list>

using namespace std;

template <typename T>
class LRUCache{
 public:	
	LRUCache(T capacity);
	T get(T key);
	void put(T key, T value);

 private:
	T capacity_;
	list<pair<T,T>> cache_;
	//unordered_map<T, list<pair<T,T>>::iterator> m_;
  //problem
  unordered_map<T, list<pair<int,int>>::iterator> m_;
};
