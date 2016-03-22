// File:        sorting.cpp
// Author:      Geoffrey Tien
//              Meihui Yan & Jiameng Duan
// Date:        2016-02-22
// Description: Skeleton file for CMPT 225 assignment #3 sorting functions and helpers
//              Function bodies to be completed by you!

// Complete your sorting algorithm function implementations here
#include<iostream>
#include<string>
#include<stdlib.h>
using namespace std;
//empty,only one, only two,equal
// Selection Sort
// 
template <class T>
int SelectionSort(T arr[], int n)
{
	int count = 0; 
	for (int i = 0; i < n - 1; ++i)
	{
		int smallest = i;
		// Find the index of the smallest element
		for (int j = i + 1; (count++ > -1)&&(j < n); ++j)
		{
			if (arr[j] < arr[smallest])
			{
				smallest = j;
			}
		}
		// Swap the smallest with the current item
		T temp = arr[i];
		arr[i] = arr[smallest];
		arr[smallest] = temp;
	}
	return count;
}


//Quick Sort
	template <class T>
	int Quicksort(T arr[], int n)
	{
		int count = 0;
		QuicksortHelper(arr, 0, n - 1, count);
		return count;
	}

	template <class T>
	void QuicksortHelper(T arr[], int low, int high, int& counter)
	{
		if (low < high)
		{
			int pivot = QSPartition(arr, low, high, counter);
			QuicksortHelper(arr, low, pivot - 1, counter);
			QuicksortHelper(arr, pivot + 1, high, counter);
		}
	}

	template <class T>
	int QSPartition(T arr[], int low, int high, int& counter)
	{
		T pivot = arr[high];
		T temp;
		int i = low;
		int j = high - 1;
		while ((counter++ >= 0) && i < j)
		{
			//counter++;
			if (arr[i]>pivot && arr[j]<pivot)
			{
				//swap low and high
				temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
				i++;
				j--;
			}
			else if (arr[i] <= pivot)
				i++;
			else if (arr[j] > pivot)
				j--;
		}
		int pivotindex;
		if (arr[i] > pivot)   //The remianing item is larger than the pivot value, swap it with pivot
		{
			temp = arr[i];
			arr[i] = arr[high];
			arr[high] = temp;
			pivotindex = i;
		}
		else {                           //The remianing item is larger than the pivot value, swap it with pivot
			temp = arr[i + 1];
			arr[i + 1] = arr[high];
			arr[high] = temp;
			pivotindex = i + 1;
		}
		return pivotindex;
	}

	// Randomized Quicksort
	// 
	template <class T>
	int RQuicksort(T arr[], int n)
	{
		int count = 0;
		int Low = 0;
		int High =n - 1;
		RQuicksortHelper(arr, Low, High, count);

		return count;
	}

	template <class T>
	void RQuicksortHelper(T arr[], int low, int high, int& counter)
	{

		if (low < high)
		{
			int pivot = RQSPartition(arr, low, high, counter);
			RQuicksortHelper(arr, low, pivot - 1, counter);
			RQuicksortHelper(arr, pivot + 1, high, counter);
		}
	}

	template <class T>
	int RQSPartition(T arr[], int low, int high, int& counter)
	{
		int random_pos = rand() % (high - low + 1) + low; // Pick a random pivot index
		int pivotindex;
		T pivot = arr[random_pos];
		T temp;
		temp = arr[random_pos];
		arr[random_pos] = arr[high];
		arr[high] = temp;  //change the position of the one on random position with high

						   // same algorithm as QSPartition. 
		int i = low;
		int j = high - 1;
		while ((counter++ > -1)&&i < j)
		{
			if (arr[i]>pivot && arr[j]<pivot)
			{
				//swap low and high
				temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
				i++;
				j--;
			}
			else if (arr[i] <= pivot)
				i++;
			else if (arr[j] > pivot)
				j--;
		}
		if (arr[i] > pivot)  //The remianing item is larger than the pivot value, swap it with pivot
		{
			temp = arr[i];
			arr[i] = arr[high];
			arr[high] = temp;
			pivotindex = i;
		}
		else {
			temp = arr[i + 1]; //The remianing item is smaller than the pivot value, swap the next itemq with pivot
			arr[i + 1] = arr[high];
			arr[high] = temp;
			pivotindex = i + 1;
		}
		return pivotindex;
	}

	// Mergesort
	template <class T>
	int Mergesort(T arr[], int n)
	{
		int count = 0;
		int low = 0;
		int high = n - 1;
		MergesortHelper(arr, low, high, n, count);
		return count;
	}

	template <class T>
	void MergesortHelper(T arr[], int low, int high, int n, int& counter)
	{
		if (low < high)//array has more than 1 element
		{
			int mid = low + (high - low) / 2;
			MergesortHelper(arr, low, mid, n, counter);//left half
			MergesortHelper(arr, mid + 1, high, n, counter);//right half
			Merge(arr, low, mid, high, n, counter);
		}


	}

	template <class T>
	void Merge(T arr[], int low, int mid, int high, int n, int& counter)
	{
		int left = low;
		int length = high - low + 1;
		int right = mid + 1;
		T* temp = new T[length];
		int i = 0;
		while ((counter++>(-1))&& left <= mid && right<=high)
		{
			if (arr[left]<arr[right])
				temp[i] = arr[left++];
			else
				temp[i] = arr[right++];
			i++;
		}
		if (left < mid + 1)   //copy rest of the left array or right array to temp array
			for (int j = i; (counter++>(-1)) && (j < length); j++)
			{
				temp[j] = arr[left++];
			}
		else if (right <= high)
			for (int j = i;(counter++>(-1)) &&(j < length); j++)
			{
				
				temp[j] = arr[right++];
			}
		int j = low;
		for (int i = 0; i < length; i++, j++)
		{
		
			arr[j] = temp[i];
		}
		delete[]temp;
	}

	// Shell Sort
	template <class T>
	int ShellSort(T arr[], int n)
	{
		int count = 0;
		int gap, i, j;
		T temp;
		for (gap = n / 2; gap > 0; gap /= 2)
			for (i = gap; i < n; i++)
			{
				for (j = i - gap; (count++>-1)&&(j >= 0)&&(arr[j] > arr[j + gap]); j -= gap)
				{
					temp = arr[j];
					arr[j] = arr[j + gap];
					arr[j + gap] = temp;
				}
			}

		return count;
		// Reference: copied from : http://www.cplusplus.com/forum/general/123961/
	}