#pragma once
#include "LC_Base.h"

namespace LeetCode
{
	class Solution6 {
	public:
		static string convert(string s, unsigned int numRows) {
			if (numRows <= 1)
				return s;
			if (s.size() <= numRows){
				return s;
			}
			/*
			
			0     6       12        18
			1   5 7	   11 13     17
			2 4   8 10	  14  16
			3     9		  15

			*/
			//abcdef
			//i : 0 - numRows-1, 
			//i=0, i += numRows*2-1-0-1
			//i=1, i += numRows*2-1-1-1
			//i=2, i += numRows*2-1-2-1
			//i=3, i += numRows*2-1-3-1
			std::string res;
			res.reserve(s.size());

			int n = numRows * 2 - 2; // Z字两个相邻竖列间隔
			for (unsigned int i = 0; i < numRows; i++)
			{
				unsigned int t = i;
				res += s[t];

				
				if (t == 0 || t == numRows - 1)
				{
					t += n;
					while (t < s.size())
					{
						res += s[t];
						t += n;
					}
				}
				else
				{
					unsigned int second_index = t + n - i * 2;
					if (second_index < s.size())
						res += s[second_index];
					t += n;
					while (t < s.size())
					{
						res += s[t];
						second_index = t + n - i * 2;
						if (second_index >= s.size())
						{
							break;
						}
						res += s[second_index];

						t += n;
					}
				}
			}

			return res;
		}
	};

	class Solution7 {
	public:
		static int reverse(int x) {
			if (x == 0)
				return 0;

			int flag = (x > 0) ? 1 : -1;
			x *= flag;
			std::vector<int> nums;
			while (x != 0)
			{
				nums.push_back(x % 10);
				x /= 10;
			}
			long long result = 0;
			for (unsigned int i = 0; i < nums.size(); i++)
			{
				result = result * 10 + nums[i];
			}
			result *= flag;
			if (result < INT_MIN || result > INT_MAX)
			{
				return 0;
			}
			return (int)result;
		}
	};

	class Solution8 {
	public:
		static int myAtoi(string str) {
			unsigned int i = 0;
			while (i <str.size() && str[i] == ' ')
			{
				++i;
			}
			if (str.size() == i)
				return 0;
			int num = 0;
			if (str[i] == '-')
			{
				++i;
				if (str.size() == i)
					return 0;
				while (str[i] == '0')
				{
					++i;
				}
				int remainder = INT_MIN % 10;
				int model_num = INT_MIN / 10;
				while (i < str.size() && (str[i] >= '0' && str[i] <= '9'))
				{
					
					int add = int(str[i] - '0');

					if (num < model_num)
					{//不能做x10操作，否则会溢出
						return INT_MIN;
					}
					else if (num == model_num)
					{//不能做-add操作，否则会溢出
						if (add > remainder * -1)
						{
							return INT_MIN;
						}
					}

					num *= 10;
					num -= add;
					++i;
				}
				return num;
			}
			else
			{
				if (str[i] == '+')
				{
					++i;
				}
				if (str.size() == i)
					return 0;
				while (str[i] == '0')
				{
					++i;
				}
				int remainder = INT_MAX % 10;
				int model_num = INT_MAX / 10;

				while (i < str.size() && (str[i] >= '0' && str[i] <= '9'))
				{
					int add = int(str[i] - '0');

					if (num == model_num)
					{//不能做+add操作，否则会溢出
						if (add > remainder)
						{
							return INT_MAX;
						}
					}
					else if (num > model_num)
					{//不能做x10操作，否则会溢出
						return INT_MAX;
					}
					num *= 10;
					num += add;
					++i;
				}
				return num;
			}
		}
	};

