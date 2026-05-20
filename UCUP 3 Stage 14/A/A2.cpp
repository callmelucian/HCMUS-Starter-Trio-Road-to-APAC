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


const int MAX = 1000;

int nodes, save[MAX];
vector<pii> adj[MAX];

int findCeil(int n){
    int k = 1;
    while(k < n){
        k <<= 1;
    }
    return k;
}

int recurse(int k){
    if(save[k] == 0){
        save[k] = ++nodes;
        if(k == 0) return save[k];
        
        adj[save[k]].eb(recurse(k - 1), 0);
        adj[save[k]].eb(recurse(k - 1), 1);
    } 
    return save[k];
}

map<pii, int> edges;
bool dfs(int id, int l, int r, int u, int v) {
    if(l > v || r < u) return 0;
    if(u <= l && r <= v) {
        // int pre = __builtin_popcount(id) == 1 ? 1 : id / 2;
        // bool edge = id & 1; 
        // edges[{pre, id}] = edge; 
        int k = 31 - __builtin_clz(r - l + 1);
        return recurse(k);
    }
    bool flag = 0;
    int mid = (l + r) >> 1;
    if(dfs(id << 1, l, mid, u, v)) {
        flag = 1;
        int X = ((-id&id) - id) == 0 ? 1 : id;
        int Y = id << 1;
        bool weight = 0;
        edges[{X, Y}] = weight;
    }
    if(dfs(id << 1 | 1, mid + 1, r, u, v)) {
        flag = 1;
        int X = id;
        int Y = id << 1;
        bool weight = 1;
        edges[{X, Y}] = weight;
    }   

    return flag;
}

void dfs(int id, int l, int r, int u, int v){
    if(u <= l && r <= v){
        int u = ++nodes;
        int k = 31 - __builtin_clz(r - l + 1);
        assert((1 << k) == r - l + 1);
        adj[u].    
    } else{
        int mid = l + r >> 1;
        int u = ++nodes;
        adj[u].eb(dfs(l, mid, u, v), 0);
        adj[u].eb(dfs(mid + 1, r, u, v, 0), 1);
        return u;
    }
}

void testcase(){
    int L, R;
    cin >> L >> R;
    int bound = findCeil(R);
    int source = dfs(1, bound, L, R);
    
    cout << nodes << '\n';
    for(int i = 1; i <= nodes; ++i){
        cout << (int)adj[i].size() << ' ';
        for(auto [j, w] : adj[i]){
            cout << j << ' ' << w << ' ';
        }
        cout << '\n';
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