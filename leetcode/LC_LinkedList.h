#pragma once
#include "LC_Base.h"
namespace LeetCode
{
	ListNode* createList()
	{
		ListNode* pHead = nullptr;
		ListNode* pLast = nullptr;
		int val = 0;
		while (1)
		{
			std::cin >> val;
			if (val == 0)
				break;
			ListNode* pNode = new ListNode(val);
			if (pLast == nullptr)
			{
				pHead = pNode;
				pLast = pNode;
			}
			else
			{
				pLast->next = pNode;
				pLast = pLast->next;
			}
		}
		return pHead;
	}
	void destroyList(ListNode* pHead)
	{
		while (pHead)
		{
			ListNode* pNext = pHead->next;
			delete pHead;
			pHead = pNext;
		}
	}

	void printList(ListNode* pHead)
	{
		while (pHead)
		{
			std::cout << pHead->val << '\t';
			pHead = pHead->next;
		}
		std::cout << std::endl;
	}
	/**
	* Definition for singly-linked list.
	* struct ListNode {
	*     int val;
	*     ListNode *next;
	*     ListNode(int x) : val(x), next(NULL) {}
	* };
	*/
	class Solution24 {
	public:
		static void test()
		{
			Solution24 sol;
			ListNode* pHead = createList();
			printList(pHead);
			pHead = sol.swapPairs(pHead);
			printList(pHead);
			destroyList(pHead);
		}
		ListNode* swapPairs(ListNode* head) {
			ListNode* pTmp = new ListNode(0);
			pTmp->next = head;
			
			ListNode* pHead = NULL;
			ListNode* pCurNode = pTmp;
			while (1)
			{
				if (pCurNode == NULL)
					break;
				if (pCurNode->next == NULL || pCurNode->next->next == NULL)
					break;

				ListNode* pNext = pCurNode->next;
				pCurNode->next = pNext->next;
				pNext->next = pCurNode->next->next;
				pCurNode->next->next = pNext;

				pCurNode = pNext;
			}
			pHead = pTmp->next;
			delete pTmp;
			return pHead;
		}
	};
	static bool reg_24 = reg_test_func(24, std::bind(&Solution24::test));
	//REG_TEST(24);
}