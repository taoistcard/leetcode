#include <iostream>
#include "Test.h"
#include <vector>
#include <map>
#include <random>
#include <functional>
#include <iomanip>

#include "BTree.h"
#include "Sort.h"

using namespace std;
class CSgsRandUint
{
	static const unsigned int MY_RAND_MAX = 200000000;
public:
	static CSgsRandUint & single(){ static CSgsRandUint rmg; return rmg; }
private:
	CSgsRandUint(unsigned int min = 0, unsigned int max = MY_RAND_MAX)
	{
		if (min > max || max > MY_RAND_MAX || min < 0)
		{
			
		}
		m_max = max;
		m_min = min;

		static std::random_device rd;
		static std::mt19937 gen(rd());
		static std::uniform_int_distribution<unsigned int> dis(0, 200000000);
		cb_gen = [&](){
			return dis(gen);
		};
	}
	~CSgsRandUint(){}

public:
	unsigned int operator ()(){ return cb_gen(); }

	unsigned int get_max(){ return m_max; }
	unsigned int get_min(){ return m_min; }
private:
	std::function<unsigned int()> cb_gen;
	unsigned int m_max;
	unsigned int m_min;
};

struct RedPackageProperty
{
	unsigned int config_id;
	unsigned int start_time; //生成时间
	unsigned int remain_times;			//可抽奖次数
	std::vector<unsigned int> remain_goods;	//剩余道具列表
};


unsigned int random_int(unsigned int min, unsigned int max)
{
	CSgsRandUint &myrand = CSgsRandUint::single();
	if (min == max)
	{
		return min;
	} else if (min > max)
	{
		
		return max;
	}

	unsigned long long temp = myrand();
	temp = temp % (max - min + 1);
	temp += min;
	if (temp<min || temp>max)
	{
		
		return max;
	}
	return (unsigned int)temp;
}
#include <bitset>

unsigned int test_move()
{
	long long s = -20;
	std::cout << s << std::endl;
	std::cout << std::bitset<sizeof(long long) * 8>(s) << std::endl;

	s = s << 17;
	std::cout << s << std::endl;
	std::cout << std::bitset<sizeof(long long) * 8>(s) << std::endl;

	s = s >> 17;
	std::cout << s << std::endl;
	std::cout << std::bitset<sizeof(long long) * 8>(s) << std::endl;

	s = s << 17;
	std::cout << s << std::endl;
	std::cout << std::bitset<sizeof(long long) * 8>(s) << std::endl;
	return 0;
}

unsigned int test_mode()
{
	unsigned int start = 1526705740;
	unsigned int num = 86400;
	for (size_t i = 1; i <= num; i++)
	{
		unsigned int remainder1 = start % i;
		unsigned int remainder2 = start & (i-1);
		if (remainder2 != remainder1)
		{
			std::cout << "i=" << i << ", remainder1:" << remainder1 << ", remainder2:" << remainder2 << std::endl;
		}
	}

	return 0;
}

using namespace CppTest;

#include "std_head.h"
#include "string_func.h"
#include "LeetCode.h"
#include "LintCode.h"
#include <algorithm>

//时间调整，加上当前时间，位了在排名时，先上榜的名次更靠前
long long AdjustDailyRankScore(int score)
{
	//seconds小的表明是先完成的，排名要靠前
	unsigned int seconds = 255;

	long long lscore = ((static_cast<long long>(score)) << 8);
	lscore = lscore + seconds;
	return lscore;
}

int RetriveDailyRankScore(long long lscore)
{
	double d = (double)(lscore / 256);
	int s1 = static_cast<int>(lscore / 256);
	int s2 = static_cast<int>(lscore >> 8);

	return s1;
}

void test_sort()
{
	std::vector<int> data{ 7, 8, 9, 9, 8, 7 };
	std::sort(data.begin(), data.end(), [](int a, int b)->bool{
		return true;
	});
}	

