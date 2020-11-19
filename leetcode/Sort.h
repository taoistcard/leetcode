#pragma once
#include <vector>
#include <iostream>
namespace CppTest
{
	//static void print_arr(int arr[], int len)
	//{
	//	for (unsigned int i = 0; i < len; i++)
	//	{
	//		std::cout << arr[i] << "\t";
	//	}
	//}
	//
	class CSort
	{
	public:
		static void print_arr(std::vector<int>& arr)
		{
			for (unsigned int i = 0; i < arr.size(); i++)
			{
				std::cout << arr[i] << "\t";
			}
			std::cout << std::endl;
		}

		static void quick_sort(std::vector<int>& arr, int left, int right)
		{
			if (right <= left)
				return;
			
			int provit = arr[left]; //保存基准值
			unsigned i = left, j = right; // i初始是一个空位
			while (i < j)
			{
				while (i < j && arr[j] >= provit) //从后往前找到第一个大于基准的位置
				{
					--j;
				}
				if (i < j)
				{
					arr[i] = arr[j]; //j处的值放到i处的空位，此时，j成了一个空位，i是有效位
					++i;
				}
				if (i >= j)
					break;
				while (i < j && arr[i] <= provit)
				{
					++i;
				}
				if (i < j)
				{
					arr[j] = arr[i]; //i空出来
					--j;
				}
			}
			arr[i] = provit;
			quick_sort(arr, left, i - 1);
			quick_sort(arr, i + 1, right);
		}

		static void quick_sort1(vector<int>& nums, int l, int r)
		{
			if (l >= r)
				return;
			int n = nums[l];
			int i = l, j = r;
			while (i < j)
			{
				while (nums[j] >= n && i < j)
					--j;
				if (i < j)
				{
					nums[i] = nums[j];
					++i;
				}
				while (nums[i] <= n && i < j)
					++i;
				if (i < j)
				{
					nums[j] = nums[i];
					--j;
				}
			}
			nums[i] = n;
			quick_sort1(nums, l, i - 1);
			quick_sort1(nums, i + 1, r);
		}
	};

	static void test_sort()
	{
		srand(time(NULL));
		std::vector<int> arr = { 4       ,9       ,4       ,5       ,0        };
		while (arr.size() < 5)
		{
			arr.push_back(rand() % 10);
		}
		CSort::print_arr(arr);
		
		CSort::quick_sort1(arr, 0, arr.size() - 1);
		CSort::print_arr(arr);

		std::sort(arr.begin(), arr.end());
		CSort::print_arr(arr);
	}
}