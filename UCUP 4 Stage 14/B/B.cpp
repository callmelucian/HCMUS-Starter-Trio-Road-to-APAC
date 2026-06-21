#include <bits/stdc++.h>
#ifdef LOCAL
    #include "../debug.hpp"
#else 
    #define dbg(...)
#endif // LOCAL

using namespace std;

#define all(v) begin(v), end(v)
#define rall(v) rbegin(v), rend(v)
#define compact(v) v.erase(unique(all(v)), end(v))
#define sz(v) (v).size()
#define pb push_back
#define eb emplace_back
#define int long long

using ll = long long;
using db = double;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using tpl = tuple<int,int,int>;

template<class T> bool minimize(T& a, const T& b){  return (a > b ? a = b, 1 : 0); }
template<class T> bool maximize(T& a, const T& b){  return (a < b ? a = b, 1 : 0); }

const int MX = 4004;
int n, k;
int f[MX], child[MX], sum[MX];
vector<pair<int, int>> G[MX];
int dp[MX][MX];

void dfs(int u, int p) {
    child[u] = 0;
    sum[u] = 0;
    vector<int> g(MX, 0);
    for(pair<int, int> e: G[u]) {
        int v = e.first;
        int w = e.second;
        if(v == p) continue;
        dfs(v, u);
        sum[u] += w + w + sum[v];
        child[u] += child[v] + 2;

        for(int i = child[u]; i >= 0; --i) {
            for(int j = 0; j <= child[v]; ++j) {
                int c = i + j + 1;
                if(c <= child[u]) {
                    f[c] = max(f[c], dp[u][i] + w + dp[v][j]);
                    dp[u][c] = max(dp[u][c], g[i] + dp[v][j] + w);
                    f[c] = max(f[c], dp[u][c]);
                }
            }
            if(i + child[v] + 2 <= child[u]) {
                int c = i + child[v] + 2;
                dp[u][c] = max(dp[u][c], dp[u][i] + w + sum[v] + w);
                f[c] = max(f[c], dp[u][c]);
            }
        }

        for(int i = child[u]; i >= child[v] + 2; --i) {
            g[i] = max(g[i], g[i - child[v] - 2] + sum[v] + w + w);
            f[i] = max(f[i], g[i]);
        }
    }
}


void testcase() {
    cin >> n;
    int all = 0;
    for(int i = 1; i < n; ++i) {
        int u, v, c;
        cin >> u >> v >> c;
        G[u].push_back({v, c});
        G[v].push_back({u, c});
        all += c * 2;
    }

    dfs(1, 0);
    for(int i = 1; i <= 2 * n; ++i) f[i] = max(f[i], f[i - 1]);
    for(int i = 0;  i <= 2 * n; ++i) dbg(i, f[i]);
    for(int i = 0; i <= 2 * n - 2; ++i) cout << all - f[i] << ' ';
    cout << '\n';

    for(int i = 0; i <= 2 * n; ++i) {
        G[i].clear();
        sum[i] = f[i] = child[i] = 0;
        for(int j = 0; j <= 2 * n; ++j) dp[i][j] = 0;
    }
}



int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
  
    int TC = 1; cin >> TC;
    while (TC--) {
        testcase();
    }

    return 0;
}

/*

5
5
1 2 2
2 3 3
2 4 1
4 5 3
5
1 2 2
2 3 3
2 4 1
4 5 3
7
1 2 1
1 3 1
1 4 4
3 5 5
3 6 1
6 7 4
5
1 2 2
2 3 3
2 4 1
4 5 3
14
1 2 2
1 3 1
2 4 3
2 5 4
3 6 2
3 7 3
3 8 1
3 9 5
5 10 2
5 11 2
6 12 2
8 13 1
8 14 1

1
14
1 2 2
1 3 1
2 4 3
2 5 4
3 6 2
3 7 3
3 8 1
3 9 5
5 10 2
5 11 2
6 12 2
8 13 1
8 14 1

5
1 2 1
1 3 2
1 4 2
1 5 2

*/