	class Solution12
	{
		/*
		罗马数字包含以下七种字符： I， V， X， L，C，D 和 M。

		字符          数值
		I             1
		V             5
		X             10
		L             50
		C             100
		D             500
		M             1000
		例如， 罗马数字 2 写做 II ，即为两个并列的 1。12 写做 XII ，即为 X + II 。 27 写做  XXVII, 即为 XX + V + II 。

		通常情况下，罗马数字中小的数字在大的数字的右边。但也存在特例，例如 4 不写做 IIII，而是 IV。数字 1 在数字 5 的左边，所表示的数等于大数 5 减小数 1 得到的数值 4 。同样地，数字 9 表示为 IX。这个特殊的规则只适用于以下六种情况：

		I 可以放在 V (5) 和 X (10) 的左边，来表示 4 和 9。
		X 可以放在 L (50) 和 C (100) 的左边，来表示 40 和 90。 
		C 可以放在 D (500) 和 M (1000) 的左边，来表示 400 和 900。
		给定一个整数，将其转为罗马数字。输入确保在 1 到 3999 的范围内。

		示例 1:

		输入: 3
		输出: "III"
		示例 2:

		输入: 4
		输出: "IV"
		示例 3:

		输入: 9
		输出: "IX"
		示例 4:

		输入: 58
		输出: "LVIII"
		解释: L = 50, V = 5, III = 3.
		示例 5:

		输入: 1994
		输出: "MCMXCIV"
		解释: M = 1000, CM = 900, XC = 90, IV = 4.

		来源：力扣（LeetCode）
		链接：https://leetcode-cn.com/problems/integer-to-roman
		著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
		*/
	public:
		static void test()
		{
			Solution12 sol;
			while (true)
			{
				std::cout << "输入一个整型数:";
				int n;
				std::cin >> n;
				std::cout << sol.intToRoman2(n) << std::endl;
			}
		}

		string intToRoman2(int num) {
			std::vector<int> base = {1000,900,500,400,100,90,50,40,10,9,5,4,1};
			std::vector<std::string> base_roman = { "M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I" };
			std::stringstream ss;
			int i = 0;
			while (num > 0)
			{
				while (num >= base[i])
				{
					num -= base[i];
					ss << base_roman[i];
				}
				++i;
			}
			return ss.str();
		}

		struct TIR
		{
			int base;
			char one;
			char five;
		};
		string intToRoman(int num) {
			std::vector<TIR> tirs = {
				{ 1000, 'M', '\0' },
				{ 100, 'C', 'D' },
				{ 10, 'X', 'L' },
				{ 1, 'I', 'V'},
			};

			std::stringstream ss;

			for (int i = 0; i < tirs.size(); i++)
			{
				if (num < tirs[i].base)
					continue;
				int m = num / tirs[i].base;
				num = num % tirs[i].base;
				if (m == 9)
				{
					if (i == 0)
					{
						for (int j = 0; j < m; j++)
						{
							ss << tirs[i].one;
						}
					}
					else
					{
						ss << tirs[i].one << tirs[i - 1].one;
					}
				}
				else if (m == 4)
				{
					ss << tirs[i].one << tirs[i].five;
				}
				else
				{
					if (m >= 5)
					{
						ss << tirs[i].five;
						m = m - 5;
					}
					for (int j = 0; j < m; j++)
					{
						ss << tirs[i].one;
					}
				}
			}
			return ss.str();
		}
	};
	REG_TEST(12);

