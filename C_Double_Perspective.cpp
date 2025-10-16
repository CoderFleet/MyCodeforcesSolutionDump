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
#define int long long
#define uint unsigned long long
#define vi vector<int>
#define vvi vector<vi >
#define vb vector<bool>
#define vvb vector<vb >
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
// ===================================END Of the input module ==========================================

// Got this from my template
class DSU {
private:
    vector<int> parent;
public:
    DSU(int n) {
        parent = vector<int>(n+1);
        iota(begin(parent), end(parent), 0);
    }
    
    int getParent(int x) {
        if (parent[x] == x) return x;
        return parent[x] = getParent(parent[x]);
    }

    bool join(int x, int y) {
        x = getParent(x);
        y = getParent(y);
        if (x == y) return false;
        parent[y] = x;
        return true;
    }
};

void solve(){
    int n; cin >> n;
    vector<pair<int, int>> ab(n);

    for(int i=0; i<n; ++i) {
        cin >> ab[i].first >> ab[i].second;
    }

    vector<vector<int>> edges(n);
    int mx = 0;
    for(int i=0; i<n; ++i) {
        edges[i] = {ab[i].first, ab[i].second, ab[i].second-ab[i].first, i+1};
        mx = max(mx, max(ab[i].first, ab[i].second));
    }

    sort(all(edges), [&](const vector<int>& e1, const vector<int>& e2) {
        return e1[2] > e2[2];
    });
    DSU ds(mx);

    vector<int> ans;

    for(auto& edge: edges) {
        if(ds.join(edge[0], edge[1])) {
            ans.push_back(edge[3]);
        }
    }

    cout << ans.size() << endl;
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