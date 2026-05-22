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

const int mn = 1e5 + 5;
int deg[mn];
vector<int> adj[mn], topo;


void testcase() {
    int n, m; cin >> n >> m;
    vector<vector<int>> opr(m + 1);
    for (int i = 1; i <= n; i++) {
        int p; cin >> p;
        while (p--) {
            int x; cin >> x;
            opr[x].push_back(i);
        }
    }

    // create DAG
    for (int j = 1; j <= m; j++) {
        if (opr[j].empty()) continue;
        for (int i = 0; i + 1 < opr[j].size(); i++)
            adj[opr[j][i]].push_back(opr[j].back());
    }

    // construct topological sorting
    priority_queue<int> pq;
    for(int i = 1; i <= n; ++i){
        for(auto j : adj[i]) ++deg[j];
    }

    for(int i = 1; i <= n; ++i) if(!deg[i]){
        pq.push(i);
    }
    while(!pq.empty()){
        int u = pq.top(); pq.pop();
        topo.push_back(u);
        for(auto v : adj[u]){
            --deg[v];
            if(!deg[v]) pq.push(v);
        }
    }

    vector<int> dodge(n); iota(all(dodge), 1);
    if (dodge == topo) cout << "No\n";
    else {
        cout << "Yes\n";
        for (int u : topo) cout << u << " ";
        cout << "\n";
    }
    
    // reset
    for (int i = 1; i <= n; i++) adj[i].clear();
    topo.clear();
    
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
  
    int tests = 1;
    cin >> tests;
    while(tests--){
        testcase();
    }
    return 0;
}