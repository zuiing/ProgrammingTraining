# <center>  递归  </center>

---  
<font size=4>  

## 1.爬楼梯(LeetCode 70)  
**问题描述：**  每次可以爬1或2个台阶，需要n步才能到达顶部。其实就是斐波那契数列。  
**(1)递归实现**  超时！  
```

	class Solution {
	public:
	    int climbStairs(int n) {
	        if(n<=2) return n;
	        return climbStairs(n-1)+climbStairs(n-2);
	    }
	};
```

**(2)循环** 借助数组记录中间值或定义两个变量。  
```

	class Solution {
	public:
	    int climbStairs(int n) {
	        vector<int> res(n+1,1);
	        for(int i=2;i<=n;i++)
	            res[i]=res[i-1]+res[i-2];
	        return res[n];
	    }
	};
```

## 2.第五天递归任务复习  



</front>