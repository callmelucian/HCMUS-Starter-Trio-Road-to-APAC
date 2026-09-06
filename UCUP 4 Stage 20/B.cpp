#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
    #include "debug.hpp"
#else
    #define dbg(...) (void(0))
#endif // LOCAL

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

template<int MOD>
struct ModInt {
    static const int mod = MOD;
    int v;
    ModInt (int a = 0) : v(a) {refine();}

    void refine() {
        if (abs(v) >= mod) v %= mod;
        if (v < 0) v += mod;
    }

    const ModInt& operator+= (const ModInt &o) {
        if ((v += o.v) >= mod) v -= mod;
        return *this;
    }

    const ModInt& operator-= (const ModInt &o) {
        if ((v -= o.v) < 0) v += mod;
        return *this;
    }

    const ModInt& operator*= (const ModInt &o) {
        v = 1LL * v * o.v % mod;
        return *this;
    }

    const ModInt& operator/= (const ModInt &o) {
        return operator*=(o.inv());
    }

    ModInt pwr (int k) const {
        ModInt ans(1), a(*this);
        for (; k; k >>= 1, a *= a)
            if (k & 1) ans *= a;
        return ans;
    }

    ModInt inv() const { return pwr(mod - 2); }

    friend ModInt operator+ (ModInt a, const ModInt &b) { return a += b; }
    friend ModInt operator- (ModInt a, const ModInt &b) { return a -= b; }
    friend ModInt operator* (ModInt a, const ModInt &b) { return a *= b; }
    friend ModInt operator/ (ModInt a, const ModInt &b) { return a /= b; }

    friend istream& operator>> (istream &i, ModInt &m) { return i >> m.v, m.refine(), i; }
    friend ostream& operator<< (ostream &o, const ModInt &m) { return o << m.v; }
};
using mint = ModInt<998'244'353>;

const int maxN = 5005;
vector<int> adj[maxN];
mint fact[maxN], ifact[maxN];
bool vist[maxN];
int A[maxN];

mint C (int n, int k) {
    if (n < k) return 0;
    return fact[n] * ifact[n - k] * ifact[k];
}

mint AC (int n, int k) {
    if (n < k) return 0;
    return fact[n] * ifact[n - k];
}

void dfs (int u, int &deg, int &node) {
    if (vist[u]) return;
    vist[u] = true, deg += adj[u].size(), node++;
    for (int v : adj[u]) dfs(v, deg, node);
}

void clearData (int N) {
    for (int i = 1; i <= N; i++)
        adj[i].clear(), vist[i] = false;
}

void addEdge (int a, int b) {
    adj[a].push_back(b);
    adj[b].push_back(a);
}

void testcase(){
    int N; cin >> N;
    for (int i = 1; i <= N; i++) cin >> A[i];
    for (int L = 1, R = N; L < R; L++, R--)
        if (A[L] != A[R]) addEdge(A[L], A[R]);

    int countTree = 0, sumTree = 0, S = 0;
    vector<int> trees;

    for (int i = 1; i <= N; i++) {
        if (vist[i]) continue;
        int sumDeg = 0, node = 0;
        dfs(i, sumDeg, node);
        int edge = sumDeg / 2;

        // if (node == 1) continue;
        if (edge >= node + 1)
            return cout << mint(N + 1) * fact[N] << "\n", clearData(N);
        
        if (edge == node) S += node;
        if (edge + 1 == node) countTree++, sumTree += node, trees.push_back(node);
        dbg(node, edge);
    }
    dbg(countTree, sumTree, S);

    vector<mint> pick(countTree + 1);
    pick[0] = 1;
    for (int node : trees)
        for (int j = countTree; j >= 1; j--) pick[j] += pick[j - 1] * mint(node);

    dbg(pick);

    mint ans = 0;
    vector<mint> prf(N + 1);
    for (int i = 0; i <= N; i++) {
        mint curr = 0;
        for (int t = 0; t <= countTree; t++) {
            curr += AC(N - i, t) * AC(i, S + sumTree - t) * pick[t];
        }
        prf[i] = curr * fact[N - S - sumTree];
        ans += (prf[i] - (i ? prf[i - 1] : 0)) * i;
    }
    dbg(prf);
    cout << ans << "\n";
    
    
    clearData(N);
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);

    fact[0] = 1;
    for (int i = 1; i < maxN; i++) fact[i] = fact[i - 1] * i;
    ifact[maxN - 1] = mint(1) / fact[maxN - 1];
    for (int i = maxN - 1; i > 0; i--) ifact[i - 1] = ifact[i] * i;

    int tests = 1;
    cin >> tests;
    while(tests--){
        testcase();
    }
    return 0;
}

/*
4
3
1 2 3
4
2 3 3 2
6
4 6 4 6 4 6
10
1 5 2 10 2 6 3 1 10 2

1
10
1 5 2 10 2 6 3 1 10 2

1
3
1 2 3
*/