	class Solution13
	{
	public:
		/*
		罗马数字包含以下七种字符: I， V， X， L，C，D 和 M。

		字符          数值
		I             1
		V             5
		X             10
		L             50
		C             100
		D             500
		M             1000
		例如， 罗马数字 2 写做 II ，即为两个并列的 1。12 写做 XII ，即为 X + II 。 27 写做  XXVII, 即为 XX + V + II 。

		通常情况下，罗马数字中小的数字在大的数字的右边。但也存在特例，例如 4 不写做 IIII，而是 IV。数字 1 在数字 5 的左边，所表示的数等于大数 5 减小数 1 得到的数值 4 。同样地，数字 9 表示为 IX。这个特殊的规则只适用于以下六种情况：

		I 可以放在 V (5) 和 X (10) 的左边，来表示 4 和 9。
		X 可以放在 L (50) 和 C (100) 的左边，来表示 40 和 90。 
		C 可以放在 D (500) 和 M (1000) 的左边，来表示 400 和 900。
		给定一个罗马数字，将其转换成整数。输入确保在 1 到 3999 的范围内。

		示例 1:
		输入: "III"
		输出: 3

		示例 2:
		输入: "IV"
		输出: 4

		示例 3:
		输入: "IX"
		输出: 9

		示例 4:
		输入: "LVIII"
		输出: 58
		解释: L = 50, V= 5, III = 3.
		示例 5:

		输入: "MCMXCIV"
		输出: 1994
		解释: M = 1000, CM = 900, XC = 90, IV = 4.

		来源：力扣（LeetCode）
		链接：https://leetcode-cn.com/problems/roman-to-integer
		著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
		*/
		static void test()
		{
			Solution13 sol;
			while (true)
			{
				std::string s;
				std::cout << "输入罗马数字:";
				std::cin >> s;
				std::cout << sol.romanToInt(s) << std::endl;
			}
		}
		int romanToInt(string s) {
			std::map<char, int> m2i;
			m2i['M'] = 1000;
			m2i['D'] = 500;
			m2i['C'] = 100;
			m2i['L'] = 50;
			m2i['X'] = 10;
			m2i['V'] = 5;
			m2i['I'] = 1;
			int num = 0;
			for (int i = 0; i < s.size(); )
			{
				int t1 = m2i[s[i]];
				if (i < s.size() - 1)
				{
					int t2 = m2i[s[i + 1]];
					if (t1 < t2)
					{
						num += t2 - t1;
						i += 2;
						continue;
					}
				}
				num += t1;
				i += 1;
			}
			return num;
		}
	};
	REG_TEST(13);

	/**
	给定两个整数，被除数 dividend 和除数 divisor。将两数相除，要求不使用乘法、除法和 mod 运算符。
	返回被除数 dividend 除以除数 divisor 得到的商。
	示例 1:
		输入: dividend = 10, divisor = 3
		输出: 3
	示例 2:
		输入: dividend = 7, divisor = -3
		输出: -2
	说明:
		被除数和除数均为 32 位有符号整数。
		除数不为 0。
		假设我们的环境只能存储 32 位有符号整数，其数值范围是[-2e31,2e31-1]。本题中，如果除法结果溢出，则返回2e31-1
	**/
	class Solution29 {
	public:
		int divide(int dividend, int divisor) {
			if (dividend == -2e31 && divisor == -1) return 2147483647;//正整数和负整数最大值差1
			bool flag = 0;
			if ((dividend > 0) ^ (divisor > 0)) flag = 1;//运用异或运算
			long long dvd = labs(dividend);//将dividend和divisor转换为正整数，并赋值给一个long long型
			long long dvs = labs(divisor);//此处一定要用labs，用abs会出错
			long long d = 0;//用来保存结果
			while (dvd >= dvs){
				long long temp = dvs;
				long long divide = 1;
				while (dvd >= (temp << 1)){
					temp <<= 1;
					divide <<= 1;
				}
				dvd -= temp;//改变被除数的大小
				d += divide;
			}
			return static_cast<int>((flag) ? (0 - d) : d);
		}
	};


