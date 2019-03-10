# <center>  LeetCode练习  </center>

---  
<font size=4>  

## 1.哈希表(下面两题要求用哈希思想实现)
- 两数之和(1)  

```  

	//Time:O(n)
	//Space:O(n)
	class Solution {
	public:
	    vector<int> twoSum(vector<int>& nums, int target) {
	        unordered_map<int,int> record;
	        
	        for(int i=0;i<nums.size();i++){
	            int complement=target-nums[i];
	            if(record.find(complement)!=record.end()){
	                int res[]={record[complement],i};
	                return vector<int>(res,res+2);
	            }            
	            record[nums[i]]=i;
	        }
	        return vector<int> {0};
	    }
	};
```

- Happy Number(202)  

```  

	class Solution {
	public:
	    bool isHappy(int n) {
	        unordered_map<int,int> record;
	        while(n!=1){
	            if(record[n]==0) record[n]++;
	            else return false;
	            int sum=0;
	            while(n){
	                sum+=pow(n%10,2);
	                n/=10;
	            }
	            n=sum;
	        }
	        return true;
	    }
	};  
``` 

## 2.字符串  
- Reverse String  
[反转字符串](https://leetcode.com/problems/reverse-string/)   
**思路：**  直接从两头往中间走，交换两边的字符即可。  

```

	class Solution {
	public:
	    void reverseString(vector<char>& s) {
	        int left=0,right=s.size()-1;
	        while(left<right){
	            swap(s[left++],s[right--]);
	        }
	    }
	};
```


- Reverse Words in a String  
[反转字符串中的单词](https://leetcode.com/problems/reverse-words-in-a-string/)  
**问题分析：**  反转字符串中的单词，如果单词之间遇到多个空格，只能返回一个，而且首尾不能有空格，对C语言程序员要求空间复杂度为O(1)，因此只能对原字符串s之间做修改。  
**解法一思路：** 定义一些辅助变量，storeIndex表示当前存储到的位置，n表示字符串长度。首先将整个字符串反转，然后循环字符串，遇到空格直接跳过，如果是非空格字符，此时看storeIndex是否为0，为0的话表示第一个单词，不用增加空格；如果不为0，说明不用第一个单词，在此过程中继续覆盖原字符串，找到结束位置了，就来反转这个单词，然后更新i为结尾位置，遍历结束后将字符串裁剪到storeIndex位置，就可以得到我们需要的结果。  

```

	class Solution {
	public:
	    string reverseWords(string s) {
	        int storeIndex=0,n=s.size();
	        reverse(s.begin(),s.end());
	        for(int i=0;i<n;i++){
	            if(s[i]!=' '){
	                if(storeIndex!=0) s[storeIndex++]=' ';
	                int j=i;
	                while(j<n&&s[j]!=' ') s[storeIndex++]=s[j++];
	                reverse(s.begin()+storeIndex-(j-i),s.begin()+storeIndex);
	                i=j;
	            }
	        }
	        s.resize(storeIndex);
	        return s;
	    }
	};
```

**解法二：字符串流类stringstream**  ，把字符串装在如字符串流中，然后定义一个临时变量tmp，然后把第一个单词赋给s，这里需要注意的是如果含有非空格字符，那么每次>>操作就会提取连在一起的非空格字符，那么我们每次将其加在s前面即可；如果原字符串为空，那么就不会进入循环；如果原字符串为许多空格字符连在一起，那么第一个>>操作就会提取出这些空格字符放入s中，然后不进入while循环，这时只要判断s的首字符是否为空格字符，是的话就将s清空即可，代码如下：   

```

	class Solution {
	public:
	    string reverseWords(string s) {
	        istringstream is(s);
	        string tmp;
	        is>>s;//先把第一个单词赋值给s，不然最后会存在一个空格
	        while(is>>tmp) s=tmp+" "+s;
	        if(!s.empty()&&s[0]==' ') s="";
	        return s;
	    }
	};
```

**解法三：字符串流类stringstream及getline**  ，getline使用时可以设定分隔符，我们用空格来分隔，这个和上面的>>不同的是每次只能过一个空格，如果有多个空格字符连在一起，那么t会被赋值为空字符串，所以在处理t时要首先判断是否为空，是的话直接跳过代码如下：  

```

	class Solution {
	public:
	    string reverseWords(string s) {
	        istringstream is(s);
	        s="";
	        string tmp="";
	        while(getline(is,tmp,' ')){
	            if(tmp.empty()) continue;
	            s= s.empty() ? tmp:(tmp+" "+s);    //避免末尾出现空格      
	        } 
	        return s;
	    }
	};
```

- String to Integer (atoi)  
[字符串转整数](https://leetcode.com/problems/string-to-integer-atoi/)  
**问题分析：**  字符串转为整数是很常用的一个函数，由于输入的是字符串，所以需要考虑的情况有很多，但是本题只需考虑数字和符号的情况：  
(1)若字符串开头为空格，则跳过所有空格，到第一个非空格字符，如果没有，则返回0；  
(2)若第一个非空格字符是符号+/-，则标记sign的真假，该题有个局限性，在C++中，+-1和-+1都是被认可的，都是-1，但本题则会返回0；   
(3)若下一个字符不是数字，则返回0，完全不考虑小数点和自然数的情况；    
(4)如果下一个字符是数字，则转换为整型存下来，若接下来再有非数字出现，则返回目前的结果；  
(5)还需考虑边界问题，如果超过了整型数的范围，则用边界值替代当前值。  

```
	
	class Solution {
	public:
	    int myAtoi(string str) {
	        if(str.empty()) return 0;
	        int sign=1,base=0,i=0,n=str.size();
	        while(i<n&&str[i]==' ') i++;//找到第一个非空格字符
	        if(i<n&&(str[i]=='-'||str[i]=='+'))
	            sign=(str[i++]=='+'?1:-1);//判断正负
	        while(i<n&&str[i]>='0'&&str[i]<='9'){
	            if(base> INT_MAX/10||(base==INT_MAX/10&&str[i]-'0'>7)){
	                return (sign==1)?INT_MAX:INT_MIN;//超出整数范围
	            }
	            base=10*base+(str[i++]-'0');//这里的小括号一定要加上
	        }
	        return base*sign;
	    }
	};

```

- Valid Number  
[验证数字](https://leetcode.com/problems/valid-number/)  
**问题分析：**  该题很复杂，所要关注的除了数字以外的特殊字符有空格、小数点、自然数e/E、正负号-/+,除了这些字符需要考虑以外，出现了任何其他的字符，可以马上判定不是数字。下面将具体分析出现了这些可能是数字的特殊字符：  
(1)空格' ':空格分两种情况，一种是出现在开头和末尾的空格，一种是出现在中间的空格。出现在开头和末尾不影响数字，而一旦中间出现了空格，则立马不是数字。解决方法：预处理时去掉字符的首尾空格，中间再检测到空格，则判定不是数字。    
(2)小数点'.':小数点要分的情况很多，首先的是小数点只能出现一次，但是小数点可以出现在任何位置，开头(".2"),中间("1.e2"),末尾("1.")，但需注意的是，小数点不能出现在自然数e/E后面，如"2e.2"false,"1e1.1"false。还有，当小数点出现在末尾时，前面必须是数字，如"1."true,"-."flase。解决方法：开头中间结尾三个位置分开讨论。    
(3)自然数e/E:自然数前后必须有数字，即自然数不能出现在开头和结尾，如"e"false,".e1"false,"2.e"false,"2.e1"true。而且小数点只能出现在自然数之前，还有自然数前面不能是符号，如"+e1"false,"1+e"false。解决方法：开头中间结尾分开讨论。    
(4)正负号-/+:正负号可以在开头出现，可以在自然数e/E后面出现，但是不能是最后一个字符，后面得有数字，如"+1.e+5"true。解决方法：开头中间结尾分开讨论。   
**开头中间结尾讨论：**  
1.在讨论之前先做预处理，去掉字符串首位的空格，可以采用两个指针分别指向开头和结尾，遇到空格则跳过，分别只想开头结尾非空格的字符。  
2.对首字符进行处理，首字符只能为数字或正负号，需要定义三个flag标示我们是否之气检测过小数点、自然数和正负号。首字符如为数字或正负号，则标记对应的flag，若不是直接返回flase。  
3.对中间字符的处理，中间字符会出现五种情况：数字、小数点、自然数、正负号、其他字符  
>若是数字，标记flag并通过；  
>若是自然数，则必须是第一个出现自然数，并且前一个字符不能是正负号，而且之前一定要出现过数字，才能标记flag通过；  
>若是正负号，则之前的字符必须是自然数e，才能标记通过；  
>若是小数点，则必须是第一次出现小数点，并且自然数没有出现过，才能标记flag通过；  
>若是其他，返回false。  

4.对尾字符处理，最后一个字符只能是数字或小数点，其他字符都返回false。
>若是数字，返回true；  
>若是小数点，则必须是第一次出现小数点，并且自然数没有出现过，还有前面必须是数字，才能返回true。  




</front>