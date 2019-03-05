# <center>  二分查找  </center>

---  
<font size=4>  

## 1.实现一个有序数组的二分查找算法    
**问题分析：**  从数组中查找与目标值完全相等的数，并返回下标。代码如下：  
```

	int find(vector<int> &A,int target){
		int left = 0, right = A.size() - 1;
		while (left<=right)
		{
			int mid = left + (right - left) / 2 ;
			if (A[mid] == target) return mid;
			else if (A[mid] > target) right = mid - 1;
			else left = mid + 1;
		}
		return -1;
	}

```
**总结：** 上述写法并不唯一，若right的初始化写成A.size()，那么判断条件必须用left<right,right的赋值必须写成right=mid,若写成right=mid-1;则会出错。  

## 2.实现模糊二分查找算法(查找第一个不小于目标值的数，改题也可变形为查找最后一个小于目标值的数)    
**问题分析：**  这是比较常见的一类问题，因为要查找的目标值不一定会在数组中出现，也有可能是跟目标值相同的值在数组中并不唯一，而是有多个，那么在这种情况下A[mid]==target，这条语句就没必要了。若在数组[2,4,6,9]中查找3，则返回数字4的位置；在数组[0,1,1,1,1]中查找1，则返回第一个数字1的位置1。代码如下：    
```

	int findNoLessThanTarget(vector<int> &A,int target){
		int left = 0, right = A.size() ;
		while (left< right)
		{
			int mid = left + (right - left)/2;
			if (A[mid] < target) 
				left = mid + 1;
			else
				right = mid;
		}
		return left;
	}

```
## 3.实现模糊二分查找算法(查找第一个大于目标值的数，可变形为查找最后一个不大于目标值的数)    
**问题分析：**  查找第一个大于目标值的数，STL中也有专门的函数upper_bound；将问题2中的条件A[mid] < target改成A[mid] <= target，就能使得数组中有很多跟目标值相同的数字存在的情况下，返回最后一个相同数字的下标。比如数组[2,4,5,6,9]中查找3，则返回 数字4的位置，这跟上面的查找方式返回结果相同，因为数字4在此数组中既是第一个不小于3的值，也是第一个大于目标值的数；在数组[0,1,1,1,1]中查找1，则返回下标5。  
```

	int findNoLessThanTarget(vector<int> &A,int target){
		int left = 0, right = A.size() ;
		while (left< right)
		{
			int mid = left + (right - left)/2;
			if (A[mid] <= target) 
				left = mid + 1;
			else
				right = mid;
		}
		return left;
	}
```

**总结：** 这一类可以轻松变形为查找最后一个不大于目标值的数。目前已经找到了第一个大于目标值的数，那么再往前一位，返回right-1，就是最后一个不大于目标数的数，如在数组[0,1,1,1,1]中查找1，就会返回最后一个数字1的位置4。  


</font>