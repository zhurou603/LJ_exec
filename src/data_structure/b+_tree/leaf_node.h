#ifndef LEAF_NODE_H
#define LEAF_NODE_H

#include"definition.h"
#include"node.h"
#include<vector>
#include<utility>
#include"record.h"
#include<iostream>
#include"inter_node.h"

using namespace std;

//叶结点
class LeafNode : public Node {
 public:
  //vector存储的Key和实际的记录Record
  using Pair = pair<Key,shared_ptr<Record>>;
  //构造函数
  LeafNode(int d) : Node(d), next_(nullptr) {}
  LeafNode(int d, shared_ptr<Node> p) : Node(d, p), next_(nullptr) {}
	virtual ~LeafNode(){}
  //可读接口
  bool is_leaf() const{
    return true;
  }
  //查找为key的记录是否存在
  virtual shared_ptr<Record> search(Key key);
  //返回最大容量
  int max_size() const;
  //返回最小容量
  int min_size() const;
  //打印叶子结点
  void printleaf() const;
  //获取next结点
  shared_ptr<LeafNode> get_next() const;
  //拿到第一个元素，方便split
  Key first_key() const;
  int get_size() const;
  
  //可写接口
  //向leaves创建记录并添加,返回当前size以便调整
  virtual int create_and_append(Key key, Value value);
  //在合适的位置插入一个pair
  virtual void insert(Key key, shared_ptr<Record> record);
  //类似链表下一指针
  void set_next(shared_ptr<LeafNode> node);
  //移动后半部分到新的结点
  virtual void move_half_to(shared_ptr<LeafNode> receiver);
  //拷贝
  virtual void copy_half_from(const vector<Pair>& origin_keys);
  //删除key对应Record,返回删除后size
  int remove_record(Key key);


  /*//转移所有数据到receiver
  void move_all_to(shared_ptr<LeafNode> receiver, int pos);
  //从指定keys拷贝数据
  void copy_all_from(vector<Pair>* data);
    void move_first_to_end_of(shared_ptr<LeafNode> node);
  void move_last_to_head_of(shared_ptr<LeafNode> node);
  void copy_first_from(Pair first);
  void set_key_pos(int pos, Key key);
  void copy_last_from(Pair last, int node_pos);
  void move_last_to_head_of(shared_ptr<LeafNode> node, int node_pos);*/


 protected:
  vector<Pair> leaves_;
  //底层链表结构
  shared_ptr<LeafNode> next_;
};

#endif
