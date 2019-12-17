#ifndef BASIC_NODE_H
#define BASIC_NODE_H

#include"definition.h"

//基本结点
class BasicNode{
 public:
  //构造函数
  BasicNode(int degree) : node_degree(degree), child(nullptr) {} 

  //判断是否是叶子结点
  bool is_leaf() const;

  //获取degree
  int get_degree() const{
    return node_degree;
  }

 private:
	//每个结点的容量
	int node_degree;
	//孩子
	BasicNode* child;
};

#endif
