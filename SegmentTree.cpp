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

/* Segment Tree Lazy Propogation Generic Code */
class Node{
public:
    int v = 0;
    Node(){ v = 0; } // Identity Element
    Node(int val){ v = val; }
    
    void merge(const Node& l, const Node& r){
        v = l.v + r.v;
    }
};

class Update{
public:
    int v = 0;
    Update(){ v = 0; } // Identity Transformation
    Update(int val){ v = val; }
    
    void combine(const Update& otherUpdate, const int& tl, const int& tr){
        v += otherUpdate.v; 
    }
    
    void apply(Node& node, const int& tl, const int& tr) const{
        node.v += (tr - tl + 1) * v;
    }	
};

template <typename node, typename update>
class SegTree{
public:
    int len;
    vector<node> t;
    vector<update> unpropUpd;
    vector<bool> isLazy;
    node identityElement;
    update identityTransformation;
    
    SegTree(int l){
        len = l;
        t.resize(4 * len);
        isLazy.assign(4 * len, false);
        unpropUpd.resize(4 * len);
        identityElement = node();
        identityTransformation = update();
    }
    
    void apply(const int& v,const int& tl,const int& tr,const update& upd){
        if(tl != tr){
            isLazy[v] = true;
            unpropUpd[v].combine(upd, tl, tm);
        }
        upd.apply(t[v], tl, tr);
    }
    
    void pushDown(const int& v,const int& tl,const int& tr){
        if(!isLazy[v]) return;
        isLazy[v] = false;
        int tm = (tl + tr)/2;
        apply(2*v, tl, tm, unpropUpd[v]);
        apply(2*v+1, tm+1, tr, unpropUpd[v]);
        unpropUpd[v] = identityTransformation;
    }
    
    template<typename T>
    void build(const T& a,const int& v,const int& tl,const int& tr){
        if(tl == tr){
            t[v] = node(a[tl]);
            return;
        }
        int tm = (tl + tr)/2;
        build(a, 2*v, tl, tm);
        build(a, 2*v+1, tm+1, tr);
        t[v].merge(t[2*v], t[2*v+1]);
    }
    
    node query(const int& v,const int& tl,const int& tr,const int& l,const int& r){
        if(tl > r || tr < l) return identityElement;
        if(l <= tl && tr <= r) return t[v];
        pushDown(v, tl, tr);
        int tm = (tl + tr)/2;
        node leftAns = query(2*v, tl, tm, l, r);
        node rightAns = query(2*v+1, tm+1, tr, l, r);
        node ans;
        ans.merge(leftAns, rightAns);
        return ans;
    }
    
    void rangeUpdate(const int& v,const int& tl,const int& tr,const int& l,const int& r, const update& upd){
        if(l <= tl && tr <= r){
            apply(v, tl, tr, upd);
            return;
        }
        if(tl > r || tr < l) return;
        pushDown(v, tl, tr);
        int tm = (tl + tr)/2;
        rangeUpdate(2*v, tl, tm, l, r, upd);
        rangeUpdate(2*v+1, tm+1, tr, l, r, upd);
        t[v].merge(t[2*v], t[2*v+1]);
    }
    
    template<typename T> void build(const T& a){ build(a, 1, 0, len-1); }
    node query(const int& l,const int& r){ return query(1, 0, len-1, l, r); }
    void rangeUpdate(const int& l,const int& r, const update& upd){ rangeUpdate(1, 0, len-1, l, r, upd); }
};

void solve(){
    int n; cin >> n;
    vi a(n); cin >> a;
     
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

    