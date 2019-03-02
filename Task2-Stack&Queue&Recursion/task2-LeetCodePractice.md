# <center>  LeetCode练习  </center>
---  
<font size=4>  
## 1.Valid Parentheses（有效的括号）  
[Valid Parentheses](https://leetcode.com/problems/valid-parentheses/)  
- **问题分析：**  字符串包括()[]{}，需要用一个栈。  
1）遍历字符串，若当前字符为左边括号，则将其压入栈中；  
2）若遇到右半边括号时，若此时栈为空，则直接返回false；若不为空，则取出栈顶元素，若对应的左半边括号，则继续循环，否则返回false。  

```

	class Solution {
	public:
	    bool isValid(string s) {
	        stack<char> rec;
	        int i=0;
	        while(s[i]!='\0'){
	            if(s[i]=='('||s[i]=='['||s[i]=='{')
	                rec.push(s[i]);
	            else if(!rec.empty()){
	                if(s[i]==')'&&rec.top()=='(')
	                    rec.pop();
	                else if(s[i]==']'&&rec.top()=='[')
	                    rec.pop();
	                else if(s[i]=='}'&&rec.top()=='{')
	                    rec.pop();
	                else 
	                    return false;
	            }else
	                return false;
	            i++;
	        }
	        return !rec.empty();
	    }
	};

```
## 2.Longest Valid Parentheses（最长有效的括号）
[longest-valid-parentheses](https://leetcode.com/problems/longest-valid-parentheses/)  
- **问题分析：**  借助栈求解，还需要定义一个start变量来记录合法字符串的起始位置。  
1)遍历字符串，遇到左括号，将当前下标压入栈；  
2)若遇到右括号：若当前栈为空，将下一个坐标记录到start；若栈不为空，则将栈顶元素取出，此时若栈为空，则更新结果和i-start+1的最大值，否则更新结果和i-栈顶元素的最大值。   

