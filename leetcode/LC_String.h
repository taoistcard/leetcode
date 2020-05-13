#pragma once
#include "LC_Base.h"

namespace LeetCode
{
	class Solution14 {
	public:
		string longestCommonPrefix(vector<string>& strs) {
			if (strs.empty())
				return "";
			int len = 0;
			while (true)
			{
				if (strs[0].length() <= len)
					break;
				bool pub = true;
				for (int i = 1; i < strs.size(); i++)
				{
					if (strs[i].length() <= len)
					{
						pub = false;
						break;
					}
					if (strs[i][len] != strs[0][len])
					{
						pub = false;
						break;
					}
				}
				if (!pub)
					break;
				++len;
			}
			return strs[0].substr(0, len);
		}
		static void test()
		{
			Solution14 sol;
			std::vector<std::string> strs;
			std::cout << "输入字符串，以@结尾" << std::endl;
			while (true)
			{
				while (true)
				{
					std::string s;
					std::cin >> s;
					if (s == "@")
						break;
					strs.push_back(s);
				}
				std::cout << "最长公共前缀:" << sol.longestCommonPrefix(strs) << std::endl;
			}
		}
	};

	REG_TEST(14);
}