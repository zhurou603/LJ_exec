#include<gtest/gtest.h>
#include"bst_serialize_v1.h"
#include<random>

//测试序列化及反序列化int64_t
TEST(encode_int, zero_positive){
	vector<int64_t> test = {-11564,0,-568,4878941,56135,568,45};
	vector<int64_t> test_result;	
	for(int i = 0; i < test.size(); i++){
		string result = encode_int(test[i]);
		test_result.push_back(decode_int(result.c_str()));
	}
	//should be equal
	ASSERT_EQ(test, test_result) << "序列化整数出错";
}


TEST(decode_vector, zero_positive){
  vector<int64_t> test = {45,0,45678,154687,54612478};
	string test_result = encode_vector(test);
  ASSERT_EQ(test, decode_vector(test_result.data(),test_result.length()));
}

//测试序列化和反序列化二叉树
TEST(serialize_deserialize, less_than_64){
  //构造1-15的满二叉树,结点值为-100000～100000的随机数
  default_random_engine random;
  uniform_int_distribution<signed> range(-100000,100000);
  for(int i = 0; i <= 13; i++){
    int number = pow(2,i) - 1;
    int64_t data[number];
    for(int j = 0; j < number; j++){
      int64_t value = range(random);
      data[j] = value; 
    }
    shared_ptr<TreeNode> root = build(data, number, 0);
    //测试二叉树的前序遍历
    vector<int64_t> pre_root;
    printpre(pre_root, root);
    //测试经过序列化与反序列化后的二叉树的前序遍历
    shared_ptr<TreeNode> result = deserialize(serialize(root));
    vector<int64_t> pre_test;
    printpre(pre_test, result);
    ASSERT_EQ(pre_root, pre_test);
  }

}

int main(int argc, char** argv){
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

