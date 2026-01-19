#include <bits/stdc++.h>
using namespace std;
#define fastio ios::sync_with_stdio(false); cin.tie(NULL);
#define int long long
void solve(){
    int n , k;
    cin >> n >> k;
    // vector<int> a(n);
    // for(int i = 0 ; i < n ; i++){
    // cin >> a[i];
    // }
    string s;
    cin >> s;
    vector<int> pre(n+1 , 0);
    for(int i = 0 ; i < n ; i++){
        pre[i+1] = pre[i] + (s[i] == '1' ? 1 : 0);
    }
    int ans = 0;
    // for(int i = 0 ; i < k ; i++){
    // if((pre[k+i-1] - pre[i])%2 == 1){
    // ans ++;
    // }
    // }
    int i = 0;
    int j = n-k;
    while(j < n){
        if((pre[j+1] - pre[i])%2 == 1){
            ans ++;
        }
        j++;
        i++;
    }
    cout<<ans<<endl;
}
int32_t main() {
    fastio
    int t;
    t=1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}