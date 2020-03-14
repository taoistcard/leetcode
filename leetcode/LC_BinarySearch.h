#pragma once
#include "LC_Base.h"

/*
LeetCode 二叉搜索
*/
namespace LeetCode
{
	class Solution4 {
		/*
		给定两个大小为 m 和 n 的有序数组 nums1 和 nums2。

		请你找出这两个有序数组的中位数，并且要求算法的时间复杂度为 O(log(m + n))。

		你可以假设 nums1 和 nums2 不会同时为空。

		示例 1:

		nums1 = [1, 3]
		nums2 = [2]

		则中位数是 2.0
		示例 2:

		nums1 = [1, 2]
		nums2 = [3, 4]

		则中位数是 (2 + 3)/2 = 2.5

		来源：力扣（LeetCode）
		链接：https://leetcode-cn.com/problems/median-of-two-sorted-arrays
		著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
		*/
	public:
		static void test()
		{
			Solution4 sol;

			std::vector<int> nums1{ 1, 2 };
			std::vector<int> nums2{ 3, 4 };
			std::cout << sol.findMedianSortedArrays(nums1, nums2) << std::endl;
		}
		double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
			if (nums1.size() > nums2.size())
				return findMedianSortedArrays(nums2, nums1);
			int m = nums1.size();
			int n = nums2.size();
			if (m == 0 && n == 0)
				return 0.0;
			if (m == 0)
			{
				int half = (n + 1) / 2;
				if (n % 2 == 1)
				{
					return nums2[(n / 2)];
				}
				else
				{
					return (nums2[n / 2] + nums2[n / 2 - 1]) / 2.0;
				}
			}
			//i = [0,m), j=[0,n)
			/*
			a[0],a[1],a[3],...,a[i-1], a[i],...a[m-1]
			b[0],b[1],b[3],...,b[j-1], b[j],...b[n-1]
			a[i-1]<=b[j] && b[j-1]<=a[i]
			i+j = (m + n + 1)/2; =>j = (m+n+1)/2 - i
			i>0 => j<n; i<m =>j>0
			*/
			int iMin = 0, iMax = m, halfLen = (m + n + 1) / 2;
			while (iMin <= iMax)
			{
				/*
				nums1[i - 1] <= nums2[j]
				nums2[j - 1] <= nums1[i]
				*/
				int i = (iMin + iMax) / 2;
				int j = halfLen - i;
				if (i > 0)
				{//j<n
					if (i == m)
					{//j<n, i==m
						if (nums1[i - 1] > nums2[j])
						{
							iMax = i - 1;
						}
						else
						{
							//满足条件
							int max_left = 0;
							int min_right = 0;
							if (j > 0)
								max_left = max(nums1[i - 1], nums2[j - 1]);
							else
								max_left = nums1[i - 1];

							if ((m + n) % 2 == 1) { return max_left; }

							min_right = nums2[j];

							return (max_left + min_right) / 2.0;
						}
					}
					else
					{// //j<n, i<m
						if (nums1[i - 1] > nums2[j])
						{
							iMax = i - 1;
						}
						else if (j  > 0 && nums2[j - 1] > nums1[i])
						{
							iMin = i + 1;
						}
						else
						{
							int max_left = 0;
							int min_right = 0;
							if (j > 0)
								max_left = max(nums1[i - 1], nums2[j - 1]);
							else
								max_left = nums1[i - 1];
							if ((m + n) % 2 == 1) { return max_left; }

							min_right = min(nums1[i], nums2[j]);

							return (max_left + min_right) / 2.0;
						}
					}
				}
				else if (i == 0)
				{
					if (j > 0 && nums2[j - 1] > nums1[i])
					{
						iMin = i + 1;
					}
					else
					{
						//满足条件
						int max_left = 0;
						int min_right = 0;
						if (j > 0)
							max_left = nums2[j - 1];
						else if (j == 0)
						{

						}
						if ((m + n) % 2 == 1) { return max_left; }

						if (j == n)
							min_right = nums1[i];
						else
							min_right = min(nums1[i], nums2[j]);

						return (max_left + min_right) / 2.0;
					}
				}
			}
			return 0.0;
		}

