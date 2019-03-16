# <center>  LeetCode练习  </center>

---  
<font size=4>  

## 1.Letter Combinations of a Phone Number(17)  [电话号码的字母组合](https://leetcode.com/problems/letter-combinations-of-a-phone-number/)  
<img src="./pic/leetcode17.JPG">  

**问题分析：**  求电话号码的字母组合，即数字2-9中每个数字可以代表若干个字母，然后给一串数字，求出所有可能的组合。  
**解题思路：**  用递归求解，需要建立一个字典，用来保存每个数字所代表的字符串，然后我们还需要一个变量level，记录当前生成的字符串的字符个数。在递归函数中，首先判断level，如果和digits中数字的个数相等了，就将当前的组合加入结果res中，然后返回。否则通过digits中的数字到dict中取出字符串，然后遍历这个取出的字符串，将每个字符都加到当前的组合后面，并调用递归函数即可。  
```

	class Solution {
	public:
	    vector<string> letterCombinations(string digits) {
	        if(digits.empty()) return {};
	        vector<string> res;
	        string dict[]={"","","abc","def","ghi","jkl","mno","pqrs","tuv","wxyz"};
	        lettersCombinationsDFS(digits,dict,0,"",res);
	        return res;
	    }
	    void lettersCombinationsDFS(string &digits,string dict[],int level,string out,vector<string> &res){
	        if(level==digits.size()){
	            res.push_back(out);return ;
	        }
	        string str=dict[digits[level]-'0'];
	        for(int i=0;i<str.size();i++){
	            lettersCombinationsDFS(digits,dict,level+1,out+str[i],res);
	        }
	    }
	};
```  

## 2.permutations(46)  [全排列](https://leetcode.com/problems/permutations/)  
**解题思路：**  每次交换nums数组里面的两个数字，经过递归生成所有的排列情况。
```

	class Solution {
	public:
	    vector<vector<int>> permute(vector<int>& nums) {
	        vector<vector<int>> res;
	        permuteDFS(nums,0,res);
	        return res;
	    }
	    void permuteDFS(vector<int> &nums,int start,vector<vector<int>> &res){
	        if(start>=nums.size()) res.push_back(nums);
	        for(int i=start;i<nums.size();i++){
	            swap(nums[start],nums[i]);
	            permuteDFS(nums,start+1,res);
	            swap(nums[start],nums[i]);
	        }
	    }
	};
```

## 3.Regular Expression Matching  [正则表达式匹配](https://leetcode.com/problems/regular-expression-matching/)  
**问题分析：**  正则表达式匹配的问题，*表示之前那个字符可以有0个或多个，就是说，字符串a*b，可以表示ab或aaaaab,即a的个数任意，这道题要分的情况 稍复杂，用递归求解。  
**思路：**   
>- 若p为空，若s也为空，返回true，反之返回false；  
>- 若p的长度为1，s长度也为1，且相同或是p为'.',则返回true，反之返回false；  
>- 若p的第二个字符不为*，若此时s为空返回false，否则判断字符是否匹配，且从各自的第二个字符开始调用递归函数匹配； 
>- 若p的第二个字符为*，进行下列循环，条件是若s不为空且首字符匹配(包括P[0]为'.'),调用递归函数匹配s和去掉前两个字符的p(这样做的原因是假设此时的星号的作用是让前面的字符出现0次，验证是否匹配)，若匹配返回true，否则s去掉首字母(因此此时首字母匹配了，我们可以去掉s的首字母而p由于星号的作用，可以有任意个首字母，所以不需要去掉)，继续进行循环。  
>- 返回调用递归函数匹配s和去掉前两个字符的p的结果(这么做的原因是处理星号无法匹配的内容，比如s="ab",p="a*b",直接进入while循环后，我们发现"ab"和"b"不匹配。所以s变成"b"，那么此时跳出循环后，就到最后的return来比较"b"和"b"了，返回true。再举个例子，比如s="",p="a*",由于s为空，不会进入任何的if和while，只能到最后的return来比较了，返回true)。   
```

	class Solution {
	public:
	    bool isMatch(string s, string p) {
	        if(p.empty()) return s.empty();
	        if(p.size()==1){
	            return s.size()==1 && (s[0]==p[0]||p[0]=='.');
	        }
	        if(p[1]!='*'){
	            if(s.empty()) return false;
	            return (s[0]==p[0]||p[0]=='.') && isMatch(s.substr(1),p.substr(1));
	        }
	        //此时p的第二个字符为*
	        while(!s.empty()&&(s[0]==p[0]||p[0]=='.')){
	            //这里又分析了两种情况，假设星号的作用是让前面的字符出现0次，验证是否匹配
	            if(isMatch(s,p.substr(2))) return true;
	            //s去掉首字母，而p由于星号的作用，可以有任意个首字母，所以不需要去掉，继续进行循环，
	            s=s.substr(1);
	        }
	        return isMatch(s,p.substr(2));
	    }
	};
```