void test_ss()
{
	std::stringstream ss;
	ss << "闪" << setw(20) << 15;
	std::cout << ss.str() << std::endl;
	std::cout << "123456789" << std::endl;
}
static void test()
{
	//LeetCode::Solution35::test();
	LeetCode::test();
	//test_ss();
	//CppTest::test_sort();
}
int main()
{
	////["cba","daf","ghi"]
	//std::vector<string> vs{"b", "a"};
	//cout << LeetCode::Solution944::minDeletionSize(vs) << endl;

	//system("pause");
	//long long lscore = AdjustDailyRankScore(-25);
	//int score = RetriveDailyRankScore(lscore);

	//test_sort();
	/**
	["RandomizedSet","insert","insert","remove","insert","insert","insert","remove","remove","insert","remove","insert","insert","insert","insert","insert","getRandom","insert","remove","insert","insert"]
	[[],[3],[-2],[2],[1],
		[-3],[-2],[-2],[3],
		[-1],[-3],
		[1],[-2],[-2],[-2],
		[1],[],[-2],[0],[-3],[1]]
	*/
	//LeetCode::Solution380 randomSet;
	//randomSet.insert(3);
	//randomSet.insert(-2);
	//randomSet.remove(2); 
	//randomSet.insert(1);
	//randomSet.insert(-3);
	//randomSet.insert(-2); 
	//randomSet.remove(-2);
	//randomSet.remove(3);
	//randomSet.insert(-1);
	//randomSet.remove(-3);

	//randomSet.insert(1);
	//randomSet.insert(-2);
	//randomSet.insert(-2);
	//randomSet.insert(-2);
	//randomSet.insert(1);
	//randomSet.getRandom();

	//randomSet.insert(-2);
	//randomSet.remove(0);
	//randomSet.insert(-3);
	//randomSet.insert(1);

	
	//LintCode::TreeNode* pRoot = LintCode::createTree("{2,1,2}");
	//LintCode::BreadthTraverse(pRoot);
	//LintCode::Solution95 s95;
	//cout << s95.isValidBST(pRoot);

	//LeetCode::Solution1103 so;
	//{
	//	std::vector<int> ans = so.distributeCandies(77, 4);
	//	for (unsigned int i = 0; i < ans.size(); i++)
	//	{
	//		if (i == 0)
	//			std::cout << "[";
	//		std::cout << ans[i];
	//		if (i == ans.size() - 1)
	//		{
	//			std::cout << "]";
	//		}
	//		else
	//		{
	//			std::cout << ",";
	//		}
	//	}
	//}
	//{
	//	std::vector<int> ans = so.distributeCandies(78, 4);
	//	for (unsigned int i = 0; i < ans.size(); i++)
	//	{
	//		if (i == 0)
	//			std::cout << "[";
	//		std::cout << ans[i];
	//		if (i == ans.size() - 1)
	//		{
	//			std::cout << "]";
	//		}
	//		else
	//		{
	//			std::cout << ",";
	//		}
	//	}
	//}

//	LeetCode::Solution1122 sol;
////	vector<int> v1{ 2, 3, 1, 3, 2, 4, 6, 7, 9, 2, 19 };
////	vector<int> v2{ 2, 1, 4, 3, 9, 6 };
//	vector<int> v1{28, 6, 22, 8, 44, 17};
//	vector<int> v2{ 22, 28, 8, 6 };
//
//	auto r = sol.relativeSortArray(v1, v2);
//
//	for (auto n : r)
//	{
//		cout << n << ' ';
//	}
	//std::cout << (int)c_2_num('0') << std::endl;
	//std::cout << (int)c_2_num('1') << std::endl;
	//std::cout << (int)c_2_num('9') << std::endl;
	//std::cout << (int)c_2_num('a') << std::endl;
	//std::cout << (int)c_2_num('d') << std::endl;
	//std::cout << (int)c_2_num('f') << std::endl;

	//std::cout << (int)c_2_num('A') << std::endl;
	//std::cout << (int)c_2_num('D') << std::endl;
	//std::cout << (int)c_2_num('F') << std::endl;

	//char data[] = {0,1,2,9,10,12,15,16,20,32,33};
	//std::string hex_s = binToHexString(data, sizeof(data));
	//std::cout << hex_s << std::endl;
	//
	//char buffer[sizeof(data)] = {0};
	//hexStringToBin(buffer, sizeof(buffer), hex_s);

	//for (unsigned int i = 0; i < sizeof(buffer); i++)
	//{
	//	std::cout << (int)buffer[i] << std::endl;
	//}

	test();
	system("pause");
	return 0;
}