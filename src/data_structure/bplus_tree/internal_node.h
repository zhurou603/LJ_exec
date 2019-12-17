#ifndef INTERNAL_NODE_H
#define INTERNAL_NODE_H

#include"definition.h"
#include"basic_node.h"
#include<vector>
#include<utility>

using namespace std;

//继承基本结点
class InternalNode : public BasicNode {
 public:
  using InternalType = pair<KeyType,BasicNode*>;
  
  bool is_leaf() const{
    return false;
  }

  //找到最后一个小于等于的key
  BasicNode* search_for_last_lessequal(KeyType key);

 private:
	//内部结点组织一个vector用来操作
 	vector<InternalType> inter_nodes;
};
#endif
