#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using tpl = tuple<int,int,int>;

#define all(v) begin(v), end(v)
#define sz(v) (int)v.size()
#define compact(v) v.erase(unique(all(v)), end(v))

template<class T> bool maximize (T &a, const T &b) { return b > a ? a = b, true : false; }
template<class T> bool minimize (T &a, const T &b) { return b < a ? a = b, true : false; }

#ifdef LOCAL
    #include "debug.hpp"
#else 
    #define dbg(...) ((void)0)
#endif //LOCAL

struct Edge {
    int u, v, w;
    Edge() : u(0), v(0), w(0) {}

    bool operator< (const Edge &o) const { return w < o.w; }
    bool operator> (const Edge &o) const { return w > o.w; }
};

struct DSU {
    vector<int> lab;
    int comp;
    DSU (int sz) : lab(sz + 1, -1), comp(sz) {}

    int get (int u) {
        if (lab[u] < 0) return u;
        return lab[u] = get(lab[u]);
    }

    bool unite (int a, int b) {
        a = get(a), b = get(b);
        if (a == b) return false;
        if (-lab[a] < -lab[b]) swap(a, b);
        lab[a] += lab[b], lab[b] = a, comp--;
        return true;
    }
    
    int getComp() const { return comp; }
};

const int maxN = 2e5 + 5;
vector<pii> adj[maxN];
int lift[maxN][19], weight[maxN][19], depth[maxN];

void addEdge (const Edge &item) {
    adj[item.u].emplace_back(item.v, item.w);
    adj[item.v].emplace_back(item.u, item.w);
}

void dfsTree (int u, int p = 0) {
    for (int i = 1; i < 19; i++) {
        lift[u][i] = lift[lift[u][i - 1]][i - 1];
        weight[u][i] = max(weight[lift[u][i - 1]][i - 1], weight[u][i - 1]);
    }
    for (auto [v, w] : adj[u]) {
        if (v == p) continue;
        lift[v][0] = u, weight[v][0] = w, depth[v] = depth[u] + 1;
        dfsTree(v, u);
    }
}

int goUp (int a, int k, int &ans) {
    for (int i = 0; k; i++, k >>= 1)
        if (k & 1) maximize(ans, weight[a][i]), a = lift[a][i];
    return a;
}

int maxWeight (int a, int b) {
    int ans = 0;
    if (depth[a] < depth[b]) swap(a, b);
    a = goUp(a, depth[a] - depth[b], ans);
    if (a == b) return ans;
    for (int i = 18; i >= 0; i--)
        if (lift[a][i] != lift[b][i])
            maximize(ans, max(weight[a][i], weight[b][i])), a = lift[a][i], b = lift[b][i];
    return max({ans, weight[a][0], weight[b][0]});
}

void testcase(){
    int N, M; cin >> N >> M;
    vector<Edge> edges(M), inMST;
    for (Edge &curr : edges) cin >> curr.u >> curr.v >> curr.w;
    sort(all(edges));

    vector<DSU> dsu(2, DSU(N));
    for (Edge curr : edges) {
        for (int i = 0; i < 2; i++) {
            if (dsu[i].unite(curr.u, curr.v)) {
                if (i) addEdge(curr);
                else inMST.push_back(curr);
                dbg(curr.u, curr.v, curr.w, i);
                break;
            }
        }
    }
    if (dsu[1].getComp() != 1)
        return cout << -1 << "\n", void();

    dfsTree(1);
    ll ans = 0;
    for (Edge curr : inMST) {
        ans += maxWeight(curr.u, curr.v) + 1 - curr.w;
        dbg(curr.u, curr.v, maxWeight(curr.u, curr.v), curr.w);
    }
    cout << ans << "\n";
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t = 1;
    // cin >> t;
    while(t--){
        testcase();
    }
    return 0;
}

/*
4 6
1 2 2
1 3 5
1 4 5
2 3 3
2 4 5
3 4 4

3 4
1 2 3
2 3 4
1 3 5
1 3 10

5 10
1 2 14
1 3 14
1 4 9
1 5 15
2 3 8
2 3 10
2 4 13
3 4 8
4 5 10
4 5 15
*/