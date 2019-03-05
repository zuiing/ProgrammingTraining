#include <iostream>
#include "time.h"
#include <vector>
#include <algorithm>
using namespace std;

int find(vector<int> &A,int target){
	int left = 0, right = A.size() - 1;
	while (left<=right)
	{
		int mid = left + (right - left) / 2 ;
		if (A[mid] == target) return mid;
		else if (A[mid] > target) right = mid - 1;
		else left = mid + 1;
	}
	return -1;
}
int findNoLessThanTarget(vector<int> &A,int target){
	int left = 0, right = A.size() ;
	while (left< right)
	{
		int mid = left + (right - left)/2;
		if (A[mid] < target) 
			left = mid + 1;
		else
			right = mid;
	}
	return left;
}

int main1(){
	vector<int> A(10);
	srand((unsigned)time(0));
	
	for (int i = 0; i < A.size(); i++)
	{
		A[i] = rand() % 100;
	}
	sort(A.begin(), A.end());
	cout << "�������飺";
	for (int i = 0; i < A.size(); i++)
	{
		cout << A[i] << ' ';
	}cout << endl;
	int target;
	cout << "������Ҫ���ҵ����֣�" << endl;
	cin >> target;
	//cout<<"Ҫ���ҵ������±�Ϊ��"<<find(A, target);
	cout<<"�����е�һ����С��"<<target<<"�������±�Ϊ��"<<findNoLessThanTarget(A, target);
	//test2
	vector<int>B = { 0, 1, 1, 1, 1 };
	cout << findNoLessThanTarget(B, 1);
	return 0;
}