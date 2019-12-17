#ifndef LEAF_NODE_H
#define LEAF_NODE_H

#include"basic_node.h"
#include<vector>
#include<utility>
#include"definition.h"
#include"record.h"

using namespace std;

class LeafNode : public BasicNode {
 public:
	using LeafType = pair<KeyType,Record*>;

  //构造函数
  //利用共有的BasicNode构造,并且初始化指针
  LeafNode(int degree) : BasicNode(degree), leaf_next(nullptr) {}

  //判断是否是叶子结点
  bool is_leaf() const{
    return true;
  }

  //获取最大允许size
  int max_size() const;

  //向leaf_node插入record
  void insert(KeyType key, Record* record);

  //向当前leaf_node创建并且插入一条record,返回当前容量
  int create_record_insert(KeyType key, ValueType value);

  //查找是否有对应记录
  Record* search_record(KeyType key) const;

 private:
	//本来是要指向磁盘文件
	vector<LeafType> leaf_nodes;
	//还要维护一个类似链表的结构
	LeafNode* leaf_next;

};

#endif