	class Solution940 {
		/**
		给定一个字符串 S，计算 S 的不同非空子序列的个数。
		因为结果可能很大，所以返回答案模 10^9 + 7.
		示例 1：
			输入："abc"
			输出：7
			解释：7 个不同的子序列分别是 "a", "b", "c", "ab", "ac", "bc", 以及 "abc"。
		示例 2：
			输入："aba"
			输出：6
			解释：6 个不同的子序列分别是 "a", "b", "ab", "ba", "aa" 以及 "aba"。
		示例 3：
			输入："aaa"
			输出：3
			解释：3 个不同的子序列分别是 "a", "aa" 以及 "aaa"。
		提示：
			S 只包含小写字母。
			1 <= S.length <= 2000
		**/
	public:
		/**
		使用一個endswith[26]陣列，儲存的是有多少個子序列以i結尾。
		則，當前總共有N = sum(endswith)個不同的子序列，當我們新增加一個字元c時，相當於在以前每個結尾的位置後面又增添了一個新的字元，所以現在有了N個以c結尾的不同的子序列了。
		所以，我們遍歷一遍s，更新的方式是end[c] = sum(end) + 1。加一是因為c本身也是一個子序列。
		重复字符的处理:计算方法同上，当前组合结果包含了之前重复字符的组合，刚好新的数值会覆盖之前的。
		**/
		static int distinctSubseqII(string S) {
			int kMod = static_cast<int>(1e9 + 7);
			std::vector<int> counts(26);
			for (char c : S)
				counts[c - 'a'] = accumulate(begin(counts), end(counts), 1L) % kMod;
			return accumulate(begin(counts), end(counts), 0L) % kMod;
		}

		/**
		没有重复字符的情况: dp[n] = dp[n-1] + dp[n-1]+1
		有重复字符的情况：重复字符位ch，上一次出现的位置索引位k(1<=k<=len(len)),dp[n] = dp[n-1] + ( (dp[n-1]+1) - (dp[k-1] + 1) )
		(dp[k-1] + 1)含义:ch上一次出现，导致新增的这么多组合，相同的这一次ch出现，这部分组合会重复一遍，所以减去。
		*/
		static int distinctSubseqII_2(string S) {

			const static int len = 2000;
			int n = S.size();
			int mod = 1000000007;
			int dp[len + 10], last[len + 10], latest[len + 10];
			char newS[len + 10];

			memset(last, 0, sizeof(last));
			memset(latest, 0, sizeof(latest));
			memset(dp, 0, sizeof(dp));
			memset(newS, 0, sizeof(newS));
			for (int i = 1; i <= n; ++i) {
				newS[i] = S[i - 1];
				last[i] = latest[newS[i]];
				latest[newS[i]] = i;
			}

			for (int i = 1; i <= n; ++i) {
				if (last[i] == 0) {
					dp[i] = dp[i - 1] * 2 + 1;
				}
				else {
					dp[i] = dp[i - 1] + (dp[i - 1] - dp[last[i] - 1]);
				}
				if (dp[i] < 0) {
					dp[i] += mod;
				}
				dp[i] %= mod;
			}

			return dp[n];
		}

		static int distinctSubseqII_3(string S) {

			const static int len = 2000;
			int n = S.size();
			int mod = 1000000007;
			int dp[len + 1], last[len + 1], latest[26];

			memset(last, 0, sizeof(last));
			memset(latest, 0, sizeof(latest));
			memset(dp, 0, sizeof(dp));

			char c = 0;
			for (int i = 1; i <= n; ++i) {
				
				c = S[i - 1];
				last[i] = latest[c-'a'];
				latest[c-'a'] = i;
			}

			for (int i = 1; i <= n; ++i) {
				if (last[i] == 0) {
					dp[i] = dp[i - 1] * 2 + 1;
				}
				else {
					dp[i] = dp[i - 1] + (dp[i - 1] - dp[last[i] - 1]);
				}
				if (dp[i] < 0) {
					dp[i] += mod;
				}
				dp[i] %= mod;
			}

			return dp[n];
		}
	};

