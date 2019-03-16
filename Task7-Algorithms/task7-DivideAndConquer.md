# <center>  分治  </center>

---  
<font size=4>  

## 1.分治算法  
**分治算法是一种处理问题的思想，递归是一种编程技巧。**  实际上，分治算法一般都比较适合用递归来实现。分治算法的递归实现中，每一层递归都会设计这样三个操作：  

- 分解：将原问题分解成一系列子问题；  
- 解决：递归求解各个子问题，若子问题足够小，则直接求解；  
- 合并：将子问题的结果合并成原问题。  

## 2.求一组数据的逆序对个数  
**(1)问题分析：**  假设有n个数据，我们期望数据从小到大排列，那完全有序的数据的有序度就是n(n-1)/2,逆序度等于0；相反，倒序排列的数据的有序度为0，逆序度是n(n-1)/2。除了这两种极端情况，我们通过计算有序对或者逆序对的个数，来表示数据的有序度或逆序度。    

**(2)解题思路：** 
>- 最笨的方法就是，拿每个数字跟它后面的数字比较，看有几个比它小的。我们把比他小的数字个数记作k，通过这样的方式，把每个数字都考察一遍，然后对每个数字对应的k值求和，最后得到的总和就是逆序对数。这样操作的时间复杂度为O(n^2).
>- 分治算法思路：用分治的思想来求数组A的逆序对个数。可以将数组分成前后两半A1和A2，分别计算A1和A2的逆序对个数K1和K2,然后在计算A1和A2之间的逆序对个数K3.那么数组A的逆序对个数就是K1+K2+K3。
```

	#include <iostream>
	#include <vector>
	using namespace std;
	int num;//全局变量
	
	void merge(vector<int> &a,int left,int mid,int right){
		int i = left, j = mid + 1,k=0;
		int *tmp = new int[right - left + 1];
		while (i<=mid&&j<=right){
			if (a[i] <= a[j])
				tmp[k++] = a[i++];
			
			else{		
				tmp[k++] = a[j++]; 
				num += (mid - i + 1);//统计right-left之间，比a[j]大的元素的个数
			}
		}
		while (i <= mid)
			tmp[k++] = a[i++];
			
		while (j <= right) 
			tmp[k++] = a[j++];
			
		for (i = 0; i < k; i++)
			a[left + i] = tmp[i];
			
	}
	void mergeSortCounting(vector<int> &a, int left, int right){
		if (left >= right) return;
		int mid = (left + right) / 2;
		mergeSortCounting(a, left, mid);
		mergeSortCounting(a, mid + 1, right);
		merge(a, left, mid, right);
	}
	int count(vector<int> &a){
		num = 0;
		mergeSortCounting(a, 0, a.size() - 1);
		return num;
	}
	int main(){
		vector<int> a = { 1, 6, 5, 4, 3, 2 };
	
		cout << count(a) << endl;//result:10
		for (auto it = a.begin(); it != a.end();it++)
		{
			cout << *it << " ";
		}
		return 0;
	}
```


</front>