#include <iostream>
#include <vector>
using namespace std;
//�����ִ��������е�λ��
int bf(string &main, string &pattern){
	int n = main.size();
	int m = pattern.size();
	if (n < m) return -1;
	else if (n == m) return 0;
	for (int i = 0;i<(n-m+1);i++)
	{
		for (int j = 0; j < m;j++)
		{
			if (main[i + j] == pattern[j]){
				if (j == m - 1)  return i;
			}else 
				break;
		}
	}
	return -1;
}
int simpleHash(string &s,int start,int end){
	/*
	**�����Ӵ��Ĺ�ϣֵ��ÿ���ַ�ȡASCII�����
	*/
	int ret = 0;
	for (int i = start; i <= end;i++)
	{
		ret += (s[i] = 'a');
	}
	return ret;
}
//int rk(string &main, string &pattern){
//	int n = main.size();
//	int m = pattern.size();
//	if (n < m) return -1;
//	else if (n == m) return 0;
//	//�Ӵ���ϣֵ��
//	vector<int> hash_memo;
//	hash_memo.push_back(simpleHash(main, 0, m - 1));
//	for (int i = 1; i<(n - m + 1);i++)
//	{
//		int tmp = hash_memo[i - 1] - simpleHash(main, i - 1, i - 1) + simpleHash(main, i + m - 1, i + m - 1);
//		hash_memo.push_back(tmp);
//	}
//	//ģʽ����ϣֵ
//	int hash_p = simpleHash(pattern, 0, m - 1);
//
//	for (int i=)
//	{
//	}
//}
int main0(){
	string main = "abdcabcdefg";
	string pattern = "abcde";
	cout << bf(main, pattern);//���Ϊ4
	return 0;
}