#include <iostream>

using namespace std;
#define n 4
struct MinHeapNode 
{
	int element;//待排序元素
	int i;//数组索引，element是从哪个数组取得
	int j;//元素索引，下一个element
};
//定义一个最小节点之间的比较函数
void swap(MinHeapNode *x, MinHeapNode *y){
	MinHeapNode t = *x; *x = *y; *y = t;
}

class MinHeap{
private:
	MinHeapNode *hArr;//指向最小堆的堆顶元素
	int size;//堆大小
public:
	MinHeap(MinHeapNode a[], int size);
	//调整堆 调整给定根节点的字数结构
	void MinHeapify(int i);
	//取堆顶元素
	MinHeapNode getMin(){
		return hArr[0];
	}
	//替换根节点，重新调整堆
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
	//2*i+1左子节点下标  2*i+2为右子节点下标
	int minpos = i;
	if ((2 * i + 1) < size&&hArr[2 * i + 1].element < hArr[i].element) minpos = 2 * i + 1;
	if ((2 * i + 2) < size&&hArr[2 * i + 2].element < hArr[minpos].element) minpos = 2 * i + 2;
	if (i != minpos){
		swap(hArr[i], hArr[minpos]);
		MinHeapify(minpos);//这里使用递归，当然也可以直接使用循环实现
	}
}
int* mergeKSortedArrays(int arr[][n],int k){
	int *output = new int[n*k];//保存排序结果
	//创建一个大小为k的最小堆，最终元素为k的数组中的每个数组的第一个元素
	MinHeapNode *harr = new MinHeapNode[k];
	for (int i = 0; i < k;i++)
	{
		harr[i].element = arr[i][0];
		harr[i].i = i;//当前数组索引
		harr[i].j = 1;//该数组下一个元素的索引(判断元素是否用完)
	}
	MinHeap hp(harr, k);//对上述大小为k的数组建堆
	//逐次取出堆顶元素，存入数组中，并将其替换为所在数组的下一元素
	for (int count = 0; count < n*k;count++)
	{
		//取堆顶，存结果
		MinHeapNode root = hp.getMin();
		output[count] = root.element;
		//替换堆顶
		if (root.j < n)
		{
			root.element = arr[root.i][root.j];
			root.j++;
		}
		else //数组元素取完了，设堆顶元素为无穷大
			root.element = INT_MAX;
		//如果还有元素，就替换堆顶元素，调整堆结构
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
		cout << output[i] << " ";//输出结果为：1 2 6 9 12 20 22 33 34 99 100 222
	}
	return 0;
}