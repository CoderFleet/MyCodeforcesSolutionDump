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
#include <ext/pb_ds/tree_policy.hpp>     // Including tree_order_statistics_node_update

#define int long long
#define uint unsigned long long
#define vi vector<int>
#define vvi vector<vi>
#define vb vector<bool>
#define vvb vector<vb>
#define pb push_back
#define eb emplace_back
#define fr(i, n) for (int i = 0; i < (n); i++)
#define rep(i, a, n) for (int i = (a); i <= (n); i++)
#define nl cout << "\n"
#define dbg(var) cout << #var << "=" << var << " "
#define all(v) v.begin(), v.end()
#define srt(v) sort(v.begin(), v.end())         // sort
#define mxe(v) *max_element(v.begin(), v.end()) // find max element in vector
#define mne(v) *min_element(v.begin(), v.end()) // find min element in vector
#define unq(v) v.resize(distance(v.begin(), unique(v.begin(), v.end())));
// make sure to sort before applying unique // else only consecutive duplicates would be removed
#define bin(x, y) bitset<y>(x)
using namespace std;
using namespace __gnu_pbds;
int MOD = 1e9 + 7; // Hardcoded, directly change from here for functions!

void modadd(int &a, int b) { a = ((a % MOD) + (b % MOD)) % MOD; }
void modsub(int &a, int b) { a = ((a % MOD) - (b % MOD) + MOD) % MOD; }
void modmul(int &a, int b) { a = ((a % MOD) * (b % MOD)) % MOD; }
// ================================== take ip/op like vector,pairs directly!==================================
template <typename typC, typename typD>
istream &operator>>(istream &cin, pair<typC, typD> &a) { return cin >> a.first >> a.second; }
template <typename typC>
istream &operator>>(istream &cin, vector<typC> &a)
{
    for (auto &x : a)
        cin >> x;
    return cin;
}
template <typename typC, typename typD>
ostream &operator<<(ostream &cout, const pair<typC, typD> &a) { return cout << a.first << ' ' << a.second; }
template <typename typC, typename typD>
ostream &operator<<(ostream &cout, const vector<pair<typC, typD>> &a)
{
    for (auto &x : a)
        cout << x << '\n';
    return cout;
}
template <typename typC>
ostream &operator<<(ostream &cout, const vector<typC> &a)
{
    int n = a.size();
    if (!n)
        return cout;
    cout << a[0];
    for (int i = 1; i < n; i++)
        cout << ' ' << a[i];
    return cout;
}

template <class T>
using oset = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>; // find_by_order, order_of_key
// ===================================END Of the input module ==========================================
int k;
multiset<int> lst, rst;
int lsum = 0, rsum = 0;

void insert(int val)
{
    int x = *lst.rbegin();
    if (val > x)
    {
        rst.insert(val);
        rsum += val;
        while (rst.size() > (k / 2))
        {
            lst.insert(*rst.begin());
            lsum += *rst.begin();
            rsum -= *rst.begin();
            rst.erase(rst.find(*rst.begin()));
        }
    }
    else
    {
        lst.insert(val);
        lsum += val;
        while (lst.size() > ((k + 1) / 2))
        {
            int sm = *lst.rbegin();
            rst.insert(sm);
            rsum += sm;
            lsum -= sm;
            lst.erase(lst.find(sm));
        }
    }
}

void erase(int val) {
    int x = *lst.rbegin();
    if(val > x) {
        rst.erase(rst.find(val));
        rsum -= val;
    } else {
        lst.erase(lst.find(val));
        lsum -= val;
    }

    if(!lst.size()) {
        int temp = *rst.begin();
        lst.insert(temp);
        lsum += temp;
        rsum -= temp;
        rst.erase(rst.find(temp));
    }
}

int median() {
    if(k&1) return *lst.rbegin();
    return 0;
}

void solve()
{
    int n;
    cin >> n >> k;
    vi a(n);
    cin >> a;

    vi ans;

    lst.insert(a[0]);
    lsum += a[0];

    rep(i, 1, k - 1)
    {
        insert(a[i]);
    }

    ans.pb(rsum - lsum + median());

    for(int i=k; i<n; ++i) {
        if(k==1) {
            insert(a[i]);
            erase(a[i-k]);
        } else {
            erase(a[i-k]);
            insert(a[i]);
        }

        ans.pb(rsum - lsum + median());
    }

    cout << ans << endl;
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