		double findMedianSortedArrays2(vector<int>& A, vector<int>& B) {
			int m = A.size();
			int n = B.size();
			if (m > n) { // to ensure m<=n
				return findMedianSortedArrays2(B, A);
			}
			int iMin = 0, iMax = m, halfLen = (m + n + 1) / 2;
			while (iMin <= iMax) {
				/*
				每次循环，i的范围被不断缩小，i位于边界时标志搜索结束；
				i不用每次和0、m比较，而是和iMin、iMax比较，只要知道达到当前边界即可;
				*/
				int i = (iMin + iMax) / 2;
				int j = halfLen - i;
				if (i < iMax && B[j - 1] > A[i]){
					iMin = i + 1; // i is too small
				}
				else if (i > iMin && A[i - 1] > B[j]) {
					iMax = i - 1; // i is too big
				}
				else { // i is perfect
					int maxLeft = 0;
					if (i == 0) { maxLeft = B[j - 1]; }
					else if (j == 0) { maxLeft = A[i - 1]; }
					else { maxLeft = std::max(A[i - 1], B[j - 1]); }
					if ((m + n) % 2 == 1) { return maxLeft; }

					int minRight = 0;
					if (i == m) { minRight = B[j]; }
					else if (j == n) { minRight = A[i]; }
					else { minRight = std::min(B[j], A[i]); }

					return (maxLeft + minRight) / 2.0;
				}
			}
			return 0.0;
		}
	};
	
	class Solution33 {
		/*
		假设按照升序排序的数组在预先未知的某个点上进行了旋转。

		( 例如，数组 [0,1,2,4,5,6,7] 可能变为 [4,5,6,7,0,1,2] )。

		搜索一个给定的目标值，如果数组中存在这个目标值，则返回它的索引，否则返回 -1 。

		你可以假设数组中不存在重复的元素。

		你的算法时间复杂度必须是 O(log n) 级别。

		示例 1:

		输入: nums = [4,5,6,7,0,1,2], target = 0
		输出: 4
		示例 2:

		输入: nums = [4,5,6,7,0,1,2], target = 3
		输出: -1

		来源：力扣（LeetCode）
		链接：https://leetcode-cn.com/problems/search-in-rotated-sorted-array
		著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
		*/
	public:
		static void test()
		{
			Solution33 sol;
			{
				std::vector<int> v{ 5, 1, 3 };
				std::cout << sol.search(v, 3) << std::endl;
			}
		}
		int search_impl(vector<int>& nums, int iMin, int iMax, int target) {
			int len = iMax - iMin + 1;
			int left = iMin, right = iMax;
			while (left <= right)
			{
				int mid = (left + right) / 2;
				int val = nums[mid];
				if (val == target)
					return mid;
				else if (val < target)
				{
					if (mid == iMax)
						break;
					left = mid + 1;
				}
				else
				{
					if (mid == iMin)
						break;
					right = mid - 1;
				}
			}

			return -1;
		}
		int search(vector<int>& nums, int target) {
			if (nums.empty())
				return -1;
			if (nums[0] < nums.back())
			{//没有旋转
				return search_impl(nums, 0, nums.size() - 1, target);
			}
			//首先找到原数组最小值位置
			int l = 0, r = nums.size() - 1;
			while (l < r)
			{
				int mid = (l + r) / 2;
				if (l == mid)
				{//1 = r - l
					if (nums[mid] > nums[r])
						l = r;
					else
						l = mid;
					break;
				}
				if (nums[l] < nums[mid])
				{
					l = mid;
				}
				else
				{//nums[l] > nums[mid]，没有相同元素，不会相等
					r = mid;
				}
			}
			std::cout << "原数组起始位置在 : " << l << std::endl;
			if (target <= nums.back())
			{
				return search_impl(nums, l, nums.size() - 1, target);
			}
			else
			{
				return search_impl(nums, 0, l - 1, target);
			}
		}
	};

	class Solution34 {
		/*
		给定一个按照升序排列的整数数组 nums，和一个目标值 target。找出给定目标值在数组中的开始位置和结束位置。

		你的算法时间复杂度必须是 O(log n) 级别。

		如果数组中不存在目标值，返回 [-1, -1]。

		示例 1:

		输入: nums = [5,7,7,8,8,10], target = 8
		输出: [3,4]
		示例 2:

		输入: nums = [5,7,7,8,8,10], target = 6
		输出: [-1,-1]

		来源：力扣（LeetCode）
		链接：https://leetcode-cn.com/problems/find-first-and-last-position-of-element-in-sorted-array
		著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
		*/
	public:
		static void test()
		{
			Solution34 sol;
			vector<int> nums = {};
			int target = 6;
			vector<int> v = sol.searchRange(nums, target);
			std::cout << "[" << v[0] << "," << v[1] << "]" << std::endl;

			//std::cout << sol.search_bound(nums, 0, nums.size() - 1, target, true) << std::endl;
			//std::cout << sol.search_bound(nums, 0, nums.size() - 1, target, false) << std::endl;
		}
		vector<int> searchRange(vector<int>& nums, int target) {
			//return searchRange(nums, 0, nums.size() - 1, target);
			vector<int> v{ -1, -1 };
			if (nums.empty())
				return v;
			v[0] = search_bound(nums, 0, nums.size() - 1, target, true);
			v[1] = search_bound(nums, 0, nums.size() - 1, target, false);
			return v;
		}

		vector<int> searchRange(vector<int>& nums, int start, int stop, int target) {
			vector<int> v{ -1, -1 };
			if (start > stop)
				return v;

			int i = search(nums, start, stop, target);
			if (i == -1)
				return v;

			v[0] = i;
			v[1] = i;
			if (start < i)
			{
				vector<int> tmp = searchRange(nums, start, i - 1, target);
				if (tmp[0] != -1 && tmp[0] < v[0])
					v[0] = tmp[0];
				if (tmp[1] != -1 && tmp[1] < v[0])
					v[0] = tmp[1];

			}
			if (i < stop)
			{
				vector<int> tmp = searchRange(nums, i + 1, stop, target);
				if (tmp[0] != -1 && tmp[0] > v[1])
					v[1] = tmp[0];
				if (tmp[1] != -1 && tmp[1] > v[1])
					v[1] = tmp[1];
			}
			return v;
		}

		int search(vector<int>& nums, int left, int right, int target) {
			int start = left;
			int stop = right;
			while (start <= stop)
			{
				int t = (start + stop) / 2;
				if (nums[t] == target)
					return t;
				else if (nums[t] < target)
				{
					start = t + 1;
				}
				else
				{
					stop = t - 1;
				}
			}
			return -1;
		}
		int search_bound(vector<int>& A, int left, int right, int target, bool lower_bound)
		{
			int res = -1;
			int l = left;
			int r = right;
			while (l <= r)
			{
				int m = (l + r) / 2;
				if (A[m] == target)
				{
					res = m;//继续找
					if (lower_bound)
						r = m - 1;
					else
						l = m + 1;
				}
				else if (A[m] > target)
				{
					r = m - 1;
				}
				else
				{
					l = m + 1;
				}
			}
			return res;
		}
		int search_left(vector<int>& A, int left, int right, int target)
		{
			int res = -1;
			int l = left;
			int r = right;
			while (l <= r)
			{
				int m = (l + r) / 2;
				if (A[m] == target)
				{
					res = m;//继续找
					r = m - 1;
				}
				else if (A[m] > target)
				{
					r = m - 1;
				}
				else
				{
					l = m + 1;
				}
			}
			return res;
		}

		int search_right(vector<int>& A, int left, int right, int target)
		{
			int res = -1;
			int l = left;
			int r = right;
			while (l <= r)
			{
				int m = (l + r) / 2;
				if (A[m] == target)
				{
					res = m;//继续找
					l = m + 1;
				}
				else if (A[m] > target)
				{
					r = m - 1;
				}
				else
				{
					l = m + 1;
				}
			}
			return res;
		}
	};

	class Solution35 {
		/*
		Given a sorted array and a target value, return the index if the target is found. If not, return the index where it would be if it were inserted in order.

		You may assume no duplicates in the array.

		Example 1:

		Input: [1,3,5,6], 5
		Output: 2
		Example 2:

		Input: [1,3,5,6], 2
		Output: 1
		Example 3:

		Input: [1,3,5,6], 7
		Output: 4
		Example 4:

		Input: [1,3,5,6], 0
		Output: 0

		来源：力扣（LeetCode）
		链接：https://leetcode-cn.com/problems/search-insert-position
		著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
		*/
	public:
		static void test()
		{
			Solution35 sol;
			vector<int> v{};
			int target = 7;
			cout << sol.searchInsert(v, target) << endl;
		}
		int searchInsert(vector<int>& nums, int target) {
			if (nums.size() == 0)
				return 0;
			int left = 0;
			int right = nums.size() - 1;
			while (left <= right)
			{
				int mid = (left + right) / 2;
				if (nums[mid] > target)
				{
					right = mid - 1;
				}
				else if (nums[mid] < target)
				{
					left = mid + 1;
				}
				else
				{
					return mid;
				}
			}
			return left;
		}
	};
	static bool reg_35 = reg_test_func(35, std::bind(&Solution35::test));
	
	class Solution50 {
		/**
		实现 pow(x, n) ，即计算 x 的 n 次幂函数。

		示例 1:

		输入: 2.00000, 10
		输出: 1024.00000
		示例 2:

		输入: 2.10000, 3
		输出: 9.26100
		示例 3:

		输入: 2.00000, -2
		输出: 0.25000
		解释: 2-2 = 1/22 = 1/4 = 0.25
		说明:

		-100.0 < x < 100.0
		n 是 32 位有符号整数，其数值范围是 [−231, 231 − 1] 。

		来源：力扣（LeetCode）
		链接：https://leetcode-cn.com/problems/powx-n
		著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
		*/
	public:
		

		double myPow_positive(double x, int n) {
			if (n < 0)
				return 0;
			if (n == 0)
				return 1;
			std::map<int, double> result_map;
			std::vector<int> pv;
			int p = 1;
			double res = x;
			result_map[p] = res;
			pv.push_back(p);
			while (p <= n / 2)
			{
				p += p;
				res *= res;
				result_map[p] = res;
				pv.push_back(p);
			}

			double r = 1.0f;
			std::vector<int> rv;
			for (int i = 0; i < 32; i++)
			{
				int tmp_p = (1 << i);
				if ((tmp_p & n) == tmp_p)
				{
					r = r * result_map[tmp_p];
				}
			}
			return r;
		}
		double myPow_positive2(double x, int n) {
			if (n < 0)
				return 0;
			if (n == 0)
				return 1;
			double r = 1;
			while (n > 0)
			{
				if ((n & 0x00000001) != 0)
				{
					r *= x;
				}
				x *= x;
				n >>= 1;
			}
			return r;
		}
		double myPow_positive3(double x, int n) {
			if (n < 0)
				return 0;
			if (n == 0)
				return 1.0;
			double d = myPow_positive3(x, n / 2);
			if (n % 2 == 0){
				return d * d;
			}
			else{
				return d * d * x;
			}
		}
		double myPow(double x, int n) {
			if (n == 0)
				return 1;
			else if (n > 0)
				return myPow_positive2(x, n);
			else
			{
				if (n == INT_MIN)
				{
					double r = myPow_positive2(x, INT_MAX);
					r *= x;
					return 1 / r;
				}
				else
				{
					double r = myPow_positive2(x, -n);
					return  1 / r;
				}
			}
		}
		static void test()
		{
			Solution50 inst;
			while (1)
			{
				double x;
				int n;
				std::cin >> x >> n;
				std::cout << "求pow(" << x << "," << n << ")：" << std::endl;
				std::cout << "结果：" << inst.myPow_positive(x, n) << std::endl;
				std::cout << "结果2：" << inst.myPow_positive2(x, n) << std::endl;
				std::cout << "结果2：" << inst.myPow_positive3(x, n) << std::endl;
				//std::cout << "结果：" << inst.myPow(x, n) << std::endl;
				std::cout << "验证：" << std::pow(x, n) << std::endl;
			}
		}
	};
	
	static bool reg_50 = reg_test_func(50, std::bind(&Solution50::test));

	class Solution74 {
	public:
		/*
		Write an efficient algorithm that searches for a value in an m x n matrix. This matrix has the following properties:

		Integers in each row are sorted from left to right.
		The first integer of each row is greater than the last integer of the previous row.
		Example 1:

		Input:
		matrix = [
		[1,   3,  5,  7],
		[10, 11, 16, 20],
		[23, 30, 34, 50]
		]
		target = 3
		Output: true
		Example 2:

		Input:
		matrix = [
		[1,   3,  5,  7],
		[10, 11, 16, 20],
		[23, 30, 34, 50]
		]
		target = 13
		Output: false

		来源：力扣（LeetCode）
		链接：https://leetcode-cn.com/problems/search-a-2d-matrix
		著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
		*/
		bool searchMatrix(vector<vector<int>>& matrix, int target) {
			if (matrix.size() == 0)
				return false;
			if (matrix[0].size() == 0)
				return  false;
			int row = matrix.size();
			int col = matrix[0].size();
			int len = row * col;
			int left = 0, right = len - 1;
			while (left <= right)
			{
				int mid = (left + right) / 2;
				int r = mid / col;
				int l = mid % col;
				if (matrix[r][l] == target)
				{
					return true;
				}
				else if (matrix[r][l] > target)
				{
					right = mid - 1;
				}
				else
				{
					left = mid + 1;
				}
			}
			return false;
		}
		static void test()
		{
			vector <vector<int >> matrix = { { 1, 3, 5, 7 }, { 10, 11, 16, 20 }, { 23, 30, 34, 50 } };
			int target = 13;
			Solution74 sol;
			cout << sol.searchMatrix(matrix, target) << endl;
		}
	};
	static bool reg_74 = reg_test_func(74,std::bind(&Solution74::test));
}