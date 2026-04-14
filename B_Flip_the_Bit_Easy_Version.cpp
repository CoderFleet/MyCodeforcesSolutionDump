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

// void solve(){
//     int n, k; cin >> n >> k;
//     vi a(n); cin >> a;
//     vi p(k); cin >> p;
//     p[0]--;
//     int og = a[p[0]];
//     int tot = 0;
//     int tms1 = 0;
//     int tms2 = 0;
//     int i = 0, j = n-1;
//     while(i<p[0] && j>p[0]) { 
//         //lft
//         int sft1=0, sft2= 0;
//         if(a[i] != og && !(tms1&1)) sft1=1;
//         else if(a[i]==og && (tms1&1)) sft1=1;
//         //rgt
//         if(a[j] != og && !(tms2&1)) sft2=1;
//         else if(a[j]==og && (tms2&1)) sft2=1;
//         tot += 1;
//         if(sft1&&sft2) {
//             ++tms1;
//             ++tms2;
//             ++i;
//             --j;
//         } else if(sft1) {
//             ++tms1;
//             ++i;
//             --j;
//         } else if(sft2) {
//             ++tms2;
//             ++i;
//             --j;
//         } else {
//             tot -= 1;
//             ++i;
//             --j;
//         }
//     }
//     dbg(tot);
//     dbg(i);
//     dbg(j);
//     if(tot&1) a[p[0]] ^= 1;
//     if(i<p[0]) {
//         // cout << "YI1" << endl;
//         int l = i;
//         for(int q=l; q<p[0]; ++q) {
//             if(tms1&1) {
//                 if(a[q] == og) {
//                     ++tms1;
//                     ++tot;
//                 }
//             } else {
//                 if(a[q] != og) {
//                     ++tms1;
//                     ++tot;
//                 }
//             }
//         }
//     }
//     if(j>p[0]) {
//         // cout << "yooy" << endl;
//         int r = j;
        
//         for(int q=r; q>=p[0]; --q) {
//             if(tms2&1) {
//                 if(a[q] == og) {
//                     ++tot;
//                     ++tms2;
//                 }
//             } else {
//                 if(a[q] != og) {
//                     ++tot;
//                     ++tms2;
//                 }
//             }
//         }
//     }
//     if(a[p[0]] != og) ++tot;

//     cout << tot << endl;
// }

void solve(){
    int n, k; cin >> n >> k;
    vi a(n); cin >> a;
    vi p(k); cin >> p;
    p[0]--;

    int og = a[p[0]];

    int lft = 0;
    int tms1 = 0;
    for(int i=0; i<p[0];++i){
        if( (a[i]^tms1) !=og){
            lft++;
            tms1 ^= 1;
        }
    }
    int rgt = 0;
    int tms2 = 0;
    for(int i=n-1; i>p[0]; --i){
        if((a[i]^tms2) != og ){
            rgt++;
            tms2 ^= 1;
        }
    }

    int tot = max(lft, rgt);
    if(tot&1) tot++;

    cout << tot << endl;
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

    