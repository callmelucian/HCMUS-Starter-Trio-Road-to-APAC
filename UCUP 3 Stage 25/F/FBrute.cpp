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

const int MX = 200005;
int n, k, q, peak;
int id[MX];
bitset<MX> vist = 0;
vector<int> G[MX], rG[MX];
vector<int> a[MX];
vector<int> pf[MX], nxt[MX], pre[MX];
vector<int> pos[MX], R[MX];
vector<int> topo;


void dfs(int u) {
    vist[u] = 1;
    for(int v: G[u]) if(!vist[v]) {
        dfs(v);
    }
    topo.push_back(u);  
}

void bfs(int u) {
    id[u] = peak;
    for(int v: rG[u]) if(!id[v]) {
        bfs(v);
    }
}

void testcase() {
    cin >> n >> k >> q;
    for(int i = 1; i <= k; ++i) {
        a[i].assign(n + 1, 0);
        for(int j = 1; j <= n; ++j) cin >> a[i][j];
        for(int j = 2; j <= n; ++j) {   
            G[a[i][j - 1]].push_back(a[i][j]);
            rG[a[i][j]].push_back(a[i][j - 1]);
        }
    }

    topo.clear();
    for(int i = 1; i <= n; ++i) if(!vist[i]) dfs(i);
    reverse(topo.begin(), topo.end());
    peak = 0;
    for(int &i: topo) if(!id[i]) {
        peak++;
        bfs(i);
    }
    // for(int i = 1; i <= n; ++i) cnt[id[i]]++;

    for (int i = 1; i <= k; i++)
        for (int j = 1; j <= n; j++) a[i][j] = id[a[i][j]];

    vector<vector<int>> pre(k + 1, vector<int>(n + 1));
    vector<vector<int>> nxt(k + 1, vector<int>(n + 1));

    for (int i = 1; i <= k; i++) {
        vector<int> cnt(n + 1);
        for (int j = 1; j <= n; j++) {
            pre[i][j] = pre[i][j - 1] + cnt[a[i][j]];
            cnt[a[i][j]]++;
        }
        
        nxt[i][n] = n;
        for (int j = n - 1; j >= 1; j--)
            nxt[i][j] = (a[i][j] == a[i][j + 1] ? nxt[i][j + 1] : j);
    }

    function<ll(ll)> C = [&] (ll n) { return n * (n - 1) / 2; };

    ll ans = 0;
    for(int i = 1; i <= q; ++i) {
        int id, l, r;
        cin >> id >> l >> r;
        id = (id + ans) % k + 1;
        l = (l + ans) % n + 1;
        r = (r + ans) % n + 1;
        if(l > r) swap(l, r);

        ans = (nxt[id][l] < r ? pre[id][r] - pre[id][nxt[id][l]] : 0);
        ans += C(min(r, nxt[id][l]) - l + 1);

        cout << ans << "\n";
    }

    topo.clear();
    for(int i = 1; i <= k; ++i) {
        a[i].clear();
        pf[i].clear();
    }
    for(int i = 1; i <= n; ++i) {
        id[i] = 0;
        vist[i] = 0;
        G[i].clear();
        rG[i].clear();
    }
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
5 2 2
1 2 3 4 5
5 4 3 2 1
1 0 2
1 2 1
5 3 3
1 2 3 4 5
1 3 2 4 5
1 2 3 5 4
0 0 2
0 2 3
1 0 3
5 2 2
1 2 3 4 5
5 4 3 2 1
1 0 2
1 2 1
5 3 3
1 2 3 4 5
1 3 2 4 5
1 2 3 5 4
0 0 2
0 2 3
1 0 3
5 2 2
1 2 3 4 5
5 4 3 2 1
1 0 2
1 2 1
5 3 3
1 2 3 4 5
1 3 2 4 5
1 2 3 5 4
0 0 2
0 2 3
1 0 3



1
5 2 2
1 2 3 4 5
5 4 3 2 1
1 0 2
1 2 1

1
5 3 3
1 2 3 4 5
1 3 2 4 5
1 2 3 5 4
0 0 2
0 2 3
1 0 3

1
5 3 3
1 3 4 5 2
3 2 4 1 5
4 3 5 2 1
0 2 3
1 0 2
2 1 3

*/