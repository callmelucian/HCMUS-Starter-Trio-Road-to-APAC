#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
    #include "debug.hpp"
#else
    #define dbg(...) ((void)0)
#endif // LOCAL

#define int long long
#define all(v) begin(v), end(v)
#define compact(v) v.erase(unique(all(v)), end(v))
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using tpiii = tuple<int, int, int>;


const int MX = 500005;
int n, q;
int a[MX], ans[MX];
int d[MX];
int paris[MX];
int child[MX];
bool used[MX];
vector<pii> G[MX];
vector<pii> qr[MX];

void lucian(int u, int p = 0) {
    child[u] = 1;
    for(auto [v, w]: G[u]) if(v != p && !used[v]) {
        lucian(v, u);
        child[u] += child[v];
    }
}

int dwuy(int u, int p, const int &half) {
    for(auto [v, w] : G[u]) if(v != p && !used[v] && child[v] > half) {
        return dwuy(v, u, half);
    }
    return u;
}

void lkthanh(int u, int p, int id, vector<pii> &vertices, vector<tpiii> &queries) {
    // d[u] = min(d[u], (int)1e9 + 5);
    paris[u] = id;
    vertices.push_back({d[u], u});
    for(auto [w, i] : qr[u]) 
        queries.push_back({w - d[u], id, i});

    for(auto [v, w] : G[u]) if(v != p && !used[v]) {
        d[v] = d[u] + w;
        lkthanh(v, u, id, vertices, queries);
    }
}

void hxano(int cen) {
    vector<pii> vertices;
    vector<tpiii> queries;
    for(auto [w, i] : qr[cen]) 
        queries.push_back({w, -1, i});
    vertices.push_back({0, cen});
    paris[cen] = -2;
    for(auto [v, w] : G[cen]) if(!used[v]) {
        d[v] = w;
        lkthanh(v, cen, v, vertices, queries);
    }
    
    sort(vertices.begin(), vertices.end(), greater<pii>());
    sort(queries.begin(), queries.end(), greater<tpiii>());
    dbg(vertices);
    dbg(queries);

    pii minFirst = {1e18, 0};
    pii minSecond = {1e18, 0};
    for(size_t i = 0, j = 0; i < queries.size(); ++i) {
        auto [K, pId, aId] = queries[i];
        while(j < vertices.size() && vertices[j].first > K) {
            auto [_, dudu] = vertices[j];
            int vId = paris[dudu];
            int w = a[dudu];
            dbg(queries[i], vertices[j]);
            if(minFirst.second == 0) 
                minFirst = pii(w, vId);
            else if(vId == minFirst.second) 
                minFirst.first = min(minFirst.first, w);
            else if(w < minFirst.first) 
                minSecond = minFirst, 
                minFirst = pii(w, vId);
            else 
                minSecond = min(minSecond, pii(w, vId));

            ++j;
        }
        if(pId == minFirst.second) ans[aId] = min(ans[aId], minSecond.first);
        else ans[aId] = min(ans[aId], minFirst.first);
    }
}

void lelam(int u) {
    lucian(u);
    int cen = dwuy(u, 0, child[u] >> 1);
    dbg(cen);
    hxano(cen);
    used[cen] = 1;
    for(auto [v, w]: G[cen]) {
        if(!used[v]) lelam(v);
    }
}

void testcase(){
    cin >> n >> q;
    for(int i = 1; i <= n; ++i) cin >> a[i];
    for(int i = 1; i < n; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        G[u].push_back({v, w});
        G[v].push_back({u, w});
    }
    for(int i = 1; i <= q; ++i) {
        int u, k;
        cin >> u >> k;
        qr[u].push_back({k, i});
    }
    
    int sybau = 0;
    map<int, int> mp; for(int i = 1; i <= n; ++i) mp[a[i]] = 1;
    while(mp[sybau]) ++sybau;

    for(int i = 1; i <= q; ++i) ans[i] = sybau;
    lelam(1);
    for(int i = 1; i <= q; ++i) cout << ans[i] << '\n';
}

int32_t main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int tests = 1;
    // cin >> tests;
    while(tests--){
        testcase();
    }
    return 0;
}

/*

5 4
3 9 0 1 2
1 2 10
3 1 4
3 4 3
3 5 2
3 0
1 0
4 6
6 7

*/