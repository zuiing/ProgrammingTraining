#include <iostream>
#include <vector>
using namespace std;
int num;//全局变量

void merge(vector<int> &a,int left,int mid,int right){
	int i = left, j = mid + 1,k=0;
	int *tmp = new int[right - left + 1];
	while (i<=mid&&j<=right){
		if (a[i] <= a[j])
			tmp[k++] = a[i++];
		
		else{		
			tmp[k++] = a[j++]; 
			num += (mid - i + 1);//统计right-left之间，比a[j]大的元素的个数
		}
	}
	while (i <= mid)
		tmp[k++] = a[i++];
		
	while (j <= right) 
		tmp[k++] = a[j++];
		
	for (i = 0; i < k; i++)
		a[left + i] = tmp[i];
		
}
void mergeSortCounting(vector<int> &a, int left, int right){
	if (left >= right) return;
	int mid = (left + right) / 2;
	mergeSortCounting(a, left, mid);
	mergeSortCounting(a, mid + 1, right);
	merge(a, left, mid, right);
}
int count(vector<int> &a){
	num = 0;
	mergeSortCounting(a, 0, a.size() - 1);
	return num;
}
int maindivideAndConquer(){
	vector<int> a = { 1, 6, 5, 4, 3, 2 };

	cout << count(a) << endl;//result:10
	for (auto it = a.begin(); it != a.end();it++)
	{
		cout << *it << " ";
	}
	return 0;
}