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


// Yaad rkhne waali baatein:
// JaldiBaazi ke chkkr me ghode nahi lgwane hain...
// Question ko dhyan se aur clearly pdhle bhai...
// Always count on sieve....
int m;
vector<char> mpp = {'n', 'a', 'r', 'e', 'k'};
unordered_set<char> st = {'n', 'a', 'r', 'e', 'k'};
// int recurFill(int i, int ch, vvi& dp, vector<string>& inps) {
//     if(i == inps.size()) return -1 * ch;
//     if(dp[i][ch] != -1) return dp[i][ch];
//     // int mx = 0;

//     // NON-PICK
//     int mx = recurFill(i+1, ch, dp, inps);

//     // PICK
//     int val = 0;
//     int new_ch = ch;
//     for(int j=0; j<m; ++j) {
//         if(inps[i][j] == mpp[new_ch]) {
//             if(mpp[new_ch] == 'k') val += 5;
//             new_ch = (new_ch+1)%5;
//         } else if(st.find(inps[i][j]) != st.end()) {
//             --val;
//         }
//     }
//     mx = max(mx, val + recurFill(i+1, new_ch, dp, inps));

//     return dp[i][ch] = mx;
// }

// int recurFill(int i, int ch, vvi& dp,
//               vector<vector<int>>& gain,
//               vector<vector<int>>& next_ch) {
//     if(i == dp.size()) return -ch;
//     if(dp[i][ch] != -1) return dp[i][ch];

//     int res = recurFill(i+1, ch, dp, gain, next_ch);
//     res = max(res,
//               gain[i][ch] +
//               recurFill(i+1, next_ch[i][ch], dp, gain, next_ch));

//     return dp[i][ch] = res;
// }

void solve(){
    int n; cin >> n >> m;
    vector<string> inps(n);
    fr(i, n) cin >> inps[i];

    vector<vector<int>> gain(n, vector<int>(5));
    vector<vector<int>> next_ch(n, vector<int>(5));

    for(int i = 0; i < n; ++i) {
        for(int ch = 0; ch < 5; ++ch) {
            int val = 0;
            int cur = ch;
            for(char c : inps[i]) {
                if(c == mpp[cur]) {
                    if(mpp[cur] == 'k') val += 5;
                    cur = (cur + 1) % 5;
                } else if(st.count(c)) {
                    --val;
                }
            }
            gain[i][ch] = val;
            next_ch[i][ch] = cur;
        }
    }
    
    int ans = 0;
    vvi dp(n+1, vi(5, 0));

    for(int ch = 0; ch < 5; ch++) {
        dp[n][ch] = -ch;
    }

    for(int i = n - 1; i >= 0; i--) {
        for(int ch = 0; ch < 5; ch++) {
            dp[i][ch] = max(
                dp[i + 1][ch],
                gain[i][ch] + dp[i + 1][next_ch[i][ch]]
            );
        }
    }

    cout << dp[0][0]; nl;

    // fr(i, n) {
    //     ans = max(ans, mxe(dp[i]));
    // }

    // cout << ans << endl;
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

    