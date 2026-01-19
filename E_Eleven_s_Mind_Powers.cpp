#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long long n, k, numOps;
    if (!(cin >> n >> k >> numOps)) return 0;

    vector<long long> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    // Step 1: Sort levels to use sliding window
    sort(a.begin(), a.end());

    int max_objects = 0;
    int left = 0;

    // Step 2: Sliding Window
    for (int right = 0; right < n; right++) {
        /* Condition 1: Difference between max and min in window 
           can't exceed 2*k (because each can move by k).
           Condition 2: Total elements to change can't exceed numOperations.
           The number of elements to change in a window of size (right - left + 1)
           is (right - left) because at least one must remain unchanged.
        */
        while (a[right] - a[left] > 2 * k || (right - left) > numOps) {
            left++;
        }

        // Update the maximum window size found
        max_objects = max(max_objects, right - left + 1);
    }

    cout << max_objects << endl;

    return 0;
}