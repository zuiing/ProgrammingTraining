#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
//编辑距离——回溯算法实现
string a = "mitcmu";
string b = "mtacnu";
int n = 6, m = 6;//分别为字符串a和b的长度
int minDist = INT_MAX;
void lwstBT(int i, int j, int edist){
	if (i==n||j==m)
	{
		if (i < n) edist += (n - i);
		if (j < m) edist += (m - j);
		if (edist < minDist) minDist = edist;
		return;
	}
	if (a[i] == b[j])//两个字符串匹配
		lwstBT(i + 1, j + 1, edist);
	else{
		lwstBT(i + 1, j, edist + 1);//删除a[i]或者b[j]前添加一个字符
		lwstBT(i , j+1 , edist + 1);//删除b[j]或a[i]前添加一个字符
		lwstBT(i + 1, j + 1, edist + 1);//将a[i]和b[j]替换为相同字符
	}

}

int min(int x, int y, int z){
	int res = INT_MAX;
	if (x < res) res = x;
	if (y < res) res = y;
	if (z < res) res = z;
	return res;
}
//编辑距离——动态规划
int lwstDP(string &a,int n,string &b,int m ){
	//int **minDist = new int[n][m];//直接这样写会报编译错误，C++不允许直接用变量做维数声明，必须用常量
	int **minDist = new int*[n];
	for (int i = 0; i < n; i++)
		minDist[i] = new int[m];//分别给int*类型的数组申请空间，即一维数组的动态申请
	for (int j = 0; j < m;j++)//初始化第0行：a[0...o]与b[0...j]的编辑距离
	{
		if (a[0] == b[j]) minDist[0][j] = j;
		else if (j != 0) minDist[0][j] = minDist[0][j - 1]+1;
		else
			minDist[0][j] = 1;
	}
	for (int i = 0; i < n;i++)//初始化第0列：a[0...i]与b[0...0]的编辑距离
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
//最长公共子序列
int lcsDP(string &a, int n, string &b, int m){
	int **maxlcs = new int*[n];
	for (int i = 0; i < n; i++)
		maxlcs[i] = new int[m];
	for (int j = 0; j < m;j++)//初始化第0行：a[0...0]和b[0...j]的maxlcs
	{
		if (a[0] == b[j]) maxlcs[0][j] = 1;
		else if (j!=0) maxlcs[0][j] = maxlcs[0][j - 1];
		else maxlcs[0][j] = 0;
	}
	for (int i = 0; i < n;i++)//初始化第0列：a[0...i]和b[0...0]的mxlca
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
//最长递增子序列
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