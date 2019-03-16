#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
//�༭���롪�������㷨ʵ��
string a = "mitcmu";
string b = "mtacnu";
int n = 6, m = 6;//�ֱ�Ϊ�ַ���a��b�ĳ���
int minDist = INT_MAX;
void lwstBT(int i, int j, int edist){
	if (i==n||j==m)
	{
		if (i < n) edist += (n - i);
		if (j < m) edist += (m - j);
		if (edist < minDist) minDist = edist;
		return;
	}
	if (a[i] == b[j])//�����ַ���ƥ��
		lwstBT(i + 1, j + 1, edist);
	else{
		lwstBT(i + 1, j, edist + 1);//ɾ��a[i]����b[j]ǰ���һ���ַ�
		lwstBT(i , j+1 , edist + 1);//ɾ��b[j]��a[i]ǰ���һ���ַ�
		lwstBT(i + 1, j + 1, edist + 1);//��a[i]��b[j]�滻Ϊ��ͬ�ַ�
	}

}

int min(int x, int y, int z){
	int res = INT_MAX;
	if (x < res) res = x;
	if (y < res) res = y;
	if (z < res) res = z;
	return res;
}
//�༭���롪����̬�滮
int lwstDP(string &a,int n,string &b,int m ){
	//int **minDist = new int[n][m];//ֱ������д�ᱨ�������C++������ֱ���ñ�����ά�������������ó���
	int **minDist = new int*[n];
	for (int i = 0; i < n; i++)
		minDist[i] = new int[m];//�ֱ��int*���͵���������ռ䣬��һά����Ķ�̬����
	for (int j = 0; j < m;j++)//��ʼ����0�У�a[0...o]��b[0...j]�ı༭����
	{
		if (a[0] == b[j]) minDist[0][j] = j;
		else if (j != 0) minDist[0][j] = minDist[0][j - 1]+1;
		else
			minDist[0][j] = 1;
	}
	for (int i = 0; i < n;i++)//��ʼ����0�У�a[0...i]��b[0...0]�ı༭����
	{
		if (a[i] == b[0]) minDist[i][0] = i;
		else if (i != 0) minDist[i][0] = minDist[i - 1][0]+1;
		else minDist[i][0] = 1;
	}
	
	for (int i = 1; i < n;i++)
	{
		for (int j = 1; j < m;j++)
		{
			if (a[i] == b[j])
				minDist[i][j] = min(minDist[i - 1][j]+1, minDist[i][j - 1]+1, minDist[i - 1][j - 1]);
			else
				minDist[i][j] = min(minDist[i - 1][j] + 1, minDist[i][j - 1] + 1, minDist[i - 1][j - 1]+1);
		}
	}
	return minDist[n - 1][m - 1];
}
int max(int x, int y, int z){
	int res = INT_MIN;
	if (x > res) res = x;
	if (y > res) res = y;
	if (z > res) res = z;
	return res;
}
//�����������
int lcsDP(string &a, int n, string &b, int m){
	int **maxlcs = new int*[n];
	for (int i = 0; i < n; i++)
		maxlcs[i] = new int[m];
	for (int j = 0; j < m;j++)//��ʼ����0�У�a[0...0]��b[0...j]��maxlcs
	{
		if (a[0] == b[j]) maxlcs[0][j] = 1;
		else if (j!=0) maxlcs[0][j] = maxlcs[0][j - 1];
		else maxlcs[0][j] = 0;
	}
	for (int i = 0; i < n;i++)//��ʼ����0�У�a[0...i]��b[0...0]��mxlca
	{
		if (a[i] == b[0]) maxlcs[i][0] = 1;
		else if (i != 0) maxlcs[i][0] = maxlcs[i - 1][0];
		else maxlcs[i][0] = 0;
	}
	for (int i = 1; i < n;i++)
	{
		for (int j = 1; j < m;j++)
		{
			if (a[i] == b[j]) maxlcs[i][j] = max(maxlcs[i - 1][j], maxlcs[i][j - 1], maxlcs[i - 1][j - 1] + 1);
			else maxlcs[i][j] = max(maxlcs[i - 1][j], maxlcs[i][j - 1], maxlcs[i - 1][j - 1]);
		}
	}
	return maxlcs[n - 1][m - 1];
}
//�����������
int LISDP(vector<int> &nums){
	vector<int> dp(nums.size(), 1);
	int res=0;
	for (int i = 0; i < nums.size();i++)
	{
		for (int j = 0; j < i;j++)
		{
			if (nums[j] < nums[i])
				dp[i] = max(dp[i], dp[j] + 1);
		}
		res = max(res, dp[i]);
	}
	return res;
}
int main(){
	/*lwstBT(0,0,0);
	cout << minDist;*///result:3

	/*cout << lwstDP(a, 6, b, 6);*/
	/*string s1 = "abcbdab";
	string s2 = "bdcaba";
	cout<<lcsDP(s1, 7, s2, 6);*///result:4

	vector<int> nums = { 10, 9, 2, 5, 3, 7, 101, 18 };
	cout << LISDP(nums);//result:4

	return 0;
}