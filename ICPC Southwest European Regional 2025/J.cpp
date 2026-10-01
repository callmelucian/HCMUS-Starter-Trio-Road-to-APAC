#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
    #include "debug.hpp"
#else
    #define dbg(...) ((void)0)
#endif // LOCAL 

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

#define int long long

const int MX = 4010;
int n, m;
int a[MX], b[MX], pf[MX], f[MX], g[MX];
bitset<MX> ok[MX];

void testcase(){
    cin >> n >> m;
    for(int i = 1; i <= n; ++i) cin >> a[i];
    for(int i = 1; i <= m; ++i) cin >> b[i];
    a[++n] = 0;
    b[++m] = 0;
    for(int i = 1; i <= m; ++i) pf[i] = pf[i - 1] + b[i];
    
    for(int i = 0; i <= m + 2; ++i) {
        f[i] = g[i] = 1e9;
    }

    f[0] = g[0] = 0;
    ok[0][0] = 1;
    for(int j = 1; j <= m; ++j) {
        for(int i = 1; i <= n; ++i) {
            if(a[i] == b[j]) {
                if(j > 1 && g[j - 2] <= i - 1 - pf[j - 1]) f[j] = min(f[j], i), ok[j][i] = 1;
                if(ok[j - 1][i - 1]) f[j] = min(f[j], i), ok[j][i] = 1;
            }
        }
        g[j] = min(g[j - 1], f[j] - pf[j]);
    }

    if(ok[m][n]) cout << "YES\n";
    else cout << "NO\n";
    for(int i = 0; i <= n + 1; ++i) a[i] = b[i] = f[i] = g[i] = pf[i] = 0, ok[i] = 0;
}

int32_t main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int tests = 1;
    cin >> tests;
    while(tests--){
        testcase();
    }
    return 0;  
}

/*

4
5 1
2 4 4 2 3
2
5 2
2 4 4 2 3
4 4
1 1
2
1
7 2
2 4 4 2 2 4 4
5 6

*/