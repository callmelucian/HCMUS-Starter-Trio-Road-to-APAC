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

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using tpl = tuple<int,int,int>;

template<class T> bool minimize(T& a, const T& b){  return (a > b ? a = b, 1 : 0); }
template<class T> bool maximize(T& a, const T& b){  return (a < b ? a = b, 1 : 0); }

const int MAX = 1e6 + 5;

int N, M, p[MAX], q[MAX], eu[MAX], ev[MAX];
vector<int> adj[MAX];
vector<pii> ans;
int cnt = 1, vis[MAX];

void dfs(int u, int p){
    if(vis[u]) return;
    dbg(u, p);
    if(u == cnt){
        vis[u] = 1;
        ++cnt;
        sort(all(adj[u]));
        for(auto v : adj[u]) if(!vis[v]){
            dfs(v, u);
        }
    } else{
        assert(p != -1);
        ans.emplace_back(p, cnt);
        dfs(cnt, p);
        dfs(u, p);
    }
}

void testcase() {
    cin >> N >> M;
    for(int i = 1; i <= M; ++i){
        int u, v;
        cin >> u >> v;
        eu[i] = u;
        ev[i] = v;
    }
    for(int i = 1; i <= N; ++i){
        cin >> p[i];
        q[p[i]] = i;
    }

    for(int i = 1; i <= M; ++i){
        int u = q[eu[i]], v = q[ev[i]];
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    for(int i = 1; i <= N; ++i){
        dfs(i, -1);
    }

    cout << sz(ans) << '\n';
    for(auto [u, v] : ans){
        cout << p[u] << ' ' << p[v] << '\n';
    }
}      

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
  
    int TC = 1;
    while (TC--) {
        testcase();
    }

    return 0;
}