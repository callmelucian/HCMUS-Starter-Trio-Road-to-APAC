#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
    #include "debug.hpp"
#else
    #define dbg(...) ((void)0)
#endif // LOCAL

#define all(v) begin(v), end(v)
#define rall(v) rbegin(v), rend(v)
#define compact(v) v.erase(unique(all(a)), a.end())
#define sz(v) (int)v.size()
#define pb push_back
#define eb emplace_back

using ll = long long;
using db = double;
using pii = pair<int,int>;
using pll = pair<ll,ll>;

template<class T> bool minimize (T &a, const T &b) { return a > b ? a = b, 1 : 0; }
template<class T> bool maximize (T &a, const T &b) { return a < b ? a = b, 1 : 0; }

const int maxN = 2e5 + 5;
vector<int> adj[maxN], cycle, line;
int deg[maxN], cntDeg[10];
bool vist[maxN];

bool dfsCycle (int u, int prv) {
    if (vist[u]) {
        int last = 0;
        dbg(line);
        do {
            cycle.push_back(last = line.back()), line.pop_back();
        } while (last != u);
        return true;
    }
    vist[u] = true;
    line.push_back(u);
    for (int v : adj[u])
        if (v != prv && dfsCycle(v, u)) return true;
    line.pop_back();
    return false;
}

void testcase() {
    int N; cin >> N;
    for(int i = 1; i <= N; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
        deg[a]++, deg[b]++;
    }
    for (int i = 1; i <= N; i++) cntDeg[min(6, deg[i])]++;
    dfsCycle(1, -1);

    ll ans = 0;
    for (int i = 0; i < cycle.size(); i++) {
        int j = (i + 1 == cycle.size() ? 0 : i + 1);
        int u = cycle[i], v = cycle[j];

        cntDeg[min(6, deg[u])]--, cntDeg[min(6, deg[v])]--;
        deg[u]--, deg[v]--;
        cntDeg[min(6, deg[u])]++, cntDeg[min(6, deg[v])]++;

        if (!cntDeg[5] && !cntDeg[6])
            ans += cntDeg[1] + cntDeg[2] + cntDeg[3];

        cntDeg[min(6, deg[u])]--, cntDeg[min(6, deg[v])]--;
        deg[u]++, deg[v]++;
        cntDeg[min(6, deg[u])]++, cntDeg[min(6, deg[v])]++;
    }
    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    int tests = 1;
    // cin >> tests;
    while (tests--) {
        testcase();
    }

    return 0;
}

/*
6
1 2
1 3
1 4
1 5
1 6
2 3
*/