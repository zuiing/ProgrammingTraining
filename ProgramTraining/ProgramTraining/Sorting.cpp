#include <iostream>
#include <vector>
#include "stdlib.h"
#include <time.h>
#include <iterator>
#include <algorithm>
#include <queue>
#include <functional>
using namespace std;

int partition(vector<int> &A, int start, int end){
	int i = start, j = end, pivot = A[end];
	while (i != j)
	{
		while (A[i] <= pivot&&i < j) i++;
		while (A[j] >= pivot&&i < j) j--;
		if (i < j)
			swap(A[i], A[j]);
	}
	swap(A[i], A[end]);
	return i;
}
void quickSort(vector<int> &A,int start,int end){
	if (start >= end) return;
	int pos = partition(A, start, end);
	quickSort(A, start, pos - 1);
	quickSort(A, pos+1, end);
}

void merge(vector<int> &A, int start,int mid, int end){
	int *tmp = new int[end-start+1];
	int i = start, j = mid + 1, k = 0;
	while (i<=mid&&j<=end)
	{
		if (A[i] < A[j])
			tmp[k++] = A[i++];
		else
			tmp[k++] = A[j++];
	}
	while (i <= mid) tmp[k++] = A[i++];
	while (j <= end) tmp[k++] = A[j++];

	//将排序后的元素覆盖到元素组
	for (i = 0; i < k; i++)
		A[start+i] = tmp[i];
	delete tmp;
}
void mergeSort(vector<int> &A, int start, int end){
	if (start >= end) return;
	int mid = (start + end) / 2;
	mergeSort(A, start, mid);
	mergeSort(A, mid + 1, end);
	merge(A,start,mid,end);
}

void bubbleSort(vector<int> &A){
	for (int i = 0; i < A.size();i++)
	{
		for (int j = 0; j < A.size()-i-1;j++)
		{
			if (A[j] > A[j+1])
				swap(A[j], A[j+1]);
		}
	}
}
void selectSort(vector<int> &A){
	for (int i = 0; i < A.size(); i++)
	{
		int min_idx = i;
		for (int j = i+1; j < A.size(); j++)
		{
			if (A[j] < A[min_idx])
				min_idx = j;
		}
		swap(A[i], A[min_idx]);
	}
}
void insertionSort(vector<int> &A){
	for (int i = 1; i < A.size();i++)
	{
		int tmp = A[i];
		int j = i - 1;//查找插入位置
		for (; j >= 0;j--)
		{
			if (A[j]>tmp)
				A[j + 1] = A[j];//数据移动
			else
				break;
		}
		A[j + 1] = tmp;//数据插入
	}
}

//堆排序
void heapify(vector<int> &A,int n,int i){//从上到下
	while (true)
	{
		int maxpos = i;
		if (i * 2 <= n&&A[i] < A[i * 2]) maxpos = i*2;
		if ((i * 2 + 1 )<= n&&A[maxpos] < A[i * 2 + 1]) maxpos = i * 2 + 1;
		if (maxpos==i) break;//满足父子节点关系，堆化完成
		swap(A[maxpos],A[i]);
		i = maxpos;
	}
}
void buildHeap(vector<int>& A,int  n){
	for (int i = n / 2; i >= 1;i--)
	{
		heapify(A, n, i);
	}
}
void heapSort(vector<int>& A,int n){
	buildHeap(A,n);
	int k = n;
	while (k>1)
	{
		swap(A[1], A[k]);
		k--;
		heapify(A, k, 1);
	}
}
//求数组中第k大元素
int findKthLargest1(vector<int>&A,int k)
{
	sort(A.begin(), A.end());
	return A[A.size()-k];
}
int findKthLargest2(vector<int>&A, int k)
{
	priority_queue<int> q(A.begin(), A.end());
	for (int i = 0; i < k - 1; i++)
	{
		q.pop();
	}
	return q.top();
}
int partition_(vector<int> &A, int left, int right){
	if (left >= right) return left;
	int pivot = A[left], i = left + 1, j = right;
	while (i!=j)
	{
		while (i < j&&A[j] <= pivot) j--;
		while (i < j&&A[i] >= pivot) i++;
		if (i < j) swap(A[i], A[j]);
	}
	swap(A[left], A[i]);
	return i;
}
int findKthLargest3(vector<int>&A, int k){
	int left = 0, right = A.size() - 1;
	while (true)
	{
		int pos = partition_(A, left, right);
		if (pos == k - 1) return A[pos];
		else if (pos > k - 1) right=pos-1;
		else left = pos + 1;
	}
}
int main0(){
	vector<int> A(8);
	srand((unsigned)time(0));
	cout << "排序前：";
	for (int i = 0; i < 8;i++)
	{
		A[i] = rand() % 100;
		cout << A[i] << ' ';
	}
	cout << endl;
	cout << "第3大元素为：" << findKthLargest3(A, 3)<<endl;

	cout << "排序后：";
	sort(A.begin(), A.end(),greater<int>());
	for (vector<int>::iterator iter = A.begin() ; iter != A.end(); iter++)
	{
		cout << *iter << ' ';
	}
	return 0;
}