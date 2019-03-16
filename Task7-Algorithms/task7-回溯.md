# <center>  回溯  </center>

---  
<font size=4>  
## 1.回溯思想  
>回溯的处理思想，有些类似枚举搜索。我们枚举所有的解，找到满足期望的解。为了有规律的枚举所有可能的解，避免遗漏和重复，可以把问题求解的过程分为多个阶段，每个阶段，都会面对一个岔路口，现随意选一条路走，当发现这条路走不通时，就回退到上一个岔路口，另选一种走法继续。回溯就是可以无限次重来。    

## 1.八皇后问题 
**问题分析：**  该题经典解法就是回溯递归，一层一层地向下扫描，需要用到一个字符串数组cur，其中cur[i]表示第i列皇后的位置，初始化为'.'，然后从0开始递归，每一行都依次遍历各列，判断如果在该位置放置皇后会不会有冲突，以此类推，当最后一行的皇后放好后，一种解法就诞生了，将其存入结果res中，然后再还会继续完成搜索所有的情况。  
```

	class Solution {
	public:
	    vector<vector<string>> solveNQueens(int n) {
	        vector<vector<string>> res;
	        vector<string> cur(n,string(n,'.'));//将n*n的二维数组初始化为'.'，并用来记录每一行皇后的位置
	        solveNQueensDFS(cur,0,res);
	        return res;
	    }
	    void solveNQueensDFS(vector<string> &cur,int row,vector<vector<string>> &res){
	        if(row==cur.size()){
	            res.push_back(cur);
	            return;
	        }
	        for(int col=0;col<cur.size();col++){
	            if(isValid(cur,row,col)){
	                cur[row][col]='Q';
	                solveNQueensDFS(cur,row+1,res);
	                cur[row][col]='.';
	            }
	        }
	    }
	    bool isValid(vector<string> &cur,int row,int col){
	        for(int i=0;i<row;i++)//列
	            if(cur[i][col]=='Q') return false;
	        //左对角线上半部分
	        for(int i=row-1,j=col-1;i>=0&&j>=0;i--,j--)
	            if(cur[i][j]=='Q') return false;
	        //右对角线上半部分
	        for(int i=row-1,j=col+1;i>=0&&j<cur.size();i--,j++)
	            if(cur[i][j]=='Q') return false;
	        return true;
	    }
	};
```


## 2.0-1背包问题   
**问题描述：** 有一个背包，背包总的承载重量是Wkg。现在有n个物品，每个物品的重量不等，并且不可分割，现在期望选择几件物品，装在到背包中，在不超过所能装在重量的前提下，如何让背包中物品的总重量最大？（如果物品可分割，可用贪心算法，但现在物品不可分割，要么装要么不装，所以叫0-1背包问题）   
**解题思路：** 对于每个物品来说，都有两种选择，装或不装。对于n个物品，总的装法有x^n种去掉总重量超过Wkg的，从剩下的装法中选择总重量最接近Wkg的。这里就可以用回溯的方法，把物品一次排列，整个问题就分为了n个阶段，每个阶段对应一个物品怎么选。     
```

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
	
	
	int main(){
	
		vector<int> items = {5,3,9,8,11};
		package_01(0, 0, items, 5, 35);
		cout << "maxW=" << maxW << endl;//result:33
	
		return 0;
	}
```

</front>