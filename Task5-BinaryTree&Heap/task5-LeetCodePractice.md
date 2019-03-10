# <center>  LeetCode练习  </center>

---  
<font size=4>  

## 1.Invert Binary Tree
[翻转二叉树](https://leetcode.com/problems/invert-binary-tree/)  
**问题分析：** 树的基本操作之一，可以使用递归和非递归两种解法。  
**1.1 递归求解**   先遍历这棵树的每个节点，如果遍历到的节点有子节点，就交换它的左右两个子节点，当交换完所有非子节点的左右子节点之后，就得到了树的镜像。  
```

	class Solution {
	public:
	    TreeNode* invertTree(TreeNode* root) {
	        if(!root) return NULL;
	        TreeNode *t=root->left;
	        root->left=invertTree(root->right);
	        root->right=invertTree(t);
	        return root;
	    }
	};
```

**1.2 非递归求解**  解法跟二叉树层次遍历一样，需要借助queue，先把根节点入队，然后从队中取出来，交换其左右节点，如果存在则分别将左右节点入队，以此类推直到队列中没有节点为止。     
```

	class Solution {
	public:
	    TreeNode* invertTree(TreeNode* root) {
	        if(!root) return NULL;
	        queue<TreeNode*> q;
	        q.push(root);
	        while(!q.empty()){
	            TreeNode *node=q.front();q.pop();
	            TreeNode *t=node->left;
	            node->left=node->right;
	            node->right=t;
	            if(node->left) q.push(node->left);
	            if(node->right) q.push(node->right);
	        }
	        return root;
	    }
	};
```

## 2.Maximum Depth of Binary Tree
[二叉树的最大深度](https://leetcode.com/problems/maximum-depth-of-binary-tree/)  
**2.1 深度优先搜索DFS** 递归的完美应用    
```

	class Solution {
	public:
	    int maxDepth(TreeNode* root) {
	        if(!root) return 0;
	        return 1+max(maxDepth(root->left),maxDepth(root->right));
	    }
	};
```

**2.2 层次遍历二叉树** ，然后计算总层数，即为二叉树的最大深度。  
```

	class Solution {
	public:
	    int maxDepth(TreeNode* root) {
	        if(!root) return 0;
	        int res=0;
	        queue<TreeNode*> q{{root}};
	        while(!q.empty()){
	            res++;
	            for(int i=q.size();i>0;i--){
	                TreeNode *t=q.front();q.pop();
	                if(t->left) q.push(t->left);
	                if(t->right) q.push(t->right);
	            }
	        }
	        return res;
	    }
	};
```
 
## 3.Validate Binary Search Tree
[验证二叉查找树](https://leetcode.com/problems/validate-binary-search-tree/)  
**问题分析：** 利用二叉搜索树本身的性质，即左<根<右，也可以通过中序遍历结果为有序数列来做。  
**3.1 根据左<根<右的性质** 初始化时带入系统最大值和最小值，在递归过程中替换成它们自己的节点值,这里用long代替int是为了包含int的边界值。  
```

	class Solution {
	public:
	    bool isValidBST(TreeNode* root) {
	        return isValidBSF(root,LONG_MIN,LONG_MAX);
	    }
	private:
	    bool isValidBSF(TreeNode* root,long min,long max){
	        if(!root) return true;
	        if(root->val<=min||root->val>=max) return false;
	        return isValidBSF(root->left,min,root->val)&&isValidBSF(root->right,root->val,max);
	    }    
	};
```

**3.2 中序遍历** 先通过中序遍历将所有节点值保存到一个数组中，然后再判断这个数组是不是有序的。  
```

	class Solution {
	public:
	    bool isValidBST(TreeNode* root) {
	        if(root==NULL) return true;
	        vector<int> res;
	        inorder(root,res);
	        for(int i=0;i<res.size()-1;i++){
	            if(res[i]>=res[i+1]) return false;
	        }
	        return true;
	    }
	private:
	    void inorder(TreeNode* root,vector<int> &res){
	        if(root){
	            inorder(root->left,res);
	            res.push_back(root->val);
	            inorder(root->right,res);
	        }
	    }    
	};
```
## 4.Path Sum
[路径总和](https://leetcode.com/problems/path-sum/)  
**4.1 深度优先搜索DFS**  ，使用DFS思想来遍历每一条完整的路径，即利用递归不停地找子节点的左右子节点，而调用递归函数的参数只有当前节点和sum值。  
>1.首先 ，如果输入的是一个空节点，则直接返false，如果输入的只有一个根节点，则比较当前根节点的值和参数sum值是否相同，若相同返回true否则返回flase；这个条件也是递归的终止条件。    
>2.由于函数的返回值是true/false，我们可以同时两个方向一起递归，中间用||连接，只要有一个是true整个结果就是true。  、
>3.递归左右节点时，这时的sum值应该是原sum值减去当前节点的值。  
```

	class Solution {
	public:
	    bool hasPathSum(TreeNode* root, int sum) {
	        if(!root) return false;
	        if(!root->left&&!root->right&&root->val==sum) return true;
	        return hasPathSum(root->left,sum-root->val)||hasPathSum(root->right,sum-root->val);
	    }
	};
```

**4.2 使用先序遍历的迭代写法**  ，先遍历二叉树，做右子节点都需要加上其父节点值，这样遍历到叶节点时，如果和sum相等了，那就说明一定有一条从root过来的路径。
```

	class Solution {
	public:
	    bool hasPathSum(TreeNode* root, int sum) {
	        if(!root) return false;
	        stack<TreeNode*> st{{root}};
	        while(!st.empty()){
	            TreeNode *t=st.top();st.pop();
	            if(!t->left&&!t->right)
	                if(t->val==sum) return true;
	            if(t->right){
	                t->right->val += t->val;
	                st.push(t->right);
	            }
	            if(t->left){
	                t->left->val += t->val;
	                st.push(t->left);
	            }
	        }
	        return false;
	    }
	};
```


</front>