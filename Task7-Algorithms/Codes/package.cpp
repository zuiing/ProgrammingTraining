#include <iostream>
#include <vector>
using namespace std;

int maxW = INT_MIN;
//cw��ʾ��ǰ�Ѿ�װ��ȥ����Ʒ�������ͣ�i��ʾ��������Ʒ�����������ֵ
//w����������items��ʾÿ����Ʒ��������n��ʾ��Ʒ����
//���豳���ɳ�������100����Ʒ����10����Ʒ�����洢������a�У��ǿ����������ú���f(0,0,10,100)
void package_01(int i,int cw,vector<int> &items,int n,int w){
	if (cw==w||i==n)//cw==w��ʾװ����i==n��ʾ������������Ʒ
	{
		if (cw > maxW) maxW = cw;
		return;
	}
	package_01(i + 1, cw, items, n, w);
	if (cw+items[i]<=w)//�Ѿ�����������������ʱ�Ͳ�Ҫ��װ��
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