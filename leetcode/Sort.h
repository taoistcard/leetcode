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
			
			int provit = arr[left]; //�����׼ֵ
			unsigned i = left, j = right; // i��ʼ��һ����λ
			while (i < j)
			{
				while (i < j && arr[j] >= provit) //�Ӻ���ǰ�ҵ���һ�����ڻ�׼��λ��
				{
					--j;
				}
				if (i < j)
				{
					arr[i] = arr[j]; //j����ֵ�ŵ�i���Ŀ�λ����ʱ��j����һ����λ��i����Чλ
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
					arr[j] = arr[i]; //i�ճ���
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