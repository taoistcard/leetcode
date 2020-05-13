﻿#pragma once
#include "LC_Base.h"
namespace LeetCode
{
	class Solution5 {
	public:
		/*
		给定一个字符串 s，找到 s 中最长的回文子串。你可以假设 s 的最大长度为 1000。

		示例 1：
		输入: "babad"
		输出: "bab"
		注意: "aba" 也是一个有效答案。

		示例 2：
		输入: "cbbd"
		输出: "bb"

		来源：力扣（LeetCode）
		链接：https://leetcode-cn.com/problems/longest-palindromic-substring
		著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
		*/
		/*
			动态规划
		*/
		static string longestPalindrome2(const string& s)
		{
			if (s.empty())
				return "";
			std::vector<std::vector<bool>> flags;
			flags.resize(s.size());
			int l = 0, c = 0;

			for (unsigned int i = 0; i < flags.size(); i++)
			{
				flags[i].resize(s.length());
				flags[i][i] = true;
				if (c < 1)
				{
					l = i;
					c = 1;
				}
				if (i + 1 < s.length() && s[i] == s[i + 1])
				{
					flags[i][i + 1] = true;
					if (c < 2)
					{
						l = i;
						c = 2;
					}
				}
			}
			
			for (unsigned int len = 3; len <= s.length(); len++)
			{
				for (unsigned int i = 0; i + len - 1 < s.length(); i++)
				{
					unsigned int j = i + len - 1;
					if (s[i] == s[j] && flags[i + 1][j - 1])
					{
						flags[i][j] = true;
						if (c < len)
						{
							l = i;
							c = len;
						}
					}
				}
			}
			return s.substr(l, c);
		}

		/*
			中心点往两边展开
		*/
		static string longestPalindrome(const string& s) {
			if (s.size() <= 1)
				return s;
			unsigned int b, e;
			b = e = -1;

			auto check_fun = [](unsigned int& left, unsigned int&right, const std::string& s){
				while (left != -1 && right < s.size())
				{
					if (s[left] == s[right])
					{
						left--;
						right++;
					}
					else
					{
						break;
					}
				}
			};


			for (unsigned int k = 0; k < s.size(); k++)
			{
				unsigned int i, j;
				i = j = -1;

				i = k;
				j = k;
				check_fun(i, j, s);


				i++;
				j--;

				if (k + 1 < s.size() && s[k] == s[k + 1])
				{
					unsigned int ti = k;
					unsigned int tj = k + 1;
					check_fun(ti, tj, s);
					ti++;
					tj--;
					if (tj - ti > j - i)
					{
						i = ti;
						j = tj;
					}
				}


				if (b < 0)
				{
					b = i;
					e = j;
				}
				else
				{
					if (e - b < j - i)
					{
						b = i;
						e = j;
					}
				}
			}

			return s.substr(b, e - b + 1);
		}

		static void test()
		{
			Solution5 sol;
			while (true)
			{
				std::string s;
				std::cout << "输入字符串:";
				std::cin >> s;
				if (s == "q")
					break;
				std::cout << "回文字符串为：";
				std::cout << sol.longestPalindrome2(s) << std::endl;
			}
		}
	};
	REG_TEST(5);

