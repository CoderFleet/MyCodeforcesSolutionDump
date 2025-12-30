#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct Friend {
    int x;
    long long c; // Extra cost (z - y)
    int id;
};

void solve() {
    int n, m;
    long long k;
    cin >> n >> m >> k;

    vector<int> a(m);
    for (int i = 0; i < m; ++i) {
        cin >> a[i];
    }

    vector<Friend> friends(n);
    long long sum_y = 0;
    for (int i = 0; i < n; ++i) {
        int x;
        long long y, z;
        cin >> x >> y >> z;
        friends[i] = {x, z - y, i};
        sum_y += y;
    }

    // Calculate remaining budget for "upgrades"
    long long budget = k - sum_y;

    // If base cost exceeds k (though problem constraints say sum_y <= k)
    if (budget < 0) {
        cout << 0 << endl;
        return;
    }

    // Sort boxes ascending
    sort(a.begin(), a.end());

    // Sort friends by requirement x ascending
    sort(friends.begin(), friends.end(), [](const Friend& f1, const Friend& f2) {
        return f1.x < f2.x;
    });

    // Max-Heap to store costs of eligible friends
    // We store pair {cost, id} to track who gets boxed
    priority_queue<pair<long long, int>> pq;
    
    vector<bool> is_boxed(n, false);
    int friend_idx = 0;
    int boxed_count = 0;

    // Greedy matching: Iterate boxes small to large
    for (int box_val : a) {
        // Add all friends who can fit in this box (and haven't been added yet)
        while (friend_idx < n && friends[friend_idx].x <= box_val) {
            pq.push({friends[friend_idx].c, friends[friend_idx].id});
            friend_idx++;
        }

        // If we have eligible friends, use the box for the one with the highest cost
        if (!pq.empty()) {
            pair<long long, int> best = pq.top();
            pq.pop();
            is_boxed[best.second] = true; // Use original ID
            boxed_count++;
        }
    }

    // Collect costs of friends who did NOT get a box
    vector<long long> remaining_costs;
    // Note: iterating the original sorted `friends` vector is fine, 
    // but we need to check `is_boxed` using the friend's original ID.
    for (int i = 0; i < n; ++i) {
        if (!is_boxed[friends[i].id]) {
            remaining_costs.push_back(friends[i].c);
        }
    }

    // Sort remaining costs to buy the cheapest ones first
    sort(remaining_costs.begin(), remaining_costs.end());

    int happy_count = boxed_count;
    for (long long cost : remaining_costs) {
        if (budget >= cost) {
            budget -= cost;
            happy_count++;
        } else {
            break;
        }
    }

    cout << happy_count << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}