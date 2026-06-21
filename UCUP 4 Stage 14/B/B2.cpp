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

using ll = long long;
using db = double;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using tpl = tuple<int,int,int>;

template<class T> bool minimize(T& a, const T& b){  return (a > b ? a = b, 1 : 0); }
template<class T> bool maximize(T& a, const T& b){  return (a < b ? a = b, 1 : 0); }

void testcase() {
    int N;
    cin >> N;
    vector<vector<pii>> adj(N);
    for(int i = 0; i < N - 1; ++i){
        int u, v, w;
        cin >> u >> v >> w;
        --u, --v;
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }    

    vector<int> edge(N), sum(N); 
    function<void(int, int)> dfs = [&](int u, int p){
        for(auto [v, w] : adj[u]) if(v != p){
            edge[v] = w;
            dfs(v, u);
            sum[u] += sum[v] + 2;
        }
    };

    const ll inf = 1e18;
    vector<ll> best(2 * N, -inf);
    best[0] = 0;
    vector<int> siz(N);
    vector<vector<array<ll, 2>>> dp(N); 
    function<void(int, int)> dfsDP = [&](int u, int p){
        dp[u].resize(sum[u] + 1, array<ll, 2>{-inf, -inf});
        dp[u][0][0] = 0;
        dp[u][0][1] = 0;
        int cur = 0;
        for(auto [v, w] : adj[u]) if(v != p){
            dfsDP(v, u);    
            vector<array<ll, 2>> nxt(cur + sum[v] + 3, array<ll, 2>{-inf, inf});
            for(int i = 0; i <= cur; ++i){
                for(int j = 0; j <= sum[v] + 2; ++j){
                    for(int a = 0; a < 2; ++a){
                        for(int b = 0; b < 2; ++b){
                            if(a + b == 2){
                                maximize(best[i + j], dp[u][i][a] + dp[v][j][b]);
                            }
                        }
                    }
                }
            }
        }
    };
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
  
    int TC = 1; cin >> TC;
    while (TC--) {
        testcase();
    }

    return 0;
}