```

	class Solution {
	public:
	    int longestValidParentheses(string s) {
	        stack<int> record;
	        int res=0,start=0;
	        for(int i=0;i<s.size();i++){
	            if(s[i]=='(') record.push(i);
	            else{
	                if(record.empty()) start=i+1;
	                else{
	                    record.pop();
	                    res=record.empty()?max(res,i-start+1):max(res,i-record.top());
	                }
	            }
	        }
	        return res;
	    }
	};

```
## 3.Evaluate Reverse Polish Notatio（逆波兰表达式求值）  
[evaluate-reverse-polish-notation](https://leetcode.com/problems/evaluate-reverse-polish-notation/)  
逆波兰表达式就是把操作数放前面，操作符后置的一种写法，通过观察可以发现，第一个出现的运算符其前面必有两个数字，当这个运算符和之前两个数字完成运算后从原数组中删去，把得到的一个新的数字插入到原来的位置，继续作战相同运算，直至整个数组变成一个数字。  
- **方法一：**  使用栈保存数字。在了LeetCode上运行超时。  
1）从前往后遍历数组，遇到数组压入栈中，遇到符号，则把栈顶的两个数字拿出来运算，把结果压入栈，直到遍历完整个数组，栈顶元素即为最终答案。
  
```

	class Solution {
	public:
	    int evalRPN(vector<string>& tokens) {
	        if(tokens.size()==1) return stoi(tokens[0]);
	        stack<int> st;
	        for(int i=0;i<tokens.size();i++){
	            if(tokens[i]>="0"&&tokens[i]<="9") st.push(stoi(tokens[i]));
	            else{
	                int num1=st.top();st.pop();
	                int num2=st.top();st.pop();
	                if(tokens[i]=="+") st.push(num2+num1);
	                else if(tokens[i]=="-") st.push(num2-num1);
	                else if(tokens[i]=="*") st.push(num2*num1);
	                else if(tokens[i]=="/") st.push(num2/num1);
	            }
	        }
	        return st.top();        
	    }
	};

```

- **方法2：**  使用递归，借助一个辅助函数完成。   
1）由于一个有效的逆波兰表达式的末尾必定是操作符，因此要从末尾开始处理；  
2）若遇到操作符，向前两个位置调用递归函数，找出前面两个数字，然后进行操作价格结果返回，如果遇到的数字直接返回即可，代码如下：  

```

	class Solution {
	public:
	    int evalRPN(vector<string>& tokens) {
	        int op=tokens.size()-1;
	        return helper(tokens,op);
	    }
	    int helper(vector<string>& tokens,int& op){
	        string str=tokens[op];
	        //str为数字则返回，为符号时才能开始运算
	        if(str!="+"&&str!="-"&&str!="*"&&str!="/") return stoi(str);
	        int num1=helper(tokens,--op);
	        int num2=helper(tokens,--op);
	        if(str=="+") return num2+num1;
	        if(str=="-") return num2-num1;
	        if(str=="*") return num2*num1;
	        return num2/num1;        
	    }
	};

```

## 4.Design Circular Deque（设计一个双端队列）  
[design-circular-deque](https://leetcode.com/problems/design-circular-deque/)  

- **方法一：**  使用vector容器的push_back()、pop_back()、front()、back()、erase()、insert()函数实现双端队列的插入和删除，实现起来简单。代码如下：  

```

	class MyCircularDeque {
	public:
	    /** Initialize your data structure here. Set the size of the deque to be k. */
	    MyCircularDeque(int k) {
	        size=k;
	    }
	    
	    /** Adds an item at the front of Deque. Return true if the operation is successful. */
	    bool insertFront(int value) {
	        if(isFull()) return false;
	        data.insert(data.begin(),value);
	        return true;
	    }
	    
	    /** Adds an item at the rear of Deque. Return true if the operation is successful. */
	    bool insertLast(int value) {
	        if(isFull()) return false;
	        data.push_back(value);
	        return true;
	    }
	    
	    /** Deletes an item from the front of Deque. Return true if the operation is successful. */
	    bool deleteFront() {
	        if(isEmpty()) return false;
	        data.erase(data.begin());
	        return true;
	    }
	    
	    /** Deletes an item from the rear of Deque. Return true if the operation is successful. */
	    bool deleteLast() {
	        if(isEmpty()) return false;
	        data.pop_back();
	        return true;
	    }
	    
	    /** Get the front item from the deque. */
	    int getFront() {
	        if(isEmpty()) return -1;
	        return data.front();
	    }
	    
	    /** Get the last item from the deque. */
	    int getRear() {
	        if(isEmpty()) return -1;
	        return data.back();
	    }
	    
	    /** Checks whether the circular deque is empty or not. */
	    bool isEmpty() {
	        return data.size()==0;
	    }
	    
	    /** Checks whether the circular deque is full or not. */
	    bool isFull() {
	        return data.size()>=size;
	    }
	private:
	    vector<int> data;
	    int size;
	};

```

- **方法二：**  使用vector或数组实现，利用环形队列的性质，除了使用size记录环形队列的最大长度的最大长度外，还要用到front、rear、cnt分别记录队首位置、队尾位置和当前队列中元素的个数。  
1）将front初始化为k-1，rear初始化为0；  
2)判空就看当前cnt是否为0；判满就看cnt是否等于size；  
3）取首位元素，先判空，然后根据front和rear分别向后和向前移动一位取即可，须使用循环数组的性质，对size取余；  
4）删除末尾元素，先判空，然后将rear向前移动一位，然后cnt自减1；删除开头元素，先判空，然后front向后移动一位，cnt自减1；  
5）插入末尾元素，先判满，然后将新的数字加到当前得到rear位置，rear移动到下一位，为避免越界，依然使用环形数组的经典操作，加1后对长度取余，然后cnt自增1；插入开头元素，先判满，然后将新的数字加入到当前的head位置，head移动到前一位，然后cnt自增1。 代码如下：  

```

	class MyCircularDeque {
	public:
	    /** Initialize your data structure here. Set the size of the deque to be k. */
	    MyCircularDeque(int k) {
	        data.resize(k);
	        size=k;front=k-1;rear=0;cnt=0;        
	    }
	    
	    /** Adds an item at the front of Deque. Return true if the operation is successful. */
	    bool insertFront(int value) {
	        if(isFull()) return false;
	        data[front]=value;
	        front=(front-1+size)%size;
	        cnt++;
	        return true;
	    }
	    
	    /** Adds an item at the rear of Deque. Return true if the operation is successful. */
	    bool insertLast(int value) {
	        if(isFull())  return false;
	        data[rear]=value;
	        rear=(rear+1)%size;
	        cnt++;
	        return true;
	    }
	    
	    /** Deletes an item from the front of Deque. Return true if the operation is successful. */
	    bool deleteFront() {
	        if(isEmpty()) return false;
	        front=(front+1)%size;
	        cnt--;
	        return true;
	    }
	    
	    /** Deletes an item from the rear of Deque. Return true if the operation is successful. */
	    bool deleteLast() {
	        if(isEmpty()) return false;
	        rear=(rear-1+size)%size;
	        cnt--;
	        return true;
	    }
	    
	    /** Get the front item from the deque. */
	    int getFront() {
	        return isEmpty()?-1:data[(front+1)%size];
	    }
	    
	    /** Get the last item from the deque. */
	    int getRear(){
	        return isEmpty()?-1:data[(rear-1+size)%size];
	    }
	    
	    /** Checks whether the circular deque is empty or not. */
	    bool isEmpty() {
	        return cnt==0;
	    }
	    
	    /** Checks whether the circular deque is full or not. */
	    bool isFull() {
	        return cnt==size;
	    }
	private:
	    vector<int> data;
	    int size;
	    int front,rear,cnt;
	};

```


## 5.Sliding Window Maximum（滑动窗口最大值）   
[sliding-window-maximum](https://leetcode.com/problems/sliding-window-maximum/)

- **问题分析：** 该题给定一个数组以及一个窗口大小为k，让我们每次向右滑动一个数字，每次返回窗口内的数字的最大值，而且要求代码的时间复杂度为O(n).  
- **方法一：** 双端队列求解  窗口中只留下有用的值，没用的全丢掉(体现在while语句中)  

1)遍历整个数组，双端队列保存数组的下标，如果此时队列的首元素是i-k的话，表示此时窗口向右移动一步，队首元素要移除；  
2)然后比较队尾元素和将要进来的值，若比即将进来的值小就移除，因为队尾元素不可能被加入res中；  
3)然后把队首元素加入res中。  

