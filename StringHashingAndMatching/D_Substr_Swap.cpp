/*
                                                                                              
                                                   dddddddd                                   
                         888888888                 d::::::d                                   
                       88:::::::::88               d::::::d                                   
                     88:::::::::::::88             d::::::d                                   
                    8::::::88888::::::8            d:::::d                                    
rrrrr   rrrrrrrrr   8:::::8     8:::::8    ddddddddd:::::drrrrr   rrrrrrrrr   aaaaaaaaaaaaa   
r::::rrr:::::::::r  8:::::8     8:::::8  dd::::::::::::::dr::::rrr:::::::::r  a::::::::::::a  
r:::::::::::::::::r  8:::::88888:::::8  d::::::::::::::::dr:::::::::::::::::r aaaaaaaaa:::::a 
rr::::::rrrrr::::::r  8:::::::::::::8  d:::::::ddddd:::::drr::::::rrrrr::::::r         a::::a 
 r:::::r     r:::::r 8:::::88888:::::8 d::::::d    d:::::d r:::::r     r:::::r  aaaaaaa:::::a 
 r:::::r     rrrrrrr8:::::8     8:::::8d:::::d     d:::::d r:::::r     rrrrrrraa::::::::::::a 
 r:::::r            8:::::8     8:::::8d:::::d     d:::::d r:::::r           a::::aaaa::::::a 
 r:::::r            8:::::8     8:::::8d:::::d     d:::::d r:::::r          a::::a    a:::::a 
 r:::::r            8::::::88888::::::8d::::::ddddd::::::ddr:::::r          a::::a    a:::::a 
 r:::::r             88:::::::::::::88  d:::::::::::::::::dr:::::r          a:::::aaaa::::::a 
 r:::::r               88:::::::::88     d:::::::::ddd::::dr:::::r           a::::::::::aa:::a
 rrrrrrr                 888888888        ddddddddd   dddddrrrrrrr            aaaaaaaaaa  aaaa
                                                                                              
*/


#include "bits/stdc++.h"
#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update

#define int long long
#define uint unsigned long long
#define vi vector<int>
#define vvi vector<vi >
#define vb vector<bool>
#define vvb vector<vb >
#define pb push_back
#define eb emplace_back
#define fr(i,n) for(int i=0; i<(n); i++)
#define rep(i,a,n) for(int i=(a); i<=(n); i++)
#define nl cout<<"\n"
#define dbg(var) cout<<#var<<"="<<var<<" "
#define all(v) v.begin(),v.end()
#define srt(v)  sort(v.begin(),v.end())         // sort 
#define mxe(v)  *max_element(v.begin(),v.end())     // find max element in vector
#define mne(v)  *min_element(v.begin(),v.end())     // find min element in vector
#define unq(v)  v.resize(distance(v.begin(), unique(v.begin(), v.end())));
// make sure to sort before applying unique // else only consecutive duplicates would be removed 
#define bin(x,y)  bitset<y>(x) 
using namespace std;
using namespace __gnu_pbds;
int MOD=1e9+7;      // Hardcoded, directly change from here for functions!



void modadd(int &a , int b) {a=((a%MOD)+(b%MOD))%MOD;}
void modsub(int &a , int b) {a=((a%MOD)-(b%MOD)+MOD)%MOD;}
void modmul(int &a , int b) {a=((a%MOD)*(b%MOD))%MOD;}
// ================================== take ip/op like vector,pairs directly!==================================
template<typename typC,typename typD> istream &operator>>(istream &cin,pair<typC,typD> &a) { return cin>>a.first>>a.second; }
template<typename typC> istream &operator>>(istream &cin,vector<typC> &a) { for (auto &x:a) cin>>x; return cin; }
template<typename typC,typename typD> ostream &operator<<(ostream &cout,const pair<typC,typD> &a) { return cout<<a.first<<' '<<a.second; }
template<typename typC,typename typD> ostream &operator<<(ostream &cout,const vector<pair<typC,typD>> &a) { for (auto &x:a) cout<<x<<'\n'; return cout; }
template<typename typC> ostream &operator<<(ostream &cout,const vector<typC> &a) { int n=a.size(); if (!n) return cout; cout<<a[0]; for (int i=1; i<n; i++) cout<<' '<<a[i]; return cout; }

template<class T> using oset =tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update> ; // find_by_order, order_of_key
// ===================================END Of the input module ==========================================

class STree {
private:
    int defaultVal = 0;
    vector<int> tree;
    vector<bool> lazy;
    int n;

    void combine(int v) {
        tree[v] = tree[v<<1] + tree[v<<1|1];
    }

    void pushDown(int v, int tl, int tr) {
        if (!lazy[v]) return;
        int tm = (tl + tr) >> 1;

        // flip children
        tree[v<<1] = (tm - tl + 1) - tree[v<<1];
        tree[v<<1|1] = (tr - tm) - tree[v<<1|1];

        lazy[v<<1] = !lazy[v<<1];
        lazy[v<<1|1] = !lazy[v<<1|1];

        lazy[v] = false; // clear parent
    }

    void buildTree(vector<int>& a, int tl, int tr, int v=1) {
        lazy[v] = false;
        if (tl == tr) {
            tree[v] = a[tl];
            return;
        }
        int mid = (tl + tr) >> 1;
        buildTree(a, tl, mid, v<<1);
        buildTree(a, mid+1, tr, v<<1|1);
        combine(v);
    }

    void update(int l, int r, int v, int tl, int tr) {
        if (tl > r || tr < l) return;
        if (l <= tl && tr <= r) {
            tree[v] = (tr - tl + 1) - tree[v]; // flip whole segment
            lazy[v] = !lazy[v]; // mark lazy
            return;
        }
        pushDown(v, tl, tr);
        int tm = (tl + tr) >> 1;
        update(l, r, v<<1, tl, tm);
        update(l, r, v<<1|1, tm+1, tr);
        combine(v);
    }

    int query(int v, int tl, int tr, int l, int r) {
        if (tl > r || tr < l) return 0;
        if (l <= tl && tr <= r) return tree[v];
        pushDown(v, tl, tr);
        int tm = (tl + tr) >> 1;
        return query(v<<1, tl, tm, l, r) + query(v<<1|1, tm+1, tr, l, r);
    }

public:
    STree(vector<int>& vec) {
        n = vec.size();
        tree.assign(n<<2, defaultVal);
        lazy.assign(n<<2, false);
        buildTree(vec, 0, n-1);
    }

    void update(int l, int r) {
        update(l, r, 1, 0, n-1);
    }

    int query(int l, int r) {
        return query(1, 0, n-1, l, r);
    }

    int getVal(int idx) {
        return query(1, 0, n-1, idx, idx);
    }
};


void solve(){
    int n, m; cin >> n >> m;

    string s; cin >> s;
    string t; cin >> t;
    vi sw(n, 0);
    STree st(sw);
    while(m--) {
        int l, r; cin >> l >> r;

        st.update(l-1, r-1);    
    }

    for(int i=0; i<n; ++i) {
        if(st.getVal(i)) cout << t[i];
        else cout << s[i];
    }

    cout << endl;
}

int32_t main()
{
 
 ios_base::sync_with_stdio(false);
 cin.tie(NULL);

    int T = 1;
    // cin >> T;
    while (T--)
    {
        solve();
    }
    return 0;
}