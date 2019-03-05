# <center>  LeetCode练习  </center>

---  
<font size=4>  

## 1.Sqrt(x) (x的平方根) ,找最后一个不大于目标值的数     
[Sqrt(x)](https://leetcode.com/problems/sqrtx/)  
**问题分析：**  leetCode上面的返回值为整型，若mid刚好为x的平方根，则返回mid即可，否则返回最大的平方根小于x的数。  
```

	class Solution {
	public:
	    int mySqrt(int x) {
	        if(x==0||x==1) return x;
	        int l=0,r=x,mid,ans;
	        while(r>=l){
	            mid=(r+l)>>1;
	            if(mid==x/mid) return mid;
	            else if(mid>x/mid) r=mid-1;
	            else {
	                l=mid+1;ans=mid;
	            }
	        }
	        return ans;
	    }
	};
```

**返回值为小数的做法：**  上述函数一点儿也不适用，下面将写出返回小数的做法，精度precision为1e-5.  
(1)二分查找做法：  
```

	double mySqrt(double x,double precision){
		double l = 0, r = x,mid;
		while ((r - l)>precision)
		{
			mid = (l + r) / 2;		
			if (mid > x / mid) r = mid;
			else l = mid;
		}
		return l;
	}
  
```  

(2)牛顿迭代：  
<img src="./pic/task3-Newton'sMethod.jpg">

```  

	double mySqrt2(double x, double precision){
		double r = x;
		while ((r*r - x)>precision)
		{
			r = (r + x / r) / 2;
		}
		return r;
	}
```

</font>