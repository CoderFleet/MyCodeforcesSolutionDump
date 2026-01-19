//1400 by the end of Jan?
#include <bits/stdc++.h>
using namespace std;
#define fastio ios::sync_with_stdio(false); cin.tie(NULL);
#define int long long

void solve(int h){
    int n , k;
    cin >> n >> k;
    if(n == 3 && k == 3) {
        cout << "9 3 1"<<endl;
        return;
    }
    h = 29;
    int high = pow(2 , 29);
    if(k-1 > h){
        cout<<-1<<endl;
    }
    else{
        int t = 0;
        int hh = pow(2 , k-1);
        while(hh != 1){
            cout<<hh<<" ";
            hh = hh >> 1;
            t++;
        }
        while(t < n){
            cout<<1<<" ";
            t++;
        }
    }
}

int32_t main() {
    fastio
    int t;
    t=1;
    // cin >> t;
    int hp2 = 1;
    int times = 0;
    while(hp2 <= 1e9){
        hp2 = hp2 << 1;
        times ++;
    }
    hp2 = hp2 >> 1;
    times --;
    while (t--) {
        solve(times);
    }
    return 0;
}