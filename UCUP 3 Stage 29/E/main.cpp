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

const int MX = 500005;
int n, m;
int h[MX], vi[MX], p[20][MX];
vector<int> G[MX];

void dfs(int u) {
    h[u] = h[p[0][u]] + 1;
    vi[u] = 1;
    for(int i = 1; i < 20; ++i) {
        p[i][u] = p[i - 1][p[i - 1][u]];
    }
    for(int v: G[u]) if(!vi[v]) {
        p[0][v] = u;
        dfs(v);
    }   
}

int LCA(int u, int v) {
    if(h[u] > h[v]) swap(u, v);
    for(int i = 19; i >= 0; --i) {
        if(h[p[i][v]] >= h[u]) {
            v = p[i][v];
        }
    }
    if(u == v) return u;
    for(int i = 19; i >= 0; --i) {
        if(p[i][u] != p[i][v]) {
            u = p[i][u];
            v = p[i][v];
        }
    }
    return p[0][u];
}

map<pair<int, int>, bool> mp;
int fuck(int u, int v, int chim) {
    int sz = 1;
    int puv = LCA(u, v);
    int fu = -1, fv = -1;
    int gg = 1;
    while(u != puv && vi[u] < 2) {
        if(vi[u] == 1 && fu == -1) fu = u;
        if(fu == -1) ++gg;
        vi[u]++;
        u = p[0][u];
        ++sz;
    }
    while(v != puv && vi[u] < 2) {
        if(vi[v] == 1 && fv == -1) fv = v;
        if(fv == -1) ++gg;
        vi[v]++;
        v = p[0][v];
        ++sz;
    }
    mp[{fu, fv}] = 1;
    if(fu == -1) fu = puv;
    if(fv == -1) fv = puv;
    if(fu > fv) swap(u, v);
    if(fu != puv || fv != puv) {
        if(gg * 2 != chim) {
            return false;
        }
    }
    if(u == puv && v == puv) {
        if(chim == -1) chim = sz;
        if(sz != chim) return false;
        return chim;
    }
    if(u > v) swap(u, v);
    if(mp[{u, v}] == 0 || sz * 2 != chim) return false;
    return chim;
}

void testcase() {
    cin >> n >> m;
    for(int i = 1; i <= n; ++i) {
        G[i].clear();
        h[i] = vi[i] = 0;
        for(int j = 0; j < 20; ++j) p[j][i] = 0;
    }
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    dfs(1);
    for(int i = 1; i <= n; ++i) vi[i] = 0;
    int skibidi = -1;
    for(int u = 1; u <= n; ++u) {
        for(int v: G[u]) {
            if(p[0][u] == v) continue;
            if(p[0][v] == u) continue;
            if(u > v) continue;
            int chim = fuck(u, v, skibidi);
            if(chim == false) {
                cout << "No\n";
                return;
            }
            if(skibidi == -1) skibidi = chim;
            else if(skibidi != chim) {
                cout << "No\n";
                return;
            }
        }
    }
    cout << "Yes\n";
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

/*

2
4 5
1 2
2 3
3 1
2 4
4 1
5 6
1 2
2 3
1 4
1 5
4 3
5 3

*/