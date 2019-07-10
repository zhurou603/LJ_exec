#include<iostream>
#include<gtest/gtest.h>

using namespace std;

struct ListNode{
	int val;
	ListNode* next;
	ListNode(int v) : val(v), next(NULL) {};
};

/*利用两个指针，快和慢指针，快指针每次循环跳两个结点，慢指针每次跳一个结点
若链表无环，则快指针最终为空，若有环则两个指针一定相遇
且快指针走过的结点数为慢指针两倍
*/
bool hasCycle(ListNode* head){
	ListNode* fast = head;
	ListNode* slow = head;
	while(fast){
		if(!fast->next) return false;
		fast = fast->next->next;
		slow = slow->next;
		if(fast == slow) {
			return true;
		}
	}
	return false;
}

//测试只有一个结点，结果应要为无环
TEST(hasCycle,case1){
	ListNode* head = new ListNode(0);
	ASSERT_EQ(hasCycle(head), false) << "single element should has no loop";
}

//测试有六个结点的无环链表
TEST(hasCycle,case2){
	int element[5] = {200, 55, 6, 47, 3};
	ListNode* head = new ListNode(0);
	ListNode *pnew, *ptemp;
	ptemp = head;
	for(int i = 0; i < 5; i++){
		pnew = new ListNode(element[i]);
		ptemp->next = pnew;
		ptemp = pnew;
	}
	ASSERT_EQ(hasCycle(head), false) << "a normal linked list should has no cycle";
}

//测试含８个结点的有环链表
TEST(hasCycle, cast3){
	int element[7] = {1234, 51234, 6, 47, 3, 66, 4213};
	ListNode* head = new ListNode(0);
	ListNode *pnew, *ptemp, *cycle_node;
	ptemp = head;
	int cycle_pos = 2;
	for(int i = 0; i < 7; i++){
		pnew = new ListNode(element[i]);
		ptemp->next = pnew;
		ptemp = pnew;
		if(i == cycle_pos){
			cycle_node = pnew;
		}
	}
	ptemp->next = cycle_node;　//将尾结点与设定的cycle_node相连，形成有环链表
	ASSERT_EQ(hasCycle(head), true) << "linked list which has cycle test wrong";
}

int main(int argc, char** argv){
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