	class Solution10 {
	public:
		/*
		给你一个字符串 s 和一个字符规律 p，请你来实现一个支持 '.' 和 '*' 的正则表达式匹配。

		'.' 匹配任意单个字符
		'*' 匹配零个或多个前面的那一个元素
		所谓匹配，是要涵盖 整个 字符串 s的，而不是部分字符串。

		说明:

		s 可能为空，且只包含从 a-z 的小写字母。
		p 可能为空，且只包含从 a-z 的小写字母，以及字符 . 和 *。
		示例 1:

		输入:
		s = "aa"
		p = "a"
		输出: false
		解释: "a" 无法匹配 "aa" 整个字符串。
		示例 2:

		输入:
		s = "aa"
		p = "a*"
		输出: true
		解释: 因为 '*' 代表可以匹配零个或多个前面的那一个元素, 在这里前面的元素就是 'a'。因此，字符串 "aa" 可被视为 'a' 重复了一次。
		示例 3:

		输入:
		s = "ab"
		p = ".*"
		输出: true
		解释: ".*" 表示可匹配零个或多个（'*'）任意字符（'.'）。
		示例 4:

		输入:
		s = "aab"
		p = "c*a*b"
		输出: true
		解释: 因为 '*' 表示零个或多个，这里 'c' 为 0 个, 'a' 被重复一次。因此可以匹配字符串 "aab"。
		示例 5:

		输入:
		s = "mississippi"
		p = "mis*is*p*."
		输出: false

		来源：力扣（LeetCode）
		链接：https://leetcode-cn.com/problems/regular-expression-matching
		著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
		*/
		static bool isMatch1(string s, string p) {
			//cout << s << " | " << p << endl;
			if (p.empty())
			{
				return s.empty();
			}
			if ('*' == p[0])
				return false;
			if (p.size() == 1)
			{
				if (s.size() != 1)
					return false;
				if (s[0] != p[0] && p[0] != '.')
					return false;
				return true;
			}

			//for (unsigned int match_begin = 0; match_begin < s.size(); match_begin++)
			{
				bool found = false;
				unsigned int s_i = 0;
				unsigned int p_i = 0;
				while (1)
				{
					if (s_i == s.size() && p_i == p.size())
					{
						break;
					}
					else if (s_i == s.size())
					{
						if ('*' == p[p_i])
						{
							if (p[p_i - 1] == '*')
							{
								break;
							}
							else
							{
								p_i++;
								continue;
							}
						}
						else
						{
							if (p_i + 1 == p.size())
							{
								break;
							}
							else
							{
								if (p[p_i + 1] == '*')
								{
									p_i++;
									continue;
								}
								else
								{
									break;
								}
							}
						}
					}
					else if (p_i == p.size())
					{
						break;
					}

					if ('*' == p[p_i])
					{
						if (p[p_i - 1] == '*')
						{//"**"，无法匹配
							return false;
						}
						unsigned int match_cnt = 0;
						unsigned int max_match_cnt = s.size() - s_i;
						char match_ch = p[p_i - 1];

						std::string sub_p;
						if (p_i + 1 < p.size())
						{
							sub_p = p.substr(p_i + 1, p.size() - p_i - 1);
						}
						bool is_match = false;
						while (match_cnt <= max_match_cnt)
						{
							//当前字符匹配成功，才会检查剩下的子字符串
							bool do_check = true;
							if (match_cnt > 0)
							{//匹配次数大于0时，要检查字符是否匹配
								if (match_ch != '.' && s[s_i + match_cnt - 1] != match_ch)
								{
									do_check = false;
									break;
								}
							}
							if (!do_check)
								return false;
							std::string sub_s = s.substr(s_i + match_cnt, s.size() - s_i - match_cnt);
							is_match = isMatch1(sub_s, sub_p);
							if (is_match)
							{
								break;
							}
							else
							{
								match_cnt++;
							}
							//if (match_ch == '.' || s[s_i] == match_ch)
							//{
							//	s_i++;
							//	match_cnt++;
							//}
							//else
							//{
							//	break;
							//}
						}
						if (is_match)
						{
							s_i += match_cnt;
							p_i++;
						}
						else
						{
							return false;
						}
					}
					//else if ('.' == p[p_i])
					//{
					//	s_i++;
					//	p_i++;
					//}
					else
					{
						//当前是普通字符,需要考虑下一位是否是通配符，如果是，调到通配符处理
						if (p_i == p.size() - 1)
						{//模式串到了最后一位，不可能再有通配符了
							if (s[s_i] != p[p_i] && p[p_i] != '.')
							{//普通字符匹配失败
								break;
							}
							s_i++;
							p_i++;
						}
						else
						{//模式串没到最后一位
							if (p[p_i + 1] == '*')
							{
								p_i++;
							}
							else
							{
								if (s[s_i] != p[p_i] && p[p_i] != '.')
								{//普通字符匹配失败
									break;
								}
								s_i++;
								p_i++;
							}
						}
					}
				}
				if (p_i == p.size() && s_i == s.size())
					return true;
			}

			return false;

		}

		static bool isMatch2(string s, string p)
		{
			return isMatch2(s.c_str(), p.c_str());
		}

		static bool isMatch2(const char* s, const char* p)
		{
			if (s == nullptr || p == nullptr)
				return false;
			if (p[0] == '\0')
				return s[0] == '\0';
			
			bool first_match = false;
			if (s[0] != '\0' && (s[0] == p[0] || p[0] == '.'))
				first_match = true;

			if (p[1] == '*')
			{
				//如果s是空字符串，这里会返回true,所以后面的s+1不用判断s的长度
				if (isMatch2(s, p + 2)) // s不动，p后移
					return true;
				if (!first_match)
					return false;
				return isMatch2(s + 1, p);//s后移，p不动
			}
			else
			{
				if (!first_match)
					return false;
				return isMatch2(s + 1, p + 1);//s,p同时后移
			}
			
			return true;
		}
		
