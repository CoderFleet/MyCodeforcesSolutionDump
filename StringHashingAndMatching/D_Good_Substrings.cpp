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


using namespace chrono;
typedef unsigned long long H; 
static H C;
static H L;
struct HashInterval {
    vector<H> ha, pw;
    HashInterval(string& str) : ha(str.size()+1), pw(ha) {
        pw[0] = 1;
        for(int i=0;i<str.size();i++)   
            ha[i+1] = (ha[i] * L + str[i]-'a'+1)%C,
            pw[i+1] = (pw[i] * L)%C;
    }
    H hashInterval(int a, int b){       // 
        return (ha[b] - ha[a] * pw[b - a]%C+C)%C;
    }
}; 
template<typename T>
bool isPrime(T N) {
    if(N<2)return false;
    if(N<4)return true;
    if(N%2==0 or N%3==0)return false;
    T curr=5;
    while(curr*curr<=N){
    if(N%curr==0)return false;
        curr+=2;
        if(N%curr==0)return false;
        curr+=4;
    }
    return true;
}
void precompH(){
    mt19937 rng(duration_cast<nanoseconds>(high_resolution_clock::now().time_since_epoch()).count());
    uniform_int_distribution<unsigned long long> distribution(1000000000,4000000000);
    uniform_int_distribution<unsigned long long> distribution2(31,200);
    C = distribution(rng);
    L = distribution2(rng);
    while(!isPrime(C))C++;
}

using ull = unsigned long long;

struct DoubleHash {
    const ull M1 = 1000000007ULL;
    const ull M2 = 1000000009ULL;
    ull B1, B2;
    vector<ull> ha1, pw1, ha2, pw2;
    DoubleHash(const string &s, ull base1=911382323ULL, ull base2=972663749ULL) {
        int n = s.size();
        B1 = base1 % M1; if (B1 == 0) B1 = 9113823;
        B2 = base2 % M2; if (B2 == 0) B2 = 9726637;
        ha1.assign(n+1, 0); pw1.assign(n+1, 0);
        ha2.assign(n+1, 0); pw2.assign(n+1, 0);
        pw1[0] = 1; pw2[0] = 1;
        for (int i = 0; i < n; ++i) {
            ull v = (ull)(s[i]-'a'+1);
            ha1[i+1] = ( (ha1[i] * B1) + v ) % M1;
            pw1[i+1] = (pw1[i] * B1) % M1;
            ha2[i+1] = ( (ha2[i] * B2) + v ) % M2;
            pw2[i+1] = (pw2[i] * B2) % M2;
        }
    }
    ull get_combined(int a, int b) {
        ull x1 = (ha1[b] + M1 - (ha1[a] * pw1[b-a]) % M1) % M1;
        ull x2 = (ha2[b] + M2 - (ha2[a] * pw2[b-a]) % M2) % M2;
        return (x1 << 32) ^ x2;
    }
};

void solve(){
    string s; cin >> s;
    int n = s.length();
    string dig; cin >> dig;
    int k; cin >> k;
    // precompH();
    DoubleHash alpha(s);
    unordered_set<H> st;
    int ans = 0;
    int i = 0, j = 0;
    int cnt = 0;
    while(j<n) {
        // dbg(i); dbg(j);
        // cout << endl;
        if(dig[s[j] - 'a'] == '0') cnt++;
        while(cnt > k && i <= j) {
            // cout << "cld" << endl;
            if(dig[s[i] - 'a'] == '0'){
                cnt--;
                // if(mpp[s[i]] <= 0) mpp.erase(s[i]);
            }
            i++;
        }
        if(cnt <= k) {
            for(int l=i; l<=j; ++l) {
                H val = alpha.get_combined(l, j+1);
                if(st.find(val) == st.end()) {
                    ++ans;
                    st.insert(val);
                }
            }
        }
        ++j;
    }
    cout << ans << endl;;
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