## 4.Minimum Path Sum  [最小路径和](https://leetcode.com/problems/minimum-path-sum/)  
**说明：**  在任务动态规划中已经完成。  

## 5.Coin Change  [硬币找零](https://leetcode.com/problems/coin-change/)  
**问题分析：**  这道题给了我们一些可用的硬币值，又给了一个钱数，求最少能拿用几个硬币来找零。根据题目中的例子可知，不是每次都会给全1,2,5的硬币，有时候没有1分硬币，那么有的钱数就没法找零，需要返回-1；  
对于求极值问题，主要考虑动态规划，这样可以保留一些中间状态的计算值，可以避免大量的重复计算。  
**解题思路：**  
>- 维护一个一维动态数组dp，其中dp[i]表示钱数为i时的最小硬币数的找零，由于数组下标从0开始，所以要申请一位，数组大小为amount+1，这样最终结果就可以保存在sp[amount]中了；  
>- 初始化sp[0]=0,因为目标值若为0，就不需要硬币了 ，其他值可以初始化为amount+1，因为最小的硬币是1，所以amount最多徐娅amount个硬币，amount+1也就是当前的最大值了；  
>- 找状态转移方程：假设我们取一个值为5的硬币，由于目标值是11，所以加入我们知道dp[6]那么就知道组成11的dp值了！所以我们更新dp[i]的方法就是遍历每个硬币，如果遍历到的硬币值小于i值(比如我们不能用值5的硬币去更新dp[3])时，我们用dp[i-coins[j]]+1来更新dp[i]，所以状态转移方程为：dp[i]=min(dp[i],dp[i-coins[j]]+1);其中coins[j]为第j个硬币，而i-coins[j]为钱数i减去其中一个硬币的值，剩余的钱数在dp数组中找得到值，然后加1和当前dp数组中的值做比较，取较小的那个更新dp数组。  

```

	class Solution {
	public:
	    int coinChange(vector<int>& coins, int amount) {
	        vector<int> dp(amount+1,amount+1);
	        dp[0]=0;
	        for(int i=1;i<=amount;i++){
	            for(int j=0;j<coins.size();j++){
	                if(coins[j]<=i)
	                    dp[i]=min(dp[i],dp[i-coins[j]]+1);
	            }
	        }
	        return dp[amount]>amount ? -1 : dp[amount];
	    }
	};
```

## 6.Best Time to Buy and Sell Stock   [买卖股票的最佳时机](https://leetcode.com/problems/best-time-to-buy-and-sell-stock/)
**问题分析：**  该题只允许买卖股票各一次，因此只需要遍历一次数组，用一个变量记录遍历国数中的最小值，然后每次计算当前值和这个最小值之间的差值为利润，然后每次选较大的利润来更新，当遍历完成后当前利润即为所求：  
```

	class Solution {
	public:
	    int maxProfit(vector<int>& prices) {
	        int res=0,buy=INT_MAX;
	        for(int i=0;i<prices.size();i++){
	            buy=min(buy,prices[i]);
	            res=max(res,prices[i]-buy);    
	        }
	        return res;
	    }
	};
```

