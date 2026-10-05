#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
    #include "debug.hpp"
#else
    #define dbg(...) ((void)0)
#endif // LOCAL

#define sz(v) (int)v.size()
#define all(v) begin(v), end(v)
#define compact(v) v.erase(unique(all(v)), end(v))
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

const int MAX = 5e5 + 5;
const int mod = 1e9 + 7;
struct mint{
    int v;
    mint(int _v = 0) : v(_v) {}
    mint& operator += (const mint& o){
        v += o.v;
        if(v >= mod) v -= mod;
        return *this;
    }
    mint& operator -= (const mint& o){
        v -= o.v;
        if(v < 0) v += mod;
        return *this;
    }
    mint& operator *= (const mint& o){
        v = 1LL * v * o.v % mod;
        return *this;
    }
    mint power(ll n) const {
        mint res(1), bs = *this;
        for(; n > 0; n /= 2, bs *= bs){
            if(n & 1) res *= bs;
        }
        return res;
    }
    mint inv() const { return power(mod - 2); }
    mint& operator /= (const mint& o){ return *this *= o.inv(); }
    friend mint operator + (mint a, const mint& b){ return a += b; }
    friend mint operator - (mint a, const mint& b){ return a -= b; }
    friend mint operator * (mint a, const mint& b){ return a *= b; }
    friend mint operator / (mint a, const mint& b){ return a /= b; }
    friend ostream& operator << (ostream& op, const mint& o){
        return op << o.v;
    }
};  

mint fact[MAX], ifact[MAX];

struct Stack{
    int size;
    vector<pii> lastNon;

    Stack(int init) : size(1), lastNon({{1, init}}) {}
    
    void add(int c){
        ++size;
        if(c != 1){
            lastNon.push_back({size, c});
        } 
    }
    
    void pop(){
        if(lastNon.back().first == size) lastNon.pop_back();
        --size;
    }

    pii query(){
        return {size - lastNon.back().first, lastNon.back().second};
    }
};

void testcase(){
    int N;
    cin >> N;
    vector<int> A(N + 1), B(N + 1), W(N + 1);
    for(int i = 1; i <= N; ++i){
        cin >> A[i];
    }
    for(int i = 1; i <= N; ++i) cin >> B[i];
    for(int i = 1; i <= N; ++i) cin >> W[i];
    vector<int> type(N + 1);
    vector<vector<int>> adj(N + 1);
    vector<int> vis(N + 1);
    vector<int> prvCycle(N + 1, -1);
    vector<vector<int>> cycles;
    for(int i = 1; i <= N; ++i){
        if(A[i] < A[B[i]]){
            type[i] = 0;
        } else if(A[i] < A[B[i]] + W[B[i]]){
            type[i] = 1;
        } else{
            type[i] = 2;
        }
    }
    for(int i = 1; i <= N; ++i) if(!vis[i]){
        int u = i;
        vector<int> path;
        while(!vis[u]){
            vis[u] = 1;
            path.push_back(u);
            u = B[u];
        }
        if(vis[u] == 2){
            //useless
            for(auto u : path){
                vis[u] = 2;
            }
        } else{
            vector<int> cycle;
            int badCycle = 1; 
            while(vis[u] != 2){
                if(type[u] != 1) badCycle = 0;
                cycle.push_back(u);
                vis[u] = 2;
                u = B[u];
            }

            for(int i = 0; i < sz(cycle); ++i){
                prvCycle[cycle[i]] = (i > 0 ? cycle[i - 1] : cycle.back());
                dbg(cycle[i], prvCycle[i]);
                if(badCycle) type[cycle[i]] = 2; 
            }
            for(auto u : path) vis[u] = 2;
        }
    }

    for(int i = 1; i <= N; ++i) {
        if(prvCycle[i] != -1 && prvCycle[B[i]] != -1){

        }else{
            adj[B[i]].push_back(i);
        }
    }

    vector<mint> probPush(N + 1);
    for(int i = 1; i <= N; ++i) dbg(i, type[i]);
    for(int i = 1; i <= N; ++i) if(prvCycle[i] != -1 && type[i] != 1){
        int u = i, c = 1;
        dbg(u);
        Stack helper(0);
        while(c || type[u] == 1){
            c = 0;
            dbg("??", u);
            function<void(int)> dfs = [&](int u){
                helper.add(type[u]);
                dbg(u, type[u]);
                if(type[u] != 1){
                    if(type[u] == 0) probPush[u] = 1;
                    else probPush[u] = 0;
                } else{
                    auto [siz, cl] = helper.query();
                    if(cl == 0){
                        probPush[u] = ifact[siz + 1];
                    } else{
                        probPush[u] = 0;
                    }
                }

                for(auto v : adj[u]){  
                    dfs(v);
                }
                helper.pop();
            };  
            dfs(u);
            helper.add(type[u]);
            u = prvCycle[u];
        }
    }

    for(int i = 1; i <= N; ++i){
        mint ans = A[i];
        ans += probPush[i] * mint(W[i]);
        cout << ans << ' ';
    }
    cout << '\n';
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    fact[0] = ifact[0] = 1;
    for(int i = 1; i < MAX; ++i){
        fact[i] = fact[i - 1] * mint(i);
    }
    ifact[MAX - 1] = fact[MAX - 1].inv();
    for(int i = MAX - 2; i >= 1; --i){
        ifact[i] = ifact[i + 1] * mint(i + 1);
    }
    int tests = 1;
    cin >> tests;
    while(tests--){
        testcase();
    }
    return 0;
}