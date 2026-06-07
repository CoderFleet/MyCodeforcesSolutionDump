#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void solve() {
    int N, P;
    cin >> N >> P;
    
    vector<long long> A(N);
    vector<long long> pref(N + 1, 0);
    
    for (int i = 0; i < N; ++i) {
        cin >> A[i];
        pref[i + 1] = pref[i] ^ A[i];
    }

    // S contains the freely permutable prefix XORs (P_1 to P_{N-1})
    vector<long long> S;
    for (int i = 1; i < N; ++i) {
        S.push_back(pref[i]);
    }
    
    // Sorting allows us to find the minimum XOR of any two elements in O(N)
    sort(S.begin(), S.end());

    if (P == 1) {
        // Case 1: First element (P_1 ^ 0)
        cout << S[0] << "\n";
    } else if (P == N) {
        // Case 2: Last element (P_N ^ x)
        long long P_N = pref[N];
        long long min_ans = P_N ^ S[0];
        for (long long x : S) {
            min_ans = min(min_ans, P_N ^ x);
        }
        cout << min_ans << "\n";
    } else {
        // Case 3: Middle element (x ^ y for x, y in S)
        long long min_ans = S[0] ^ S[1];
        for (size_t i = 1; i < S.size() - 1; ++i) {
            min_ans = min(min_ans, S[i] ^ S[i + 1]);
        }
        cout << min_ans << "\n";
    }
}

int main() {
    // Optimize standard I/O operations for competitive programming limits
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    cin >> T;
    while (T--) {
        solve();
    }
    
    return 0;
}