	class Solution944 {
		/**
		给出由 N 个小写字母串组成的数组 A，所有小写字母串的长度都相同。
		现在，我们可以选择任何一组删除索引，对于每个字符串，我们将删除这些索引中的所有字符。
		举个例子，如果字符串为 "abcdef"，且删除索引是 {0, 2, 3}，那么删除之后的最终字符串为 "bef"。
		假设我们选择了一组删除索引 D，在执行删除操作之后，A 中剩余的每一列都是有序的。
		形式上，第 c 列为 [A[0][c], A[1][c], ..., A[A.length-1][c]]
		返回 D.length 的最小可能值。

		示例 1：
		输入：["cba","daf","ghi"]
		输出：1

		示例 2：
		输入：["a","b"]
		输出：0

		示例 3：
		输入：["zyx","wvu","tsr"]
		输出：3

		提示：
		1 <= A.length <= 100
		1 <= A[i].length <= 1000
		**/
	public:
		static int minDeletionSize_0(vector<string>& A) {
			unsigned int row_cnt = A.size();
			if (row_cnt <= 2)
				return 0;
			unsigned int col_cnt = A[0].length();
			if (col_cnt == 0)
				return 0;
			unsigned int del_col_cnt = 0;
			for (int c = 0; c < col_cnt; ++c)
			{
				bool bDel = false;
				for (int r = 0; r < row_cnt - 2; ++r)
				{
					if (A[r][c] >= A[r + 1][c] && A[r + 1][c] >= A[r + 2][c])
					{
						continue;
					}
					else if (A[r][c] <= A[r + 1][c] && A[r + 1][c] <= A[r + 2][c])
					{
						continue;
					}
					else
					{
						bDel = true;
						break;
					}
				}
				if (bDel)
				{
					del_col_cnt++;
				}
			}

			return del_col_cnt;
		}

		static int minDeletionSize_1(vector<string>& A) {
			unsigned int row_cnt = A.size();
			if (row_cnt <= 2)
				return 0;
			unsigned int col_cnt = A[0].length();
			if (col_cnt == 0)
				return 0;
			unsigned int del_col_cnt = 0;
			for (int c = 0; c < col_cnt; ++c)
			{
				bool bDel = false;
				int flag = 3;
				for (int r = 0; r < row_cnt - 1; ++r)
				{
					
					if (flag == 3)
					{
						if (A[r][c] > A[r + 1][c])
						{
							flag = 1;
							continue;
						}
						else if (A[r][c] < A[r + 1][c])
						{
							flag = 2;
							continue;
						}
						//else
						//{
						//	continue;
						//}
					}
					else if (flag == 1)
					{
						if (A[r][c] < A[r + 1][c])
						{
							bDel = true;
							break;
						}
					}
					else if (flag == 2)
					{
						if (A[r][c] > A[r + 1][c])
						{
							bDel = true;
							break;
						}
					}
					
				}
				if (bDel)
				{
					del_col_cnt++;
				}
			}

			return del_col_cnt;
		}

		static int minDeletionSize(vector<string>& A) {
			int result = 0;
			for (int j = 0; j < A[0].size(); ++j){
				for (int i = 0; i < A.size() - 1; ++i){
					if (A[i][j] > A[i + 1][j]){
						++result;
						break;
					}
				}
			}

			return result;
		}
	};

	class Solution942 {
	public:
		vector<int> diStringMatch(string S) {

		}
	};

	class Solution943 {
		/**
		给定一个字符串数组 A，找到以 A 中每个字符串作为子字符串的最短字符串。
		我们可以假设 A 中没有字符串是 A 中另一个字符串的子字符串。

		示例 1：
		输入：["alex","loves","leetcode"]
		输出："alexlovesleetcode"
		解释："alex"，"loves"，"leetcode" 的所有排列都会被接受。
		
		示例 2：
		输入：["catg","ctaagt","gcta","ttca","atgcatc"]
		输出："gctaagttcatgcatc"

		提示：
		1 <= A.length <= 12
		1 <= A[i].length <= 20
		**/
	public:
		static string shortestSuperstring(vector<string>& A) {

		}
	};

	class Solution380 {
		public:

