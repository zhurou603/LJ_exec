#ifndef NODE_H
#define NODE_H

#include"definition.h"

const Key DUMMY_KEY{-1};

//基本结点
//只需要知道两个事情，一个是它的degree，一个是它的父结点是谁
class Node{
 public:
	Node(int d) : degree_(d), parent_(nullptr) {}
	Node(int d, Node* p) : degree_(d), parent_(p) {}
  //虚函数需要子类重新定义
  virtual bool is_leaf() const{
    return false;
  }
  //设置父结点
  void set_parent(Node* new_parent){
    parent_ = new_parent;
  }
  //拿到父结点，const保护
  Node* get_parent() const{
    return parent_;
  }
  //protected供子类访问但对外部用户不可见
 protected:
	int degree_;
	Node* parent_;
};

#endif