		static bool isMatch3(string s, string p)
		{
			std::vector<std::vector<bool>> dp;
			dp.resize(s.length() + 1);
			for (unsigned int i = 0; i < s.length() + 1; i++)
			{
				dp[i].resize(p.length() + 1);
			}
			dp[0][0] = true;
			for (unsigned int sl = 0; sl <= s.length(); sl++)
			{
				for (unsigned int pl = 1; pl <= p.length(); pl++)
				{
					if (p[pl - 1] == '*')
					{
						if (pl < 2)
						{
							dp[sl][pl] = false;
						}
						else if (dp[sl][pl - 2])
						{
							dp[sl][pl] = true;
						}
						else if (sl > 0 && dp[sl - 1][pl] && (s[sl - 1] == p[pl - 2] || p[pl - 2] == '.'))
						{
							dp[sl][pl] = true;
						}
						else
						{
							dp[sl][pl] = false;
						}
					}
					else
					{
						if (sl > 0 && (p[pl - 1] == s[sl - 1] || p[pl - 1] == '.') && dp[sl-1][pl-1])
						{
							dp[sl][pl] = true;
						}
						else
						{
							dp[sl][pl] = false;
						}
					}
				}
			}
			return dp[s.length()][p.length()];
		}


		static void test()
		{
			Solution10 sol;
			while (true)
			{
				std::string s, p;
				std::cout << "输入原字符串：";
				std::cin >> s;
				std::cout << "输入匹配字符串：";
				std::cin >> p;
				std::cout << sol.isMatch3(s, p) << std::endl;
			}
		}
	};

	REG_TEST(10);

	class Solution32 {
	public:
		/*
		给定一个只包含 '(' 和 ')' 的字符串，找出最长的包含有效括号的子串的长度。
		示例 1:
		输入: "(()"
		输出: 2
		解释: 最长有效括号子串为 "()"

		示例 2:
		输入: ")()())"
		输出: 4
		解释: 最长有效括号子串为 "()()"
		*/
		int longestValidParentheses(string s) 
		{
			int left = 0;
			int right = 0;
			int max_len = 0;
			bool is_left = true;
			for (unsigned int i = 0; i < s.size(); i++)
			{
				if (s[i] == '(') {
					if (is_left){
						left++;
					} else {
						is_left = true;
						
						if (left > 0 && right > 0)
						{
							max_len += 2 * std::min(left, right);
						}
						left = right = 0;
						left++;
					}
				} else if (s[i] == ')') {
					if (is_left){
						is_left = false;
						right = 0;
					}
					right++;
				} else {
					break;
				}
			}
			if (left > 0 && right > 0)
			{
				max_len += 2 * std::min(left, right);
			}
			return max_len;
		}
		int longestValidParentheses2(string s)
		{
			int left = 0, right = 0;
			int res = 0;
			for (int i = 0; i < s.length(); i++)
			{
				if (s[i] == '(')
				{
					left++;
				}
				else
				{
					right++;
				}
				if (left == right)
				{
					int tmp = 2 * left;
					res = res > tmp ? res : tmp;
				}
				if (right > left)
				{
					right = left = 0;
				}
			}

			left = right = 0;
			for (int i = s.length() - 1; i >= 0; i--)
			{
				if (s[i] == '(')
				{
					left++;
				}
				else
				{
					right++;
				}
				if (left == right)
				{
					int tmp = 2 * left;
					res = res > tmp ? res : tmp;
				}
				if (right < left)
				{
					right = left = 0;
				}
			}
			return res;
		}
		
		/*
		dp[i]:s[i]如果是一个有效字符串的最后一个字符,d[i]记录这个有效字符串的长度
		*/
		int longestValidParentheses3(string s)
		{
			std::vector<int> dp;
			dp.resize(s.length(), 0);
			int max_len = 0;
			for (int i = 0; i < s.length(); i++)
			{
				if (s[i] == ')')
				{
					if (i == 0)
					{
						dp[i] = 0;
						continue;
					}
					if (s[i - 1] == '(')
					{//.....()
						if (i >= 2)
							dp[i] = dp[i - 2] + 2;
						else
							dp[i] = 2;
					}
					else
					{//...((...)) or ...)(...))
						int pre = i - 1 - dp[i - 1];
						if (pre >= 0 && s[pre] == '(')
						{
							if (pre >= 1)
								dp[i] = dp[pre-1] + dp[i - 1] + 2;
							else
								dp[i] = dp[i - 1] + 2;
						}
					}
					max_len = std::max(dp[i], max_len);
				}
			}
			return max_len;
		}
		static void test()
		{
			Solution32 sol;
			while (true)
			{
				std::string s;
				std::cout << "输入:";
				std::cin >> s;
				std::cout << sol.longestValidParentheses3(s) << std::endl;
			}
		}
	};
	REG_TEST(32);
}