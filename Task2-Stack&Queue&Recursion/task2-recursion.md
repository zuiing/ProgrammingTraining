# <center>  递归练习总结  </center>  

---  
<font size=4>  

使用递归须满足三个条件：  
1）一个问题的解可以分解为几个子问题的解；  
2）这个问题与分解之后的子问题，除了数据规模不同，求解思路完全一样；  
3）存在递归终止条件。  
## 1.编程实现斐波那契数列求值 f(n)=f(n-1)+f(n-2)  
- 递归求解：会出现很多次重复计算，效率极低，Time:O(2^n)  

```  

	long long fibonacci(int n){
		if (n == 1 || n == 2) return 1;
		return fibonacci(n - 1) + fibonacci(n - 2);
	}

```  
  
- 使用三个变量配合：  

```

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

```  
- 还可以数组保存每次计算得到的值


## 2.编程实现求阶乘 n!  

``` 
 	
	int factorial(int n){ //n<=12,计算13!时数据会溢出
		int ans = 1;
		for (int i = 2; i <= n;i++)
		{
			ans *= i;
		}
		return ans;
	}

```

## 3.编程实现一组数据集合的全排列
- **解题分析：** 集合全排列的思想为求a1+(a2,a3,…,an)的全排列，而a1可以与集合中的n个元素进行交换，同理，(a2,a3,…,an)的全排列等于a2+(a3,a4,…,an)的全排列，以此类推，可以写出递归算法

```

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

```

</font>