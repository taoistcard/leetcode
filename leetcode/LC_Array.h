#pragma once
#include "LC_Base.h"
#include <set>

namespace LeetCode
{

	class Solution16 {
		/*
		给定一个包括 n 个整数的数组 nums 和 一个目标值 target。找出 nums 中的三个整数，使得它们的和与 target 最接近。返回这三个数的和。假定每组输入只存在唯一答案。

		示例：

		输入：nums = [-1,2,1,-4], target = 1
		输出：2
		解释：与 target 最接近的和是 2 (-1 + 2 + 1 = 2) 。
		 
		 提示：
		 3 <= nums.length <= 10^3
		 -10^3 <= nums[i] <= 10^3
		 -10^4 <= target <= 10^4
		 通过次数122,389提交次数270,173
		 来源：力扣（LeetCode）
		 链接：https://leetcode-cn.com/problems/3sum-closest
		 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
		 */
	public:
		int threeSumClosest(vector<int>& nums, int target) {
			std::sort(nums.begin(), nums.end());
			int res_sum = INT_MAX;
			for (int i = 0; i < nums.size() - 2; i++)
			{
				int j = i + 1, k = nums.size() - 1;
				int rj = -1, rk = -1;
				int pre_dt = INT_MAX;
				while (j < k)
				{
					int cur_dt = nums[i] + nums[j] + nums[k] - target;
					if (cur_dt == 0)
						return target;
					bool isfirst = false;
					if (rj != -1 && rk != -1)
					{
						if (std::abs(cur_dt) < std::abs(pre_dt))
						{
							rj = j;
							rk = k;
						}
					}
					else
					{
						rj = j;
						rk = k;
						isfirst = true;
					}

					if (cur_dt > 0)
					{
						k--;
						pre_dt = cur_dt;
					}
					else if (cur_dt < 0)
					{
						j++;
						pre_dt = cur_dt;
					}
				}
				if (rj != -1 && rk != -1)
				{
					int tmp_sum = nums[i] + nums[rj] + nums[rk];
					if (res_sum == INT_MAX)
						res_sum = tmp_sum;
					else if (std::abs(res_sum - target) > std::abs(tmp_sum - target))
						res_sum = tmp_sum;
				}
			}
			return res_sum;
		}

		static void test()
		{
			Solution16 sol;
			std::vector<int> arr{ 1, 2, 4, 8, 16, 32, 64, 128};
			std::cout << sol.threeSumClosest(arr, 82) << std::endl;
		}
	};

	REG_TEST(16);

	class Solution209 {
		/*
		给定一个含有 n 个正整数的数组和一个正整数 s ，找出该数组中满足其和 ≥ s 的长度最小的连续子数组，并返回其长度。如果不存在符合条件的连续子数组，返回 0。
		示例: 
		输入: s = 7, nums = [2,3,1,2,4,3]
		输出: 2
		解释: 子数组 [4,3] 是该条件下的长度最小的连续子数组。
		进阶:
		如果你已经完成了O(n) 时间复杂度的解法, 请尝试 O(n log n) 时间复杂度的解法。
		来源：力扣（LeetCode）
		链接：https://leetcode-cn.com/problems/minimum-size-subarray-sum
		著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
		*/
	public:
		int minSubArrayLen(int s, vector<int>& nums) {

			return 0;
		}

		static void test()
		{
			Solution209 sol;
			int s = 7;
			std::vector<int> nums{ 2, 3, 1, 2, 4, 3 };
			std::cout << sol.minSubArrayLen(s, nums) << std::endl;
		}
	};
	REG_TEST(209);

	class Solution215 {
	public:
		int findKthLargest(vector<int>& nums, int k) {
			if (k <= 0 || k > nums.size())
				return 0;
			std::vector<int> kq;
			for (int i = 0; i < nums.size(); i++)
			{
				if (kq.size() == k && nums[i] < kq[0])
				{
					continue;
				}
				auto it = std::lower_bound(kq.begin(), kq.end(), nums[i]);
				if (it == kq.end())
				{
					kq.push_back(nums[i]);
				}
				else
				{
					kq.insert(it, nums[i]);
				}
				if (kq.size() > k)
					kq.erase(kq.begin());
			}
			if (kq.size() == k)
				return *kq.begin();
			else
				return 0;
		}
		static void test()
		{
			Solution215 sol;
			int k = 4;
			std::vector<int> nums{ 3, 2, 3, 1, 2, 4, 5, 5, 6 };
			
			std::cout << sol.findKthLargest(nums, k) << std::endl;
		}
	};

	REG_TEST(215);
}