		/** Inserts a value to the set. Returns true if the set did not already contain the specified element. */
		bool insert(int val) {
			if (m_val_location.count(val) == 0)
			{
				m_vals.push_back(val);
				m_val_location.insert(make_pair(val, m_vals.size() - 1));
				return true;
			}
			else
			{
				return false;
			}
		}

		/** Removes a value from the set. Returns true if the set contained the specified element. */
		bool remove(int val) {
			auto it = m_val_location.find(val);
			if (m_val_location.end() == it)
			{
				return false;
			}
			else
			{
				if (m_vals.size() == 1)
				{
					m_vals.clear();
					m_val_location.erase(it);
				}
				else
				{
					m_vals[it->second] = m_vals.back();
					m_val_location[m_vals.back()] = it->second;
					m_vals.pop_back();
					m_val_location.erase(it);
				}
				
				return true;
			}
		}

		/** Get a random element from the set. */
		int getRandom() {
			if (m_vals.size() == 0)
				return 0;
			int idx = rand() % m_vals.size();
			return m_vals[idx];
		}
	private:
		vector<int> m_vals;
		unordered_map<int, int> m_val_location;
	};


	/*
	排排坐，分糖果。

	我们买了一些糖果 candies，打算把它们分给排好队的 n = num_people 个小朋友。

	给第一个小朋友 1 颗糖果，第二个小朋友 2 颗，依此类推，直到给最后一个小朋友 n 颗糖果。

	然后，我们再回到队伍的起点，给第一个小朋友 n + 1 颗糖果，第二个小朋友 n + 2 颗，依此类推，直到给最后一个小朋友 2 * n 颗糖果。

	重复上述过程（每次都比上一次多给出一颗糖果，当到达队伍终点后再次从队伍起点开始），直到我们分完所有的糖果。注意，就算我们手中的剩下糖果数不够（不比前一次发出的糖果多），这些糖果也会全部发给当前的小朋友。

	返回一个长度为 num_people、元素之和为 candies 的数组，以表示糖果的最终分发情况（即 ans[i] 表示第 i 个小朋友分到的糖果数）。

	 示例 1：

	 输入：candies = 7, num_people = 4
	 输出：[1,2,3,1]
	 解释：
	 第一次，ans[0] += 1，数组变为 [1,0,0,0]。
	 第二次，ans[1] += 2，数组变为 [1,2,0,0]。
	 第三次，ans[2] += 3，数组变为 [1,2,3,0]。
	 第四次，ans[3] += 1（因为此时只剩下 1 颗糖果），最终数组变为 [1,2,3,1]。
	 示例 2：

	 输入：candies = 10, num_people = 3
	 输出：[5,2,3]
	 解释：
	 第一次，ans[0] += 1，数组变为 [1,0,0]。
	 第二次，ans[1] += 2，数组变为 [1,2,0]。
	 第三次，ans[2] += 3，数组变为 [1,2,3]。
	 第四次，ans[0] += 4，最终数组变为 [5,2,3]。
	  
	  提示：
	  1 <= candies <= 10^9
	  1 <= num_people <= 1000
	*/
	/*
	T:总的糖果数
	x:没一次交个一个人糖果记一次，x表示总共可以交给几次，第一次交给1个糖果，第二2个，第三次3个，....., 第x-1次x-1个,第x次的糖果数可能小于x
	更具T算出x，[x]表示x向下取整,1~x次交给操作的糖果数分别是1，2，3,...,[x], T - sum{1, 2, [x]}
	(1+x)*x/2 = T
	x = sqrt((8*T + 1)/4) - 1 / 2
	*/
	class Solution1103 {
	public:
		//算出T个糖果总共可以交给几次(x), 返回[x]，可能比实际的次数小1
		int CalcGiveTimes(int T)
		{
			double x = sqrt((8.0 * T + 1.0) / 4.0) - 1.0f / 2.0;
			return (int)floor(x);
		}
		vector<int> distributeCandies(int candies, int num_people) {
			vector<int> ans;
			if (num_people <= 0)
			{
				return ans;
			}
			ans.resize(num_people);

			int x = CalcGiveTimes(candies); // 交给的糖果数和当前次数相匹配的x最大值,有可能还剩余一些糖果在下一次交给(糖果数和下一次的次数不匹配)
			int T = (1 + x) * x / 2;
			int last_candies = 0; // 最后一次交给的糖果数
			if (T > candies)
			{
				std::cout << "Error x:" << x << ", candies:" << candies << std::endl;
				return ans;
			}
			else if (T < candies)
			{
				last_candies = candies - T;
			}
			
			int cycle_cnt = x / num_people;
			if (cycle_cnt > 0)
			{
				int cycle_add = (cycle_cnt - 1) * num_people;
				for (size_t i = 0; i < num_people; i++)
				{
					ans[i] = (i + 1) * cycle_cnt + (cycle_cnt - 1)*cycle_cnt*num_people/2;
				}
			}
			//left_x>=0 && left_x < num_people-1
			int left_x = x - cycle_cnt * num_people;
			if (left_x > 0)
			{
				++cycle_cnt;
				int cycle_add = (cycle_cnt - 1) * num_people;
				int tmp_x = cycle_cnt * num_people;
				for (size_t i = 0; i < left_x; i++)
				{
					ans[i] += i + 1 + cycle_add;
				}
			}
			
			ans[left_x] += last_candies;			
			return ans;
		}
	};

