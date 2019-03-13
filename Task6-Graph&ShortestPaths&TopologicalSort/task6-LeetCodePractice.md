# <center>  LeetCode练习  </center>

---  
<font size=4>  

## 1.Number of Islands
[岛屿的个数](https://leetcode.com/problems/number-of-islands/)  
**问题分析：**  求岛屿数量的本质是求矩阵中连续区域的个数，要用深度优先搜索，我们需要建立一个visited数组来记录某个位置是否被访问过，对于一个为'1'且未被访问过的位置，我们递归进入其上下左右位置上为'1'的数，将其visited对应值赋为true，继续进入其所有相连的邻位置，这样可以将这个连通区域所有的数找出来，并将其对应的visited中的值赋为true，以此类推直至遍历完整个原数组即可可到最终结果。  
判断一个岛屿的要素是判断是否该陆地的上下左右是否被水包围，即岛屿的数量=连通陆地的数量。  
```

	class Solution {
	public:
	    int numIslands(vector<vector<char>>& grid) {
	        if(grid.empty()||grid[0].empty()) return 0;
	        int m=grid.size(),n=grid[0].size(),res=0;  
	        vector<vector<bool> > visited(m, vector<bool>(n,false));
	        for(int i=0;i<m;i++){
	            for(int j=0;j<n;j++){
	                if(grid[i][j]=='1'&&!visited[i][j]){
	                    numIslandsDFS(grid,visited,i,j);
	                    res++;
	                }
	            }
	        }
			return res;
	    }
	private:
	    void numIslandsDFS(vector<vector<char>>& grid,vector<vector<bool> > &visited,int x,int y){
	        if(x<0||x>=grid.size()) return;
	        if(y<0||y>=grid[0].size()) return ;
	        if(grid[x][y]!='1'||visited[x][y]) return;
	        visited[x][y]=true;
	        numIslandsDFS(grid,visited,x-1,y);
	        numIslandsDFS(grid,visited,x+1,y);
	        numIslandsDFS(grid,visited,x,y-1);
	        numIslandsDFS(grid,visited,x,y+1);
	    }    
	};
```


## 2.Valid Sudoku
[有效的数独](https://leetcode.com/problems/valid-sudoku/)  
**问题分析** 这道题让我们验证一个方阵是否为数独矩阵。判断标准是看各行各列以及每个小的3×3的小方阵里是否有重复数字，如果都无重复，则当前矩阵是数独矩阵，但不代表该数独矩阵有解，只是单纯的判断当前未填完的矩阵是否是数独矩阵。  
**思路：** 根据数独矩阵的定义，在遍历每个数字时，就看看包含当前位置的行、列以及3×3的小方阵是否已出现某个数字。  

```

	class Solution {
	public:
	    bool isValidSudoku(vector<vector<char>>& board) {
	        if(board.empty()||board[0].empty()) return false;
	        int m=board.size(),n=board[0].size();
	        vector<vector<bool>> rowFlag(m,vector<bool>(n,false));
	        vector<vector<bool>> colFlag(m,vector<bool>(n,false));
	        vector<vector<bool>> cellFlag(m,vector<bool>(n,false));
	        for(int i=0;i<m;i++){
	            for(int j=0;j<n;j++){
	                if(board[i][j]>='1'&&board[i][j]<='9'){
	                    int c=board[i][j]-'1';
	                    if(rowFlag[i][c]||colFlag[c][j]||cellFlag[3*(i/3)+j/3][c])
	                        return false;
	                    rowFlag[i][c]=true;
	                    colFlag[c][j]=true;
	                    cellFlag[3*(i/3)+j/3][c]=true;
	                }
	            }
	        }
	        return true;
	    }
	};
```

</front>