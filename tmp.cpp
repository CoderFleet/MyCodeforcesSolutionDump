#include <bits/stdc++.h>
using namespace std;
 
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int t; cin >> t;
    while (t --)
    {
        int n; cin >> n;
        int l = n * 2;
        vector <int> a(l);
        for (int i = 0; i < l; i ++) cin >> a[i];
        sort(a.begin(), a.end());
 
        vector <int> b, c;
        int B = 0, C = 0;
        unordered_map <int, int> hashb, hashc;
        for (int i = 0; i < l; i ++) {
            if (((hashb[a[i]] % 2 == 0) && (hashc[a[i]] % 2 == 0)) || ((hashb[a[i]] % 2 == 1) && (hashc[a[i]] % 2 == 1))) {
                if (B <= C) {
                    hashb[a[i]] ++;
                    b.push_back(a[i]);
                    B ++;
                } else {
                    hashc[a[i]] ++;
                    c.push_back(a[i]);
                    C ++;
                }
            } 
            else {
                if (hashb[a[i]] % 2 == 0 && (B != n)) {
                    hashb[a[i]] ++;
                    b.push_back(a[i]);
                    B ++;
                }
                else {
                    hashc[a[i]] ++;
                    c.push_back(a[i]);
                    C ++;
                }
            }
        }
        int count = 0;
        for (auto it : hashb) {
            if ((it.second % 2) == 1) {
                count ++;
            } 
        }
        for (auto it : hashc) {
            if ((it.second % 2) == 1) {
                count ++;
            }
        }
        cout << count << endl;
    }
    
    return 0;
}