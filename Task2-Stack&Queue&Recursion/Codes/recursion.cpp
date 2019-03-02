#include <iostream>
using namespace std;
int fibonacci(int n){
	if (n == 1 || n == 2) return 1;
	return fibonacci(n - 1) + fibonacci(n - 2);
}
int fibonacci2(int n){
	int a = 0, b = 1, tmp;
	if (n == 0) return 0;
	for (int i = 1; i < n;i++)//循环n-1次
	{
		tmp = a + b;
		a = b;
		b = tmp;
	}
	return  b;
}
int factorial(int n){
	int ans = 1;
	for (int i = 2; i <= n;i++)
	{
		ans *= i;
	}
	return ans;
}
void swap(int &a, int &b){ 
	if (a == b) return;//防止&a、&b指向同一个地址,因为和自身异或会变0
	a ^=b;
	b ^=a;
	a ^=b;
}
void permutation(int *a,int k,int m){
	if (k == m){
		for (int i = 0; i <= m;i++)
		{
			cout << a[i] << ' ';
		}cout << endl;
	}
	else{
		for (int i = k; i <= m;i++)
		{
			swap(a[k], a[i]);//固定一个数
			permutation(a, k + 1, m);//求剩余数的全排列
			swap(a[k], a[i]);//完成递归后交换回来
		}
	}
}
int main(int argv, char *argc[]){
	
	int a[4] = { 1, 2,3,4};
	permutation(a, 0, 3);//下标从0~n-1
	return 0;
}