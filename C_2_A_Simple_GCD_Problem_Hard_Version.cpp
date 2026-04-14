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

void solve(){
    int n; cin >> n;
    vi a(n), b(n); cin >>a >> b;
    auto lcm = [&](int a, int b) {
        return (a*b) / (__gcd(a, b));
    };

    if(n==1) {
        cout << 1 << endl;
    }
    vector<vector<int>> dp(n);
    vector<vector<int>> mul(n);
    vi gcdi(n-1);
    for(int i=0; i<n-1; ++i) gcdi[i] = __gcd(a[i], a[i+1]);
    vi lcmi(n, gcdi[0]);
    for(int i=1; i<n-1; ++i) {
        lcmi[i] = lcm(gcdi[i-1], gcdi[i]);
    }
    lcmi[n-1] = gcdi[n-2];
    // dp[0].pb(a[0] / (lcm(__gcd(a[0], a[1]), __gcd(a[1], a[]))))
    // mul[0].pb(a[0] / lcmi[0]);
    // for(int i=1; i<=b[0]/lcmi[0]; ++i) {
    //     if(k!=a[0]/lcmi[0]) {
    //         dp[0].pb(i);
    //         if(dp[0].size() == 10) break;
    //     }
    // }

    for(int i=0; i<n; ++i) {
        mul[i].pb(a[i] / lcmi[i]);

        for(int j=1; j<=(b[i]/lcmi[i]); ++j) {
            int flg = 1;
            if(i>0) {
                int mulp = lcmi[i-1] / gcdi[i-1];
                if(__gcd(mulp, j) != 1) flg = 0;
            }
            // flg && i>    
            if(flg && i<n-1) {
                int muln = lcmi[i+1] / gcdi[i];
                if(__gcd(muln, j) != 1) flg = 0;
            }

            if(flg) {
                if(j == a[i] / lcmi[i]) continue;
                mul[i].pb(j);
                if(mul[i].size() > 10) break;
            } 
        }
    }

    for(int i=0; i<n; ++i) {
        dp[i].resize(mul[i].size(), -1);
    } 
    for(int i=0; i<dp[0].size(); ++i) dp[0][1] = 1;
    dp[0][0] = 0;

    for(int i=1; i<n; ++i ){
        for(int j=0; j<mul[i].size(); ++j) {
            int currml = mul[i][j];
            int bst = -1;
            for(int k=0; k<mul[i-1].size(); ++k) {
                if(dp[i-1][k] != -1) {
                    int prevml = mul[i-1][k];
                    if(__gcd(currml, prevml) == 1) bst = max(bst, dp[i-1][k]);  
                }
            }

            if(bst != -1) {
                dp[i][j] = bst + (currml != (a[i] / lcmi[i]));
            }
        }
    }

    int ans = 0;
    for(int i=0; i<dp[n-1].size(); ++i) {
        ans = max(ans, dp[n-1][i]);
    }
    cout << ans << endl;
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

    