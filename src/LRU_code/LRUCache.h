#include<unordered_map>
#include<list>

using namespace std;

class LRUCache{

public:	
	LRUCache(int capacity);
	
	int get(int key);

	void put(int key, int value);

private:
	int capacity_;
	list<pair<int,int>> cache_;
	unordered_map<int, list<pair<int,int>>::iterator> m_;
};
