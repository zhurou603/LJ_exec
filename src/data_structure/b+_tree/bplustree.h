#ifndef BPLUSTREE_H
#define BPLUSTREE_H

#include"definition.h"
#include"disk_node.h"
#include"node.h"
#include"leaf_node.h"
#include"inter_node.h"
#include<queue>
#include<set>

const int DEFAULT_DEGREE = 3;

class BplusTree{
 public:
  //构造函数
	//需要初始化leave中存储key value的二进制文件
  BplusTree(int d = DEFAULT_DEGREE) : tree_degree_(d), root_(nullptr), leave_file("./data/leaves_key_value.bin"){
		open_file("wb+");
	}
  //外部接口
  void insert(Key key, Value value);
  void remove(Key key);
  shared_ptr<Record> search(Key key);

  //遍历
  void print_all();
  //BFS
  void bfs_key(vector<Key>* result);

 private:
  //空树增加一个结点
  void insert_empty_tree(Key key, Value value);
  //插入到叶子结点
  void insert_to_leaf(Key key, Value value);
  //split
  template <typename T>
  shared_ptr<T> split(shared_ptr<T> node);
  //叶子结点split后把key更新到parent
  void insert_key_to_parent(shared_ptr<Node> old_node, Key key, shared_ptr<Node> new_node);

  int tree_degree_;
  shared_ptr<Node> root_;

	//磁盘信息
	const string leave_file;
	FILE* leave_fp;

	bool open_file(const char* mode = "rb+"){
		leave_fp = fopen(leave_file.c_str(), mode);
		if(!leave_fp){
			cout << "打开" << leave_file << "文件失败" << endl;
			return false;
		}
		return true;
	}
	//记录一次操作中分配了内存的结点
	set<shared_ptr<DiskNode>> used;
};

#endif
