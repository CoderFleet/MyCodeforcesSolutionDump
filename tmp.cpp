#include <bits/stdc++.h>
using namespace std;

const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};

class Solution {
  public:
    void f(int x, int y, vector<vector<int>>& vis, vector<vector<int>>& grid) {
        int n = vis.size();
        int m = vis[0].size();
        vis[x][y] = 1;
        auto isVal = [&](int a, int b) {
            return (a>=0 && b>=0 && a<n && b<m);
        };
        for(int i=0; i<4; ++i) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            
            if(isVal(nx, ny) && grid[nx][ny] && !vis[nx][ny]) {
                f(nx, ny, vis, grid);
            }
        }
    }
    int cntOnes(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        
        vector<vector<int>> vis(n, vector<int>(m, 0));
        for(int i=0; i<n; ++i) {
            if(grid[i][0] && !vis[i][0]) f(i, 0, vis, grid);
        }
        for(int j=0; j<m; ++j) {
            if(grid[0][j] && !vis[0][j]) f(0, j, vis, grid);
        }
        for(int i=0; i<n; ++i) {
            if(grid[i][m-1] && !vis[i][m-1]) f(i, m-1, vis, grid);
        }
        for(int j=0; j<m; ++j) {
            if(grid[n-1][j] && !vis[n-1][j]) f(n-1, j, vis, grid);
        }
        int cnt = 0;
        for(int i=0; i<n; ++i) {
            for(int j=0; j<m; ++j) {
                if(grid[i][j] && !vis[i][j]) ++cnt;
            }
        }
        
        return cnt;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if(!(cin >> n >> m)) return 0;
    vector<vector<int>> grid(n, vector<int>(m));
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            cin >> grid[i][j];
        }
    }

    Solution sol;
    cout << sol.cntOnes(grid) << '\n';

    return 0;
}