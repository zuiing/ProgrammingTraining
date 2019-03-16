#include <iostream>
#include <vector>
using namespace std;

int maxW = INT_MIN;
//cw表示当前已经装进去的物品的重量和；i表示背包中物品总重量的最大值
//w背包重量；items表示每个物品的重量；n表示物品个数
//假设背包可承受重量100，物品个数10，物品重量存储在数组a中，那可以这样调用函数f(0,0,10,100)
void package_01(int i,int cw,vector<int> &items,int n,int w){
	if (cw==w||i==n)//cw==w表示装满；i==n表示考察完所有物品
	{
		if (cw > maxW) maxW = cw;
		return;
	}
	package_01(i + 1, cw, items, n, w);
	if (cw+items[i]<=w)//已经超过背包承受重量时就不要再装了
	{
		package_01(i + 1, cw + items[i],items, n, w);
	}
}


int mainpackage(){

	vector<int> items = {5,3,9,8,11};
	package_01(0, 0, items, 5, 35);
	cout << "maxW=" << maxW << endl;//result:33

	return 0;
}