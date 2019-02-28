#include <iostream>
using namespace std;
void mergSortedArray(int *n1,int *n2,int len1,int len2,int *ans){
	int i = 0, j = 0, k = 0;
	while (i<len1&&j<len2)
	{
		if (n1[i] < n2[j] && i < len1){
			ans[k++] = n1[i++];
		}
		else if(j<len2){
			ans[k++] = n2[j++];
		}
	}
	while (i<len1) ans[k++] = n1[i++];
	while (j<len2) ans[k++] = n2[j++];
}
int main3(int argv, char *argc[]){
	int n1[5] = { 1, 3, 5, 7, 9 };
	int n2[8] = { 0, 2, 4, 6, 8, 10, 11, 12 };
	int ans[50] = { 0 };
	mergSortedArray(n1, n2, 5,8,ans);
	int len = (sizeof(n1)+sizeof(n2)) / sizeof(int);
	cout << "result:\n";
	for (int i = 0; i < len;i++)
	{
		cout << ans[i] << ' ';
	}
	return 0;
}