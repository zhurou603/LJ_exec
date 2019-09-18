#include<vector>

using namespace std;

vector<vector<int>> combination_sum(int k, int n);

void back_tracking(int k, int n, int num, vector<int> part, 
                                          vector<vector<int>>& result);