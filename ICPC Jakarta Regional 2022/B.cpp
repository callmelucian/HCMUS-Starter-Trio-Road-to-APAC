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

const int MX = 200005;
int n;
pii ans[MX];
pii edges[MX];
vector<int> G[MX];

int ot(int id, int u) {
    return edges[id].first ^ edges[id].second ^ u;
}

set<int> st[MAX];

void dfsSolve(int u){
    for(auto id : adj[u]){
        int v = ot(id, u);
        dfsSolve(v);
        st[v].insert(v);
        if(sz(st[v]) > sz(st[u])) swap(st[u], st[v]);
        for(auto x : st[v]) st[u].insert(x);
    }

    for(auto q : queries[u]){
        if(!st[u].empty()){
            
        }
    }
}

void dfs(int u) {
    for(auto id : adj[u]) {
        int v = ot(id, u);
        adj[v].erase(find(all(adj[v]), id));
        queries[u].emplace_back(id);
        dfs(v);
    }

    for(int i = 0; i + 1 < sz(adj[u]); ++i){
        int p = adj[u][i], q = adj[u].back();
        int x = ot(p, u), y = ot(q, u);
        ans[p] = {x, y};
    }
}   

void testcase(){
    cin >> n;
    for(int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        edges[i] = {u, v};
        G[u].push_back(i);
        G[v].push_back(i);
    }
    for(int i = 1; i <= n; ++i) if(G[i].size() == n - 1) {
        cout << -1;
        return;
    }
    dfs(1);

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