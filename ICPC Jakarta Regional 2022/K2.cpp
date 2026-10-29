#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using tpl = tuple<int,int,int>;

#define all(v) begin(v), end(v)
#define sz(v) (int)v.size()
#define compact(v) v.erase(unique(all(v)), end(v))

template<class T> bool maximize (T &a, const T &b) { return b > a ? a = b, true : false; }
template<class T> bool minimize (T &a, const T &b) { return b < a ? a = b, true : false; }

#ifdef LOCAL
    #include "debug.hpp"
#else 
    #define dbg(...) ((void)0)
#endif //LOCAL

template<int MOD>
struct ModInt {
    static const int mod = MOD;
    int v;
    ModInt(int _v = 0) : v(_v) {refine();}

    void refine() {
        if (abs(v) >= mod) v %= mod;
        if (v < 0) v += mod;
    }

    ModInt& operator += (const ModInt& o){
        v += o.v;
        if(v >= mod) v -= mod;
        return *this;
    }
    ModInt& operator -= (const ModInt& o){
        v -= o.v;
        if(v < 0) v += mod;
        return *this;
    }
    ModInt& operator *= (const ModInt& o){
        v = 1LL * v * o.v % mod;
        return *this;
    }
    ModInt power(ll n) const {
        ModInt res(1), bs = *this;
        for(; n > 0; n /= 2, bs *= bs){
            if(n & 1) res *= bs;
        }
        return res;
    }
    ModInt inv() const {
        return power(mod - 2);
    }
    ModInt& operator /= (const ModInt& o){
        return *this *= o.inv();
    }
    friend ModInt operator + (ModInt a, const ModInt& b){ return a += b; }
    friend ModInt operator - (ModInt a, const ModInt& b){ return a -= b; }
    friend ModInt operator * (ModInt a, const ModInt& b){ return a *= b; }
    friend ModInt operator / (ModInt a, const ModInt& b){ return a /= b; }
    friend ostream& operator << (ostream& op, const ModInt& o){ return op << o.v; }
};

using mint = ModInt<998'244'352>;
using matcha = ModInt<998'244'353>;

using pm = pair<mint,mint>; // (div, mod)

pm mul (const pm &a, const pm &b, int N) {
    mint full = a.first * b.first * mint(N) + b.first * a.second + a.first * b.second;
    full += mint(((1LL * a.second.v * b.second.v) / N) % mint::mod);
    return make_pair(full, mint((1LL * a.second.v * b.second.v) % N));
}

// compute (2^K / N) % MOD and (2^K % N) % MOD
pair<mint,mint> compute (int N, int K) {
    pair<mint,mint> ans = {mint(1 / N), mint(1 % N)}, a = {mint(2 / N), mint(2 % N)};
    for (; K; K >>= 1, a = mul(a, a, N)) {
        dbg(ans, a);
        if (K & 1) ans = mul(ans, a, N);
    }
    return ans;
}

void testcase(){
    int N, K; cin >> N >> K;
    mint a, b; tie(a, b) = compute(N, K);

    vector<matcha> A(2 * N + 1, 1);
    for (int i = 1; i <= N; i++) cin >> A[i].v, A[i + N] = A[i];
    for (int i = 1; i <= 2 * N; i++) A[i] *= A[i - 1];

    auto query = [&] (int l, int r) { return A[r] / A[l - 1]; };

    matcha full = A[N].power(a.v);
    for (int i = 1; i <= N; i++) {
        cout << query(i, i + b.v - 1) * full << " ";
    }
    cout << "\n";
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t = 1;
    // cin >> t;

    while(t--){
        testcase();
    }
    return 0;
}

/*
5 2
1 2 3 4 5

5 2
1 2 3 4 5

8 3
12 5 16 14 10 6 9 2

6 10
3 7 8 2 9 5

2 100
1 2
*/