	/*
	给定一个二叉树，返回所有从根节点到叶子节点的路径。
	说明: 叶子节点是指没有子节点的节点。
	示例:
	输入:
	   1
	 /   \
	2     3
	 \
	  5
	输出: ["1->2->5", "1->3"]

	解释: 所有根节点到叶子节点的路径为: 1->2->5, 1->3

	来源：力扣（LeetCode）
	链接：https://leetcode-cn.com/problems/binary-tree-paths
	著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
	*/
	class Solution257
	{

	};

	/*
	数组的相对排序

	给你两个数组，arr1 和 arr2，
	arr2 中的元素各不相同
	arr2 中的每个元素都出现在 arr1 中
	对 arr1 中的元素进行排序，使 arr1 中项的相对顺序和 arr2 中的相对顺序相同。未在 arr2 中出现过的元素需要按照升序放在 arr1 的末尾。

	示例：
	输入：arr1 = [2,3,1,3,2,4,6,7,9,2,19], arr2 = [2,1,4,3,9,6]
	输出：[2,2,2,1,4,3,3,9,6,7,19]

	提示：
	
	arr1.length, arr2.length <= 1000
	0 <= arr1[i], arr2[i] <= 1000
	arr2 中的元素 arr2[i] 各不相同
	arr2 中的每个元素 arr2[i] 都出现在 arr1 中
	*/
	class Solution1122
	{
	public:
		bool isBigger(int n1, int n2, vector<int>& arr2)
		{
			unsigned int i, j;
			i = j = -1;
			for (unsigned int k = 0; k < arr2.size(); k++)
			{
				if (i == -1 && arr2[k] == n1)
					i = k;
				if (j == -1 && arr2[k] == n2)
					j = k;
				if (i != -1 && j != -1)
					break;
			}
			if (i != -1 && j != -1)
			{
				return i > j;
			}
			if (i != -1)
				return false;
			if (j != -1)
				return true;
			return n1 > n2;
		}
		vector<int> relativeSortArray(vector<int>& arr1, vector<int>& arr2) {
			for (unsigned int i = 0; i < arr1.size()-1; i++)
			{
				for (unsigned j = i; j < arr1.size(); j++)
				{
					if (isBigger(arr1[i], arr1[j], arr2))
					{
						int tmp = arr1[i];
						arr1[i] = arr1[j];
						arr1[j] = tmp;
					}
				}
			}
			return arr1;
		}
	};


}