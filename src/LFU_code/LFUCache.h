#include<unordered_map>
#include<list>

using namespace std;

struct Node{
	int key;
	int value;
	int freq;
	list<int>::const_iterator it;
};

template<typename T>
class LFUCache{
 public:
	//构造函数
	LFUCache(T capacity): capacity_(capacity), min_freq_(0){}
	T get(T key);
	void put(T key, T value);

 private:
	unordered_map<T, Node> cache_;
	unordered_map<T, list<T>> freq_list_;
	T min_freq_;
	T capacity_;
	void visit(Node& node);
};
