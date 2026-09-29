#include <bits/stdc++.h>
using namespace std;

#define all(v) begin(v), end(v)
#define rall(v) rbegin(v), rend(v)
#define sz(v) (int)v.size()
#define pb push_back
#define eb emplace_back
#define compact(v) v.erase(unique(all(v)), end(v))

template<class T> bool minimize(T& a, const T& b){ return a > b ? a = b, 1 : 0; }
template<class T> bool maximize(T& a, const T& b){ return a < b ? a = b, 1 : 0; }

using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

#ifdef LOCAL 
    #include "debug.hpp"
#else
    #define dbg(...) (void(0))
#endif //LOCAL

const int MX = 1005;
int n, m;
int a[MX];
int f[MX][2], trace[MX][2];
int ans[MX][MX];

int w(bool z) {
    return (m + z) / 2;
}

void testcase(){
    cin >> n >> m;
    for(int i = 1; i <= n; ++i) cin >> a[i];

    f[0][0] = f[0][1] = 1;
    for(int i = 1; i <= n; ++i) {
        if(a[i] <= w(0) && f[i - 1][1]) {
            f[i][0] = 1;
            trace[i][0] = 1;
        }
        if(a[i] <= w(1) && f[i - 1][0]) {
            f[i][1] = 1;
            trace[i][1] = 0;
        }
        if(a[i] + a[i - 1] <= w(0) && f[i - 1][0]) {
            f[i][0] = 1;
            trace[i][0] = 0;
        }
        if(a[i] + a[i - 1] <= w(1) && f[i - 1][1]) {
            f[i][1] = 1;
            trace[i][1] = 1;
        }
        dbg(f[i][0], f[i][1]);
    }
    if(f[n][0] == 0 && f[n][1] == 0) {
        cout << -1;
        return;
    }
    bool t = f[n][0] ? 0 : f[n][1];
    for(int i = n, q = 0; i >= 1; --i, q = !q) {
        if(q) {
            int start = m;
            if(start % 2 != t) start--;
            for(int j = start; a[i] > 0; a[i]--, j -= 2) ans[i][j] = 1;
        }
        else {
            int start = 1;
            if(start % 2 != t) start++;
            for(int j = start; a[i] > 0; a[i]--, j += 2) ans[i][j] = 1;
        }
        t = trace[i][t];
    }

    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= m; ++j) {
            cout << ans[i][j];
        }
        cout << '\n';
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int tests = 1;
    // cin >> tests;
    while(tests--){
        testcase();
    }
    return 0;
}