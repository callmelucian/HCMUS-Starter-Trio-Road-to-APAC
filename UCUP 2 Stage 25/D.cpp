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

// void testcase() {
//     int N, M;
//     cin >> N >> M;

//     vector<vector<int>> adj(N + 1);
//     for(int i = 0; i < N - 1; ++i){
//         int u, v;
//         cin >> u >> v;
//         adj[u].pb(v);
//         adj[v].pb(u);
//     }
//     function<void(int)> dfs = [&](int u){
//         for(auto v : adj[u]){
//             adj[v].erase(find(all(adj[v]), u));
//             dfs(v);
//         }
//     };
//     dfs(N);

//     auto nxt = [&](int i){ return i == M ? 1 : i + 1; };
//     auto prv = [&](int i){ return i == 1 ? M : i - 1; };

//     vector<vector<int>> vis(N + 1, vector<int>(N + 1));
//     vector<vector<int>> dp(N + 1, vector<int>(N + 1, 1));
//     for(int i = 1; i <= M; ++i){
//         dp[i][nxt(i)] = 0;
//         vis[i][nxt(i)] = 1;
//     }

//     int state0 = M;
//     function<int(int, int)> calc = [&](int u, int v){
//         dbg(u, v);
//         if(vis[u][v]) return dp[u][v];
//         vis[u][v] = 1;
//         if(adj[u].empty()){
//             dp[u][v] = 1;
//             for(auto y : adj[v]){
//                 dp[u][v] &= calc(u, y);
//             }
//             return dp[u][v];
//         }
//         if(adj[v].empty()){
//             dp[u][v] = 0;
//             for(auto x : adj[u]){
//                 dp[u][v] |= calc(x, v);
//             }
//             return dp[u][v];
//         }
//         dbg(u, v, adj[u], adj[v]);
//         for(auto x : adj[u]){
//             int ex = 0;
//             for(auto y : adj[v]){
//                 if(calc(x, y) == 0){
//                     dbg(x,y);
//                     ex = 1;
//                     break;
//                 }
//             }
//             if(!ex) return dp[u][v] = 1;
//         }
//         ++state0;
//         return dp[u][v] = 0;
//     };
//     calc(N, N);
//     // dbg(state0, M);
//     // for(int i = 1; i <= N; ++i){
//     //     for(int j = 1; j <= N; ++j){
//     //         if(vis[i][j]){
//     //             dbg(i, j, dp[i][j]);
                
//     //         }
//     //     }
//     // }
// }

void testcase(){
    int N, M;
    cin >> N >> M;
    vector<vector<int>> adj(N + 1);
    for(int i = 1; i < N; ++i){
        int u, v;
        cin >> u >> v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    int L = 32 - __builtin_clz(N);
    vector<int> dep(N + 1), cntGo(N + 1);
    vector<vector<int>> nodesByDep(N + 1);
    vector<vector<int>> lift(L + 1, vector<int>(N + 1));
    function<void(int, int)> dfs = [&](int u, int p){
        nodesByDep[dep[u]].pb(u);
        for(auto v : adj[u]) if(v != p){
            adj[v].erase(find(all(adj[v]), u));
            lift[0][v] = u;
            dep[v] = dep[u] + 1;
            cntGo[v] = cntGo[u] + (sz(adj[u]) == 1);
            for(int i = 1; (1 << i) <= dep[v]; ++i){
                lift[i][v] = lift[i - 1][lift[i - 1][v]];
            }
            dfs(v, u);
        }
    };
    dfs(N, -1);
    function<int(int, int)> binaryLifting = [&](int u, int k){
        for(int i = 0; (1 << i) <= k; ++i){
            if(k >> i & 1){
                u = lift[i][u];
            }
        }
        return u;
    };

    vector<vector<int>> states(N + 1);
    for(int i = 1; i <= M; ++i){
        int j = (i == M ? 1 : i + 1);   
        if(dep[i] < dep[j]){
            int upj = binaryLifting(j, dep[j] - dep[i]);
            if(cntGo[j] - cntGo[upj] == dep[j] - dep[upj]){
                //can be 0
                states[i].eb(upj);
            }
        } else if(dep[i] > dep[j]){
            int upi = binaryLifting(i, dep[i] - dep[j]);
            if(cntGo[i] - cntGo[upi] == dep[i] - dep[upi]){
                //can be 0
                states[upi].pb(j);
            }
        } else{
            states[i].pb(j);
        }
    }
    // for(int i = 1; i <= N; ++i){
    //     dbg(i, states[i]);
    // }

    int D = *max_element(all(dep));
    vector<pii> activeStates;
    for(int d = D; d >= 1; --d){
        for(auto u : nodesByDep[d]){
            for(auto v : states[u]){
                activeStates.eb(u, v);
            }
        }

        vector<pair<pii, pii>> S;
        for(auto [u, v] : activeStates){
            S.eb(make_pair(lift[0][u], lift[0][v]), make_pair(u, v));
        }
        // dbg(D, activeStates);
        sort(all(S));
        vector<pii> newStates;
        for(int i = 0; i < sz(S); ++i){
            vector<pii> downStates = {S[i].second};
            while(i + 1 < sz(S) && S[i].first == S[i + 1].first){
                downStates.eb(S[++i].second);
            }

            int cntDied = 0, last = -1;
            for(auto [a, b] : downStates){
                cntDied += last != a;
                last = a;
            }
            if(cntDied == sz(adj[S[i].first.first])){
                newStates.eb(S[i].first);
            }
        }
        swap(newStates, activeStates);
    }
    cout << (activeStates.empty() ? "Tie\n" : "Doddle\n");
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    int tests = 1;
    cin >> tests;
    while (tests--) {
        testcase();
    }

    return 0;
}