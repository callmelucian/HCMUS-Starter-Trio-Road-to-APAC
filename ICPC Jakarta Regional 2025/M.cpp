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

template<int MOD>
struct ModInt {
    static const int mod = MOD;
    int a;
    ModInt (int v = 0) : a(v) {refine();}

    void refine() {
        if (abs(a) >= mod) a %= mod;
        if (a < 0) a += mod;
    }

    const ModInt& operator+= (const ModInt &o) {
        if ((a += o.a) >= mod) a -= mod;
        return *this;
    }

    const ModInt& operator-= (const ModInt &o) {
        if ((a -= o.a) < 0) a += mod;
        return *this;
    }

    const ModInt& operator*= (const ModInt &o) {
        a = 1LL * a * o.a % mod;
        return *this;
    }

    const ModInt& operator/= (const ModInt &o) {
        return operator*=(o.inv());
    }

    ModInt pwr (int k) const {
        ModInt ans(1), curr = *this;
        for (; k; k >>= 1, curr *= curr)
            if (k & 1) ans *= curr;
        return ans;
    }

    ModInt inv() const { return pwr(mod - 2); }

    friend ModInt operator+ (ModInt a, const ModInt &b) { return a += b; }
    friend ModInt operator- (ModInt a, const ModInt &b) { return a -= b; }
    friend ModInt operator* (ModInt a, const ModInt &b) { return a *= b; }
    friend ModInt operator/ (ModInt a, const ModInt &b) { return a /= b; }

    friend istream& operator>> (istream &i, ModInt &m) { return i >> m.a, m.refine(), i; }
    friend ostream& operator<< (ostream &o, const ModInt &m) { return o << m.a; }
};
using mint = ModInt<998'244'353>;

void testcase(){
    int N, M, Q; cin >> N >> M >> Q;
    for (int i = 0; i < Q; i++) {
        int x, y; cin >> x >> y;
    }

    cout << mint(M).pwr(N - Q) << "\n";
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

/*
2 3 2
1 0
2 1

100000 100000 1
100000 0
*/