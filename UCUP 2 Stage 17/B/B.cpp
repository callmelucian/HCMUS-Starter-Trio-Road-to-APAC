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
    mint power(ll n) const {
        mint res(1), base = *this;
        for(; n > 0; n >>= 1, base *= base){
            if(n & 1) res *= base;
        }
        return res;
    }
    mint inv() const { return power(mod - 2); }
    mint& operator /= (const mint& o){
        return *this *= o.inv();
    }
    friend mint operator + (mint a, const mint& b){ return a += b; }
    friend mint operator - (mint a, const mint& b){ return a -= b; }
    friend mint operator * (mint a, const mint& b){ return a *= b; }
    friend mint operator / (mint a, const mint& b){ return a /= b; }
    friend ostream& operator << (ostream& stream, const mint& o){
        return stream << o.v;
    }
};

template<class mint, int root, int maxSize>
struct NTT{
    static const int mod = 998244353;
    vector<mint> rt, out;
    vector<int> rev;
    int s, LG;

    NTT(){
        LG = 32 - __builtin_clz(maxSize - 1);
        s = 1LL << LG;
        assert(s > 1);
        assert(LG <= __builtin_ctz(mod - 1));
        rt.assign(s, mint(0));
        rev.resize(s, 0);
        rt[0] = rt[1] = mint(1);
        for(int k = 2, t = 2; k < s; k <<= 1, ++t){
            mint z = mint(root).power((mod - 1) >> t);
            for(int i = k; i < 2 * k; ++i){
                rt[i] = (i & 1 ? rt[i >> 1] * z : rt[i >> 1]);
            }
        }
        for(int i = 0; i < s; ++i){
            rev[i] = (rev[i >> 1] | ((i & 1) << LG)) >> 1;
        }
    }

    void ntt(vector<mint>& a){
        int n = sz(a);
        assert((n & (n - 1)) == 0);
        assert(n <= s);
        int shift = __builtin_clz(n) - __builtin_clz(s);
        for(int i = 0; i < n; ++i){
            int j = rev[i] >> shift;
            if(i < j) swap(a[i], a[j]);
        }
        for(int k = 1; k < n; k <<= 1){
            for(int i = 0; i < n; i += 2 * k){
                for(int j = 0; j < k; ++j){
                    mint u = rt[j + k] * a[i + j + k];
                    mint v = a[i + j];
                    tie(a[i + j], a[i + j + k]) = make_pair(v + u, v - u);
                }
            }
        }
    }
    vector<mint> conv(vector<mint> a, vector<mint> b){
        // dbg(a, b);
        if(a.empty() || b.empty()) return {};
        int need = sz(a) + sz(b) - 1;
        int n = 1;
        while(n < need) n <<= 1;
        assert(n <= s);
        a.resize(n); b.resize(n);
        out.assign(n, mint(0));
        ntt(a); ntt(b);
        mint invN = mint(n).inv();
        for(int i = 0; i < n; ++i) out[-i & (n - 1)] = a[i] * b[i] * invN;
        ntt(out);
        out.resize(need);
        // dbg(out);
        return out;
    }
};

NTT<mint, 3, (int)2e5 + 5> nttHelper;
const int MAX = 1e5 + 5;

int N, K, BOUND;
vector<int> adj[MAX];
vector<mint> f[MAX];

void dfs(int u, int p){
    // dbg(u, p);
    f[u] = {0, 1};
    for(auto v : adj[u]) if(v != p){
        dfs(v, u);
        f[u] = nttHelper.conv(f[u], f[v]);
        if(sz(f[u]) > K + 2){
            f[u].resize(K + 2);
        }
    }


    if(sz(f[u]) > K) f[u][0] += f[u][K];
    if(sz(f[u]) > K + 1) f[u][0] += f[u][K + 1];
    // dbg(u, f[u]);
}

void solve1(){
    dfs(1, -1);
    cout << f[1][0] << '\n';
}


namespace sub2 {
    int child[MAX], x[MAX], y[MAX];
    mint f[MAX];
    
    int szDfs (int u, int p) {
        child[u] = 1;
        for (int v : adj[u])
            if (v != p) child[u] += child[v];
        x[u] = child[u] / K - child[u] % K, y[u] = child[u] % K;
        return child[u];
    }

    void dfs (int u, int p) {
        if (child[u] <= K + 1) {
            if (child[u] == K || child[u] == K + 1) f[u] = 1;
            return;
        }
        int sumX = 0, sumY = 0;
        mint mult = 1;
        for (int v : adj[u]) {
            if (v == p) continue;
            dfs(v, u), sumX += x[v], sumY += y[v];
            mult *= f[v];
        }
        if (x[u] == 1 + sumX) {
            if (sumY == y[u]) f[u] = mult;
            else f[u] = 0;
        }
        else {
            if (y[u] == 1 + sumY) f[u] = mult;
            else f[u] = 0;
        }
    }
};

void solve2(){
    sub2::szDfs(1, 1);
    sub2::dfs(1, 1);

    cout << sub2::f[1] << "\n";
}

void testcase() {
    cin >> N >> K;
    cerr << N << ' ' << K << '\n';
    for(int i = 1; i < N; ++i){
        int u, v;
        cin >> u >> v;
        dbg(u, v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    BOUND = 0; //sqrt(N) + 1;
    if(K <= BOUND){
        solve1();
    } else{
        solve2();
    }
}

void reset(){
    for(int i = 1; i <= N; ++i){
        adj[i].clear();
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int TC = 1;
    cin >> TC;
    while (TC--) {
        testcase();
        reset();
    }

    return 0;
}