#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
    #include "debug.hpp"
#else
    #define dbg(...) (void(0))
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

const int maxN = 4e5 + 5;
int depth[maxN], xorAll, leaf[2], par[maxN];
vector<int> adj[maxN];

void dfsTree (int u, int p, int d) {
    depth[u] = (d & 1), xorAll ^= depth[u], par[u] = p;
    if (adj[u].size() == (u != p)) leaf[depth[u]] = u;
    for (int v : adj[u])
        if (v != p) dfsTree(v, u, d + 1);
}

void clearData (int N) {
    for (int i = 1; i <= N; i++) adj[i].clear();
    xorAll = leaf[0] = leaf[1] = 0;
}

void testcase(){
    int N; ll K; cin >> N >> K;
    N *= 2;
    for (int i = 1; i < N; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfsTree(1, 1, 0);

    if (xorAll != (K & 1)) {
        cout << 1 << " " << adj[1][0] << "\n";
        cout << 1 << " " << adj[1][0] << "\n";
        clearData(N);
        return;
    }

    for (int i = 0; i < 2; i++) {
        if (!leaf[i]) continue;
        for (int u = 1; u <= N; u++) {
            if (leaf[i] == u) continue;
            if (i == depth[u]) {
                cout << leaf[i] << " " << par[leaf[i]] << "\n";
                cout << leaf[i] << " " << u << "\n";
                clearData(N);
                return;
            }
        }
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int tests = 1;
    cin >> tests;
    while(tests--){
        testcase();
    }
    return 0;
}

/*
5
2 20
1 2
2 3
3 4

2 4
1 2
2 3
3 4

2 1
1 2
1 3
1 4

2 1
1 2
1 3
1 4

2 1
1 2
1 3
1 4
*/