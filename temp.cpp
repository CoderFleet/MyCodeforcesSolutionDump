#include <bits/stdc++.h>
using namespace std;

const int N = 1e6;  // Maximum limit
vector<int> d[N];

void divisorSieve() {
    for (int i = 1; i * i < N; i++) {
        for (int j = i * i; j < N; j += i) {
            d[j].push_back(i);
            if (j / i != i) d[j].push_back(j / i);  // Avoid duplicate for perfect squares
        }
    }
}

int main() {
    divisorSieve();
    int num = 36;
    cout << "Divisors of " << num << ": ";
    for (int div : d[num]) cout << div << " ";
    cout << endl;
    return 0;
}