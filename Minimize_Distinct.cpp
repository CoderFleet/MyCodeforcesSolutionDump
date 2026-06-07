/*
                                                                            
                                                    dddddddd                
                         888888888                  d::::::d                
                       88:::::::::88                d::::::d                
                     88:::::::::::::88              d::::::d                
                    8::::::88888::::::8             d:::::d                 
rrrrr   rrrrrrrrr   8:::::8     8:::::8     ddddddddd:::::drrrrr   rrrrrrrrr
r::::rrr:::::::::r  8:::::8     8:::::8   dd::::::::::::::dr::::rrr:::::::::r
r:::::::::::::::::r  8:::::88888:::::8   d::::::::::::::::dr:::::::::::::::::r
rr::::::rrrrr::::::r  8:::::::::::::8   d:::::::ddddd:::::drr::::::rrrrr::::::r
 r:::::r     r:::::r 8:::::88888:::::8  d::::::d    d:::::d r:::::r     r:::::r 
 r:::::r     rrrrrrr8:::::8     8:::::8 d:::::d     d:::::d r:::::r     rrrrrrr
 r:::::r            8:::::8     8:::::8 d:::::d     d:::::d r:::::r            
 r:::::r            8:::::8     8:::::8 d:::::d     d:::::d r:::::r            
 r:::::r            8::::::88888::::::8 d::::::ddddd::::::ddr:::::r            
 r:::::r             88:::::::::::::88   d:::::::::::::::::dr:::::r            
 r:::::r               88:::::::::88      d:::::::::ddd::::dr:::::r            
 rrrrrrr                 888888888         ddddddddd   dddddrrrrrrr            
                                                                            
*/

#include "bits/stdc++.h"
using namespace std;

#define int long long
#define vi vector<int>
#define pb push_back
#define fr(i,n) for(int i=0; i<(n); i++)
#define rep(i,a,n) for(int i=(a); i<=(n); i++)
#define srt(v)  sort(v.begin(),v.end())
#define unq(v)  v.resize(distance(v.begin(), unique(v.begin(), v.end())));
#define all(v) v.begin(),v.end()

template<typename typC> istream &operator>>(istream &cin,vector<typC> &a) { for (auto &x:a) cin>>x; return cin; }
template<typename typC> ostream &operator<<(ostream &cout,const vector<typC> &a) { int n=a.size(); if (!n) return cout; cout<<a[0]; for (int i=1; i<n; i++) cout<<' '<<a[i]; return cout; }

void solve() {
    int n; cin >> n;
    vi a(n); cin >> a;

    vi u = a;
    srt(u);
    unq(u);

    int sz = u.size();
    unordered_map<int, int> ex;
    for(int x : u) ex[x] = 1;

    int mx1 = -1, mx2 = -1;

    // Find the furthest possible points for 1 and 2 collisions
    for(int x : u) {
        // Condition for 1 collision: {x, x+2} exist
        if(ex.count(x + 2)) {
            mx1 = max(mx1, x + 1); // R = x+1 makes x inside, x+2 outside. Valid for L <= x+1
            
            // Condition for 2 collisions: {x, x+1, x+2, x+3} exist
            if(ex.count(x + 1) && ex.count(x + 3)) {
                mx2 = max(mx2, x); // R = x+1 makes {x,x+1} inside, {x+2,x+3} outside. Valid for L <= x
            }
        }
    }

    vi ans(n);
    rep(i, 1, n) {
        if(i <= mx2) ans[i-1] = sz - 2;
        else if(i <= mx1) ans[i-1] = sz - 1;
        else ans[i-1] = sz;
    }

    cout << ans << "\n";
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T; cin >> T;
    while (T--) solve();
    return 0;
}