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

const int mod = 1e9 + 9;
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
        mint res(1), base = *this;
        for(; n > 0; n >>= 1, base *= base){
            if(n & 1) res *= base;
        }
        return res;
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
    friend bool operator == (const mint& a, const mint& b){ return a.v == b.v; }
    friend bool operator != (const mint& a, const mint& b){ return a.v != b.v; }
    friend ostream& operator << (ostream& op, const mint& o){ return op << o.v; }
};

// using mint = long double;

mint l[1010][1010], n[1010];

void testcase() {
    int m, K; cin >> m >> K;
    mint M(m);

    auto cnt = [&] (int k) {
        return 1 + (M - 1) * k;
    };

    l[0][0] = n[0] = 1;
    for (int k = 1; k <= K; k++) {
        mint a = (mint(1) - mint(1) / cnt(k - 1)), b = M / cnt(k - 1);
        for (int i = 1; i <= K; i++) {
            l[i][k] = l[i][k - 1] * a + l[i - 1][k - 1] * b;
            n[i] += l[i - 1][k - 1] * b;
        }
    }

    mint ans = 0;
    for (int j = 1; j < K; j++) {
        ans += mint(K - j) / (1 + (M - 1) * j);
    }
    cout << M * K + M * M * ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    int tests = 1;
    // cin >> tests;
    while (tests--) {
        testcase();
    }

    return 0;
}