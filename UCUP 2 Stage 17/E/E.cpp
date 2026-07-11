#include <bits/stdc++.h>
#ifdef LOCAL
    #include "../debug.hpp"
#else 
    #define dbg(...)
#endif // LOCAL

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

using namespace std;

#define all(v) begin(v), end(v)
#define rall(v) rbegin(v), rend(v)
#define compact(v) v.erase(unique(all(v)), end(v))
#define sz(v) (int)(v).size()

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using tpl = tuple<int,int,int>;

template<class T> bool minimize(T& a, const T& b){  return (a > b ? a = b, 1 : 0); }
template<class T> bool maximize(T& a, const T& b){  return (a < b ? a = b, 1 : 0); }

const int MX = 100005;
int timer = 0;
int f[MX], p[MX];
int vist[MX];
bool dpGood[MX][2][2]; // u, leftSide, nextLightEdge
vector<int> G[MX], revG[MX];

bool dfs(int u) {
    if(vist[u] == timer) return false;
    vist[u] = timer;
    for(int v: G[u]) if(!f[v]) {
        f[v] = u;
        p[u] = v;
        return true;
    }
    for(int v: G[u]) if(dfs(f[v])) {
        f[v] = u;
        p[u] = v;
        return true;
    }
    return false;
}

mt19937 rng(21);

struct Dinic{
    struct Edge{
        int v, rev; ll cap;
    };
    int n;
    vector<vector<Edge>> g;
    vector<int> level, it;
    Dinic(int _n){ init(_n); }

    void init(int _n){
        n = _n;
        g.assign(n, {});
        level.resize(n);
        it.resize(n);
    }

    void addEdge(int u, int v, ll c){
        // dbg(u, v, c);
        g[u].push_back(Edge{v, sz(g[v]), c});
        g[v].push_back(Edge{u, sz(g[u]) - 1, 0});
    }

    bool bfs(int s, int t){
        fill(all(level), -1);
        queue<int> q;
        q.push(s);
        level[s] = 0;
        // for(int i = 0; i < n; ++i){
        //     for(auto e : g[i]){
        //         dbg(i, e.v, e.cap);
        //     }
        // }
        while(!q.empty()){
            int u = q.front(); q.pop();
            // dbg(u);
            for(auto e : g[u]) if(e.cap && level[e.v] == -1){
                level[e.v] = level[u] + 1;
                q.push(e.v);
            }
        }
        return level[t] != -1;
    }
    ll dfs(int u, int t, ll f){
        if(u == t) return f;
        for(int& i = it[u]; i < sz(g[u]); ++i){
            Edge &e = g[u][i];
            if(e.cap && level[e.v] == level[u] + 1){
                ll ret = dfs(e.v, t, min(f, e.cap));
                if(ret){
                    e.cap -= ret;
                    g[e.v][e.rev].cap += ret;
                    return ret;
                }
            }
        }
        return 0;
    }

    ll maxflow(int s, int t){
        ll flow = 0, f;
        while(bfs(s, t)){
            fill(all(it), 0);
            while(f = dfs(s, t, (ll)4e18)){
                flow += f;
            }
        }
        return flow;
    }

    vector<pii> trace(int s, int t){
        vector<pii> ans;
        for(int i = 0; i < n; ++i) if(i != s && i != t){
            for(auto e : g[i]) if(e.v != s && e.v != t && i < e.v){
                if(e.cap == 0){
                    dbg(i, e.v, e.cap, e.rev);
                    ans.emplace_back(i, e.v);
                }
            }
        }
        return ans;
    }
};

void testcase() {
    int N, M;
    cin >> N >> M;
    Dinic network(2 * N + 2);
    int S = 0, T = 2 * N + 1;
    for(int i = 1; i <= N; ++i) network.addEdge(S, i, 1), network.addEdge(i + N, T, 1);
    for(int i = 1; i <= M; ++i) {
        int u, v;
        cin >> u >> v;
        network.addEdge(u, v + N, 1);
        dbg(i, i + N);
        G[u].push_back(v);
        revG[v].push_back(u);
    }
    int maxMatch = network.maxflow(S, T);
    dbg(maxMatch);
    vector<pii> ans = network.trace(S, T);


    for(auto &[u, v] : ans){
        p[u] = v - N, f[v - N] = u;
        // cout << u << ' ' << v - N << '\n';
    }

    vector<tpl> qu;
    for (int i = 1; i <= N; i++) {
        if (!p[i]) dpGood[i][true][true] = true, qu.emplace_back(i, true, true);
        if (!f[i]) dpGood[i][false][true] = true, qu.emplace_back(i, false, true);
    }

    for (int _ = 0; _ < qu.size(); _++) {
        int u; bool leftSide, nextLightEdge; tie(u, leftSide, nextLightEdge) = qu[_];
        for (int v : (leftSide ? G[u] : revG[u])) {
            bool isBold = (v == (leftSide ? p[u] : f[u]));
            if (nextLightEdge == isBold) continue;
            if (!dpGood[v][!leftSide][!nextLightEdge]) {
                dpGood[v][!leftSide][!nextLightEdge] = true;
                qu.emplace_back(v, !leftSide, !nextLightEdge);
            }
        }
    }

    int goodLeft = 0, goodRight = 0;
    for (int i = 1; i <= N; i++) {
        goodLeft += dpGood[i][true][true];
        goodRight += dpGood[i][false][true];
    }
    cout << 1LL * goodLeft * goodRight << "\n";

    for (int u = 1; u <= N; u++) {
        p[u] = f[u] = 0;
        for (int j = 0; j < 2; j++)
            for (int k = 0; k < 2; k++) dpGood[u][j][k] = false;
        G[u].clear(), revG[u].clear();
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
  
    int TC = 1;
    cin >> TC;
    while (TC--) {
        testcase();
    }

    return 0;
}