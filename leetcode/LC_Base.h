#pragma once
#include "std_head.h"
#include "json/json.h"

#define REG_TEST(N) static bool reg_##N = (reg_test_func(N, std::bind(&Solution##N::test)))

namespace LeetCode
{
	struct ListNode {
		int val;
		ListNode *next;
		ListNode(int x) : val(x), next(NULL) {}
	};

	static std::map<int, std::function<void()>> register_test_funcs;
	static bool reg_test_func(int id, std::function<void()> func)
	{
		if (register_test_funcs.count(id) == 1)
			return false;
		register_test_funcs[id] = func;
		return true;
	}

	static void test()
	{
		while (true)
		{
			int id;
			std::cout << "选择要执行的测试程序:" << std::endl;
			std::cin >> id;
			if (id == 0)
				break;
			if (register_test_funcs.count(id) == 1)
			{
				register_test_funcs[id]();
			}
			else
			{
				std::cout << "test func not found : " << id << std::endl;
			}
		}

	}
}