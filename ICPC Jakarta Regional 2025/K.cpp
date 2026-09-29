#include <bits/stdc++.h>
using namespace std;

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

#ifdef LOCAL 
    #include "debug.hpp"
#else
    #define dbg(...) (void(0))
#endif //LOCAL

const int MAX = 3e5 + 5;

int N, M, K, Q;
set<pii> adj[MAX];
set<tuple<int, int, int>> st;
bool ok[MAX];

void testcase(){
    cin >> N >> M >> K >> Q;
    ok[1] = 1;
    int ans = 1;
    for(int i = 1; i <= M; ++i){
        int u, v, w;
        cin >> u >> v >> w;
        if(ok[u] && !ok[v]){
            st.insert({w, u, v});
        } 
        adj[u].insert({v, w});
    }

    while(Q--){
        int t;
        cin >> t;
        if(t == 1){
            int u, v, w;
            cin >> u >> v >> w;
            if(ok[u] && !ok[v]){
                st.insert({w, u, v});
            }
            adj[u].insert({v, w});
        } else if(t == 2){
            int u, v, w;
            cin >> u >> v >> w;
            if(ok[u] && !ok[v]){
                dbg(w, u, v);
                st.erase({w, u, v});
            }
            adj[u].erase({v, w});
        } else{
            int k;
            cin >> k;

            auto itL = st.lower_bound({k, -1, -1});
            auto itR = st.lower_bound({k + 1, -1, -1});
            vector<int> newCan;
            for(auto it = itL; it != itR; it = st.erase(it)){
                auto [w, u, v] = *it;
                if(ok[v]) continue;
                newCan.pb(v);
                adj[u].erase({v, w});
                dbg(w, u, v);
                ok[v] = 1;
                ++ans;
            }
            dbg(newCan);
            for(auto v : newCan){
                for(auto [nxt, w] : adj[v]) if(!ok[nxt]){
                    st.insert({w, v, nxt});
                }   
            }
        
            cout << ans << '\n';
        }
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