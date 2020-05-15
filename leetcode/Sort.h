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
	};

	static void test_sort()
	{
		srand(time(NULL));
		std::vector<int> arr;
		while (arr.size() < 10)
		{
			arr.push_back(rand() % 100);
		}
		CSort::quick_sort(arr, 0, arr.size()-1);
		CSort::print_arr(arr);

		std::sort(arr.begin(), arr.end());
		CSort::print_arr(arr);
	}
}