## 7.Maximum Product Subarray  [最大子数组乘积](https://leetcode.com/problems/maximum-product-subarray/)  
**问题分析：**  这个求最大子数组乘积问题是由最大子数组之和问题演变而来，但是比求最大子数组之和要复杂，因为再求和时，遇到0不会改变最大值，遇到负数也只是会减小最大值而已；而在求最大子数组乘积的问题中，遇到0会使整个乘积变为0，而遇到负数，则会使最大乘积变成最小乘积；  
**解题思路：**  最先想到的就是暴力枚举，现有一个数组[2,3,-2,4],找出所有的子数组，然后算出每一个子数组的乘积，然后比较找出最大的一个，需要两层循环，外层for遍历整个数组，内层for遍历含有当前数字的子数组，就是按照以下顺序找出子数组[2],[2,3],[2,3,-2],[2,3,-2,4], [3],[3,-2],[3,-2,4], [-2],[-2,4], [4].时间复杂度为O(n^2)。  
还有一种方法就是用DP来做，要用两个dp数组，其中f[i]表示子数组[0,i]范围内并且一定包含nums[i]数字的最大子数组乘积，g[i]表示子数组[0,1]范围内并且一定包含nums[i]数字的最小数组乘积，初始化时f[0]和g[0]都初始化为nums[0],其余都为0，那么从数组的第二个数字开始遍历，此时的最大值和最小值只会在这三个数字之间产生，即f[i-1]*nums[i],g[i-1]*nums[i]和nums[i]。所以我们用三者中的最大值来更新f[i],用最小值更新g[i]，然后用f[i]来更新结果res即可，由于最终的结果不一定会包括nums[n-1]这个数字，所以f[n-1]不一定是最终解，不断更新的结果res才是。  
```

	class Solution {
	public:
	    int maxProduct(vector<int>& nums) {
	        int res=nums[0],n=nums.size();
	        vector<int> f(n,0),g(n,0);
	        f[0]=nums[0];g[0]=nums[0];
	        for(int i=1;i<n;i++){
	            f[i]=max(max(f[i-1]*nums[i],g[i-1]*nums[i]),nums[i]);
	            g[i]=min(min(f[i-1]*nums[i],g[i-1]*nums[i]),nums[i]);
	            res=max(res,f[i]);
	        }
	        return res;
	    }
	};
```


## 8.Triangle [三角形最小路径和](https://leetcode.com/problems/triangle/)
**问题分析：** 给一个二维数组组成的三角形，让我们寻找一条自上而下的路径，使得路径和最短。若是用暴力枚举，那么遍历所有的路径的化，就是阶乘级的时间复杂度，不可取。再看贪婪算法，每次只要选下一层相邻的两个数字中较小的一个，似乎就能得到答案，其实是不对的，贪婪算法可以得到局部最优，但不能保证全局最优，很有可能在其他分支的底层的数字变得非常小，但是贪婪算法已经将其他所有分支剪掉了。因此只能使用DP了。  
**方法一：**   不新建dp数组，直接复用triangle数组，我们希望一层一层的累加下来，从而使得triangle[i][j]是从最顶层到(i,j)位置的最小路径和，那么来看如何求状态转移方程：因为每个节点能往下走的只有跟它相邻的两个位置，那么每个位置(i,j)也就只能从上层跟它相邻的两个位置过来，即(i-1,j-1)和(i-1,j)这两个位置，DP方程为：triangle[i][j]=min(triangle[i-1][j-1],triangle[i-1][j]);从第二行开始更新，注意两边的数字直接赋值上一行的边界值，那么最终我们只要在最底层找出最小值，就是全局最小的路径和啦！  
```

	class Solution {
	public:
	    int minimumTotal(vector<vector<int>>& triangle) {
	        for(int i=1;i<triangle.size();i++){
	            for(int j=0;j<triangle[i].size();j++){
	                if(j==0) 
	                    triangle[i][j]+=triangle[i-1][j];
	                else if(j==triangle[i].size()-1)
	                    triangle[i][j]+=triangle[i-1][j-1];
	                else
	                    triangle[i][j]+=min(triangle[i-1][j-1],triangle[i-1][j]);
	            }
	        }
	        return *min_element(triangle.back().begin(), triangle.back().end());
	    }
	};
```

**方法二：**  新建一个dp数组，赋值三角形最后一行，作为用来更新的一维数组。然后遍历这个DP数组，对于每个数组，和它之后的元素比较选择较小的再加上上面一行想邻位置的元素作为新的元素，然后一层一层向上扫描，整个过程和，冒泡排序原理差别不多，最后最小的元素都冒到前面，第一个元素即为所求。  
```

	class Solution {
	public:
	    int minimumTotal(vector<vector<int>>& triangle) {
	        vector<int> dp(triangle.back());
	        for(int i=triangle.size()-2;i>=0;i--){
	            for(int j=0;j<=i;j++)
	                dp[j]=min(dp[j],dp[j+1])+triangle[i][j];
	        }
	        return dp[0];
	    }
	};
```



</front>