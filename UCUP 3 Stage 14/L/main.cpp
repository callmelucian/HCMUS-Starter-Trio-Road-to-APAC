#include <bits/stdc++.h>
#ifdef LOCAL
    #include "../debug.hpp"
#else 
    #define dbg(...) (36)
#endif // LOCAL

using namespace std;

#define int long long
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

const int MAX = 1e5 + 5;
const int mod = 998244353;

struct mint{
    int v;
    mint() : v(0) {}
    mint(int _v) : v(_v % mod) {}
    mint& operator += (const mint& o){
        if((v += o.v) >= mod) v -= mod;
        return *this;
    }
    mint& operator -= (const mint& o){
        if((v -= o.v) < 0) v += mod;
        return *this;
    }
    mint& operator *= (const mint& o){
        v = 1LL * v * o.v % mod;
        return *this;
    }
    mint power(ll n) const {
        mint base = *this, ans = 1;
        for(; n > 0; n >>= 1, base *= base){
            if(n & 1) ans *= base;
        }
        return ans;
    }
    mint inv() const {
        return power(mod - 2);
    }
    mint& operator /= (const mint& o){
        return *this *= o.inv();
    }
    friend mint operator + (mint a, const mint& b){ return a += b; }
    friend mint operator - (mint a, const mint& b){ return a -= b; }
    friend mint operator * (mint a, const mint& b){ return a *= b; }
    friend mint operator / (mint a, const mint& b){ return a /= b; }
    friend ostream& operator << (ostream& stream, mint o){ return stream << o.v; }
};

int N; 
vector<int> adj[MAX];
int par[MAX], dep[MAX];
mint siz[MAX], sumSiz[MAX];


void dfs(int u, int p){
    siz[u] = 1;
    for(auto v : adj[u]) if(v != p){
        dfs(v, u);
        siz[u] += siz[v];
    }
}

void dfsSize(int u, int p){
    sumSiz[u] = siz[u] * siz[u];
    for(auto v : adj[u]) if(v != p){
        dfsSize(v, u);
        sumSiz[u] += sumSiz[v];
    }
}

mint ans = 0;
void calc(int u, int p, mint sumParSize, mint sumPar){
    sumParSize += siz[u] * siz[u];
    for(auto v : adj[u]) if(v != p){
        // ans += mint(N - siz[v]) * (sumSiz[u] - siz[u]);
        // cerr << "edge " << u << ' ' << v << '\n';
        dbg(siz[v] * siz[v], (sumSiz[1] - sumSiz[v] - sumParSize));
        dbg((N - siz[v]) * (N - siz[v]), sumSiz[v]);
        dbg(siz[v] * siz[v], sumPar);
        ans += siz[v] * siz[v] * (sumSiz[1] - sumSiz[v] - sumParSize);
        ans += (N - siz[v]) * (N - siz[v]) * sumSiz[v];
        ans += siz[v] * siz[v] * (sumPar); 
        calc(v, u, sumParSize, sumPar + (N - siz[v]) * (N - siz[v]));
    }
}

void testcase(){
    cin >> N;
    for(int i = 1; i < N; ++i){
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1, -1);
    dfsSize(1, -1);
    ans = 0;
    calc(1, -1, 0, 0);
    mint Q = mint(1LL * N * (N - 1) / 2);
    dbg(ans);
    Q *= Q;
    ans /= Q;
    // {
    //     mint brute = 0;
    //     for(int a = 1; a <= N; ++a){
    //         for(int b = a + 1; b <= N; ++b){
    //             for(int c = 1; c <= N; ++c){
    //                 for(int d = c + 1; d <= N; ++d){
    //                     brute += f(a, b, c, d);
    //                 }
    //             }
    //         }
    //     }
    //     dbg(brute);
    //     brute /= Q;
    //     dbg(brute);
    // }
    cout << ans << '\n';
}   

signed main(){
  ios_base::sync_with_stdio(0); cin.tie(0);
  
  int tests = 1;
  cin >> tests;
  while(tests--){
    testcase();
    for(int i = 1; i <= N; ++i){
        adj[i].clear();
        siz[i] = 0;
        sumSiz[i] = 0;
    }
  }
  return 0;
}