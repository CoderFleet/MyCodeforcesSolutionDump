#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const ll MAX_SUM = 50000;
const ll FILL_VALUE = 100000000;
const int MAX_SIZE = 10;
const int SEQ_LEN = 20;

ll maxCoverage(const vector<vector<uint8_t>>& dp, int z, ll limit) {
    ll mm = 0;
    for (ll i = 1; i <= limit; ++i) {
        bool covered = false;
        for (int s = 1; s <= z; ++s) {
            if (s < (int)dp.size() && i < (ll)dp[s].size() && dp[s][(size_t)i]) {
                covered = true;
                break;
            }
        }
        if (!covered) break;
        mm = i;
    }
    return mm;
}

vector<vector<uint8_t>> addNumber(const vector<vector<uint8_t>>& dp, ll val) {
    vector<vector<uint8_t>> newDP(MAX_SIZE + 1, vector<uint8_t>((size_t)MAX_SUM + 1, 0));
    for (int sz = 0; sz <= MAX_SIZE; ++sz) {
        for (ll s = 0; s <= MAX_SUM; ++s) {
            if (sz < (int)dp.size() && s < (ll)dp[sz].size() && dp[sz][(size_t)s]) {
                newDP[sz][(size_t)s] = 1;
                if (sz < MAX_SIZE && s + val <= MAX_SUM) {
                    newDP[sz + 1][(size_t)(s + val)] = 1;
                }
            }
        }
    }
    return newDP;
}

long long scoreDP(const vector<vector<uint8_t>>& dp) {
    long long score = 0;
    for (int sz = 1; sz <= MAX_SIZE; ++sz) {
        ll nf = maxCoverage(dp, sz, MAX_SUM);
        score += nf * (1LL << (MAX_SIZE - sz));
    }
    return score;
}

vector<ll> buildSequence(ll n) {
    if (n == SEQ_LEN) {
        vector<ll> seq;
        for (int i = 1; i <= 10; ++i) seq.push_back(i);
        for (int i = 1; i <= 10; ++i) seq.push_back(i);
        return seq;
    }

    vector<vector<uint8_t>> dp(MAX_SIZE + 1, vector<uint8_t>((size_t)MAX_SUM + 1, 0));
    dp[0][0] = 1;

    vector<ll> result;

    for (int it = 0; it < SEQ_LEN; ++it) {
        ll currentCoverage = maxCoverage(dp, MAX_SIZE, MAX_SUM);
        if (currentCoverage >= n) break;

        set<ll> candidates;
        candidates.insert(currentCoverage + 1);
        for (int sz = 1; sz < MAX_SIZE; ++sz) {
            ll f = maxCoverage(dp, sz, MAX_SUM);
            candidates.insert(f + 1);
        }

        ll bestVal = -1;
        long long bestScore = -1;
        vector<vector<uint8_t>> bestDP;

        for (ll val : candidates) {
            if (val < 1 || val > FILL_VALUE) continue;
            auto newDP = addNumber(dp, val);
            long long sc = scoreDP(newDP);
            if (sc > bestScore) {
                bestScore = sc;
                bestVal = val;
                bestDP = move(newDP);
            }
        }

        dp = move(bestDP);
        result.push_back(bestVal);
    }

    while ((int)result.size() < SEQ_LEN) result.push_back(FILL_VALUE);

    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n;
    cin >> n;

    vector<ll> seq = buildSequence(n);

    for (size_t i = 0; i < seq.size(); ++i) {
        if (i > 0) cout << " ";
        cout << seq[i];
    }
    cout << "\n";

    return 0;
}

