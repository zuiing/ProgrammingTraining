#include <iostream>

using namespace std;
#define n 4
struct MinHeapNode 
{
	int element;//������Ԫ��
	int i;//����������element�Ǵ��ĸ�����ȡ��
	int j;//Ԫ����������һ��element
};
//����һ����С�ڵ�֮��ıȽϺ���
void swap(MinHeapNode *x, MinHeapNode *y){
	MinHeapNode t = *x; *x = *y; *y = t;
}

class MinHeap{
private:
	MinHeapNode *hArr;//ָ����С�ѵĶѶ�Ԫ��
	int size;//�Ѵ�С
public:
	MinHeap(MinHeapNode a[], int size);
	//������ �����������ڵ�������ṹ
	void MinHeapify(int i);
	//ȡ�Ѷ�Ԫ��
	MinHeapNode getMin(){
		return hArr[0];
	}
	//�滻���ڵ㣬���µ�����
	void replaceMin(MinHeapNode x){
		hArr[0] = x; MinHeapify(0);
	}
};

MinHeap::MinHeap(MinHeapNode a[], int size)
{
	this->size = size;
	hArr = a;
	int i = (size - 1) / 2;
	while (i>=0)
	{
		MinHeapify(i);
		i--;
	}
}
void MinHeap::MinHeapify(int i)
{
	//2*i+1���ӽڵ��±�  2*i+2Ϊ���ӽڵ��±�
	int minpos = i;
	if ((2 * i + 1) < size&&hArr[2 * i + 1].element < hArr[i].element) minpos = 2 * i + 1;
	if ((2 * i + 2) < size&&hArr[2 * i + 2].element < hArr[minpos].element) minpos = 2 * i + 2;
	if (i != minpos){
		swap(hArr[i], hArr[minpos]);
		MinHeapify(minpos);//����ʹ�õݹ飬��ȻҲ����ֱ��ʹ��ѭ��ʵ��
	}
}
int* mergeKSortedArrays(int arr[][n],int k){
	int *output = new int[n*k];//����������
	//����һ����СΪk����С�ѣ�����Ԫ��Ϊk�������е�ÿ������ĵ�һ��Ԫ��
	MinHeapNode *harr = new MinHeapNode[k];
	for (int i = 0; i < k;i++)
	{
		harr[i].element = arr[i][0];
		harr[i].i = i;//��ǰ��������
		harr[i].j = 1;//��������һ��Ԫ�ص�����(�ж�Ԫ���Ƿ�����)
	}
	MinHeap hp(harr, k);//��������СΪk�����齨��
	//���ȡ���Ѷ�Ԫ�أ����������У��������滻Ϊ�����������һԪ��
	for (int count = 0; count < n*k;count++)
	{
		//ȡ�Ѷ�������
		MinHeapNode root = hp.getMin();
		output[count] = root.element;
		//�滻�Ѷ�
		if (root.j < n)
		{
			root.element = arr[root.i][root.j];
			root.j++;
		}
		else //����Ԫ��ȡ���ˣ���Ѷ�Ԫ��Ϊ�����
			root.element = INT_MAX;
		//�������Ԫ�أ����滻�Ѷ�Ԫ�أ������ѽṹ
		hp.replaceMin(root);
	}
	return output;
}

int mainMergeKArray(){
	int arr[][n] = { { 2, 6, 12, 34 },
	{ 1, 9, 20, 100 },
	{ 22, 33, 99, 222 } };
	int k = sizeof(arr) / sizeof(arr[0]);
	int *output = mergeKSortedArrays(arr, k);
	cout << "Merged Array is \n";
	for (int i = 0; i < n*k; i++)
	{
		cout << output[i] << " ";//������Ϊ��1 2 6 9 12 20 22 33 34 99 100 222
	}
	return 0;
}