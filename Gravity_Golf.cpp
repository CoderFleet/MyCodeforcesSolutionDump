#include <iostream>
#include <vector>
#include <string>

using namespace std;

void solve() {
    int n;
    cin >> n;
    string s;
    cin >> s;

    int small_limit = n / 2;
    int k = 2 * small_limit + 4;

    // Grid initialized to '0'
    vector<string> grid(k, string(n, '0'));

    // 1. Process Small Powers (1-indexed power P corresponds to s[P-1])
    for (int p = 1; p <= small_limit; ++p) {
        if (s[p - 1] == '1') {
            int block_row = 2 * p; // 0-indexed row matching 2P + 1
            int curr = 1 + p;      // 1-based column
            while (curr < n) {
                grid[block_row][curr - 1] = '1';
                curr += p;
            }
        }
    }

    // 2. Process Large Powers
    int large_block_row = 2 * small_limit + 2; // 0-indexed row matching shared blocking row
    for (int p = small_limit + 1; p < n; ++p) {
        if (s[p - 1] == '1') {
            int curr = 1 + p;
            if (curr < n) {
                grid[large_block_row][curr - 1] = '1';
            }
        }
    }

    // 3. Place the trap on the bottom row
    grid[k - 1][n - 2] = '1';

    // Print output
    cout << k << "\n";
    for (int i = 0; i < k; ++i) {
        cout << grid[i] << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    return 0;
}