```

	class Solution {
	public:
	    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
	        vector<int> res;
	        deque<int> q;//记录nums下标，
	        for(int i=0;i<nums.size();i++){
	            if(!q.empty()&&q.front()==i-k) q.pop_front();
	            //若即将入队的元素大于队列中的原色，则队中元素可删掉
	            while(!q.empty()&&nums[q.back()]<nums[i]) q.pop_back();
	            q.push_back(i);    
	            if(i>=k-1) res.push_back(nums[q.front()]);
	        }
	        return res;
	    }
	};

```

- **方法二：** 使用multiset数据结构，multiset能够实现自动排序，因此时间复杂度为O(nlogK)  

```

	class Solution {
	public:
	    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
	        vector<int> res;
	        if(nums.size()==0) return res;
	        multiset<int> window;
	        for(int i=0;i<nums.size();i++){
	            if(i>=k) window.erase(window.find(nums[i-k]));
	            window.insert(nums[i]);
	            if(i>=k-1)
	                res.push_back(*window.rbegin());//multiset自动升序排列
	        }
	        return res;
	    }
	};
```  
## 6.Climbing Stairs（爬楼梯）  
[climbing-stairs](https://leetcode.com/problems/climbing-stairs/)
- **问题分析：** 每次只能爬一级或两级和斐波那契数列做法一样。但是改题使用递归实现的话会超时。也可以使用两个变量做记录的方法实现，但这里就不写了，下面介绍用动态规划的方法实现。  
1）假设有n层，那么爬到第n层的方法是从第n-1层上来以及从第n-2层上来之和，因此dp[n]=dp[n-1]+dp[n-2]。代码如下：  

```

	class Solution {
	public:
	    int climbStairs(int n) {
	        if(n<=1) return 1;
	        vector<int> dp(n);
	        dp[0]=1; dp[1]=2;
	        for(int i=2;i<n;i++){
	            dp[i]=dp[i-1]+dp[i-2];
	        }
	        return dp.back();
	    }
	};

```

</font>