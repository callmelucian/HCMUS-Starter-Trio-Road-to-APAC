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

const int MAX = 2e3 + 5;

int N, M, P, need;
set<int> g[MAX];
vector<int> adj[MAX];
int deg[MAX];

mt19937 rng(123211);
vector<int> solveS2(){
    int maxQ = -1;
    vector<int> finalAns;
    for(int iter = 0; iter < 200; ++iter){
        vector<int> vert(N);
        iota(all(vert), 0);
        shuffle(all(vert), rng);
        vector<int> vis(N);
        vector<int> ans;
        int q = 0;
        for(auto s : vert){
            bool failed = false;
            for(auto t : adj[s]){
                if(vis[t]){
                    failed = true;
                    break;
                }
            }
            if(!failed){
                ++q;
                ans.pb(s);
                vis[s] = 1;
            }
        }
        if(maxQ < q){
            maxQ = q;
            finalAns = ans;
        }
    }
    return finalAns;
}

vector<int> findGreedy(){
    vector<int> remained;
    P = -1;
    for(int iter = 0; iter < 50; ++iter){
        vector<int> vert(N);
        iota(all(vert), 0);
        shuffle(all(vert), rng);
        vector<int> deg(N);
        int mx = -1, atSize = 0;
        vector<int> in(N);
        multiset<int> hihi;
        for(int i = 0; i < N; ++i){
            in[vert[i]] = 1;
            for(auto j : adj[vert[i]]) if(in[j]){
                hihi.erase(hihi.lower_bound(deg[j]));
                ++deg[j];
                ++deg[vert[i]];
                hihi.insert(deg[j]);
            }
            hihi.insert(deg[vert[i]]);

            if(*hihi.begin() > mx){
                mx = *hihi.begin();
                atSize = i + 1;
            }
        }
        // cerr << "ASDFas\n";
        if(mx > P){
            P = mx;
            remained.clear();
            for(int j = 0; j < atSize; ++j){
                remained.pb(vert[j]);
            }
        }
    }
    return remained;
}

void testcase(){
    cin >> N >> M;
    for(int i = 0; i < M; ++i){
        int u, v;
        cin >> u >> v;
        --u, --v;
        ++deg[u];
        ++deg[v];
        adj[u].pb(v);
        adj[v].pb(u);
    }

    vector<int> S1 = findGreedy();
    vector<int> ans = solveS2();
    cout << P << ' ' << sz(ans) << '\n';
    assert((P + 1) * (sz(ans) + 1) > N);
    dbg(P + 1, sz(ans) + 1);
    cout << sz(S1) << " ";
    for(auto u : S1) cout << u + 1 << ' ';
    cout << '\n';
    cout << sz(ans) << " ";
    for(auto u : ans) cout << u + 1 << ' ';
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