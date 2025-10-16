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

long long ipow(long long base, int exp) {
    long long res = 1;
    while (exp--) res *= base;
    return res;
}

long long findv(int p) {
    if (p == 0) return 3;
    return ipow(3, p+1) + p * ipow(3, p-1);
}

// void precomp(vi& cst) {
//     cst.pb(1);
//     int p = 1;
//     while(cst.back() < 1e9) {
//         cst.pb(findv(p));
//         ++p;
//     }
// }

// int recurFind(int n, int k, vi& cst) {
//     if(n <= 0) return 0;
//     if(k == 0) return 1e12;

//     int p = 0;
//     int mx = 1;
//     while(n >= mx) {
//         ++p;
//         mx = mx*3;
//     }
//     --p;
// }

auto minans(int n, map<int, int>& mpp){
    int mx = 1;
    int p = 0;
    while(n >= mx) {
        ++p;
        mx = mx*3;
    }
    --p;
    mx = mx/3;
    int dl = 0;
    int ans = 0;
    while(n) {
        if(n >= mx) {
            dl += n/mx;
            ans += (n/mx) * findv(p);
            mpp[p] = n/mx;
            n = n%mx;
        } else {
            mpp[p] = 0;
        }
        --p;
        mx = mx/3;
    }

    return make_pair(ans, dl);
}

void solve(){
    int n, k; cin >> n >> k;
    map<int, int> mpp;
    auto acc = minans(n, mpp);
    int bsTime = acc.second;
    int bsCost = acc.first;
    if(bsTime > k) {
        cout << -1 << endl;
        return;
    }
    else if(bsTime == k) {
        cout << bsCost << endl;
        return;
    }

    int times = (k - bsTime)/2;

    for (auto it = mpp.rbegin(); it != mpp.rend(); ++it) {
        int p = it->first;
        int tms = it->second;
        if(p==0) continue;
        int act = min(tms, times);
        times -= act;
        mpp[p-1] += 3*act;
        bsCost -= (ipow(3, p-1) * act);
    }

    cout << bsCost << endl;
}

int32_t main()
{
 
 ios_base::sync_with_stdio(false);
 cin.tie(NULL);

    int T = 1;
    cin >> T;
    while (T--)
    {
        solve();
    }
    return 0;
}

    