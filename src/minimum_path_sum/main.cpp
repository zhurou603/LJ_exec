#include"minimum_path_sum.h"

//返回二维数组中从左上角到右下角的最小路径和
//[
 // [1,3,1],
 // [1,5,1],
 // [4,2,1]
//]
//从data[0][0]->data[2][2]的最小路径和每次只能向右或者向下,返回1+3+1+1=7
//时间复杂度:O(n),n为二维数组总元素个数
//空间复杂度:O(n),leetcode只需要返回结果，所以就在grid in place执行了
int min_path_sum(vector<vector<int>>& grid) {
    if(0 == grid.size()) return 0;
    //从右下角往左上角更新
    for(int i = grid.size() - 1; i >=0; i--){
      for(int j = grid[i].size() - 1; j >= 0; j--){
        //第一个元素不用处理，但是每次都要判断挺浪费时间的
        if(i == grid.size() - 1 && j == grid[i].size() - 1) continue;
        //如果右或者下的元素超出范围了，那么就赋予INT_MAX
        int right = numeric_limits<int>::max(), 
               down = numeric_limits<int>::max();
        if((j+1) <= (grid[i].size() - 1)){
          right = grid[i][j+1];
        }
        if((i+1) <= (grid.size() - 1)){
          down = grid[i+1][j];
        }
        //更新
        grid[i][j] = grid[i][j] + min(right, down);
      }
    }
    return grid[0][0];
}