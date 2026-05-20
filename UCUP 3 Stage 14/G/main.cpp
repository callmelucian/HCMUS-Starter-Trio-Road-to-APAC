#include <bits/stdc++.h>
#ifdef LOCAL
    #include "../debug.hpp"
#else 
    #define dbg(...) (36)
#endif // LOCAL

using namespace std;

#define all(v) begin(v), end(v)
#define rall(v) rbegin(v), rend(v)
#define compact(v) v.erase(unique(all(v)), end(v))
#define pb push_back
#define eb emplace_back

using ll = long long;
using db = double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
template<class T> bool minimize(T& a, const T& b){  return (a > b ? a = b, 1 : 0); }
template<class T> bool maximize(T& a, const T& b){  return (a < b ? a = b, 1 : 0); }

const int MAX = 2e5 + 5;

int N, M, K, marked[MAX];
vector<int> adj[MAX];

void testcase(){
    cin >> N >> M >> K;
    for(int i = 0; i < K; ++i){
        int u; cin >> u;
        marked[u] = 1;
        dbg(u);
    }
    for(int i = 0; i < M; ++i){
        int u, v;
        cin >> u >> v;
        dbg(u, v);
        if(marked[u] && marked[v]) continue;
        if(marked[v]) swap(u, v);
        if(marked[u]){
            adj[v].pb(u);
        } else{
            adj[u].pb(v);
            adj[v].pb(u);
        }
    }
    if(K == N){
        cout << "No\n";
        return;
    }
    queue<int> q;
    int root = -1;
    vector<int> vis(N + 1);
    for(int i = 1; i <= N; ++i) if(!marked[i]) root = i;
    q.push(root);
    vis[root] = 1;
    int cnt = 0;
    vector<vector<int>> steps;
    while(!q.empty()){
        ++cnt;
        int u = q.front(); q.pop();
        vector<int> invites = {};
        for(auto v : adj[u]){
            if(!vis[v]){
                invites.pb(v);
                vis[v] = 1;
                q.push(v);
            }
        }
        dbg(u, invites);
        if(int(invites.size()) == 0) continue;
        invites.insert(begin(invites), (int)(invites.size()));
        invites.insert(begin(invites), u);
        steps.push_back(invites);
    }
    if(cnt != N){
        cout << "No\n";
        return;
    }
    cout << "Yes\n";
    cout << (int)steps.size() << '\n';
    for(auto vt : steps){
        cout << vt[0] << ' ';
        for(int i = 1; i < (int)vt.size(); ++i) cout << vt[i] << ' '; cout << '\n';
    }
}

int main(){
  ios_base::sync_with_stdio(0); cin.tie(0);
  
  int tests = 1;
  // cin >> tests;
  while(tests--){
    testcase();
  }
  return 0;
}