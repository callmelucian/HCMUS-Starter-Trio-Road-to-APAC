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

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using tpl = tuple<int,int,int>;

template<class T> bool minimize(T& a, const T& b){  return (a > b ? a = b, 1 : 0); }
template<class T> bool maximize(T& a, const T& b){  return (a < b ? a = b, 1 : 0); }

const int mod = 998244353;

struct mint{
    int v;
    mint() : v(0) {}
    mint(int _v) : v(_v) {}
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
    friend mint operator + (mint a, const mint& b){ return a += b; }
    friend mint operator - (mint a, const mint& b){ return a -= b; }
    friend mint operator * (mint a, const mint& b){ return a *= b; }
    friend ostream& operator << (ostream& stream, const mint& o){
        return stream << o.v;
    }
};

using info = pair<int, mint>;

vector<info> compress(vector<info> res){
    sort(all(res), [&](const info& a, const info& b){
        return a.first < b.first;
    });

    vector<info> last;
    for(int i = 0; i < sz(res); ++i){
        if(last.empty() || last.back().first != res[i].first){
            last.push_back(res[i]);
        }  else{
            last.back().second += res[i].second;
        }
    }
    return last;
}

vector<info> pointwiseProduct(vector<info>& a, vector<info>& b, int bound){
    vector<info> res;
    dbg(a, b);
    for(auto [i, pi] : a){
        for(auto [j, pj] : b){
            if(i + j <= bound){
                res.emplace_back(i + j, pi * pj);
            }   
        }
    }
    return compress(res);
}   

void testcase() {
    int N, K;
    cin >> N >> K;
    vector<vector<int>> adj(N);
    for(int i = 1; i < N; ++i){
        int u, v;
        cin >> u >> v;
        --u, --v;
        dbg(u, v);
        assert(u >= 0 && v >= 0);
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    function<vector<info>(int, int)> dfs = [&](int u, int p){
        dbg(u, p);
        vector<info> cur = {make_pair(1, 1) };
        for(auto v : adj[u]) if(v != p){
            vector<info> below = dfs(v, u);
            cur = pointwiseProduct(cur, below, K + 1);
        }

        vector<info> nw = cur;
        for(auto [i, pi] : cur){
            if(i == K || i == K + 1) nw.emplace_back(0, pi);
        }
        dbg(u, nw);
        return compress(nw);
    };

    vector<info> ans = dfs(0, -1);
    if(!ans.empty() && ans[0].first == 0){
        cout << ans[0].second << '\n';
    } else{
        cout << 0 << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
  
    int TC = 1;
    cin >> TC;
    while (TC--) {
        testcase();
    }

    return 0;
}