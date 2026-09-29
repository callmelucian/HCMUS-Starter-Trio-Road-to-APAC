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

const int MAX = 305;

int N, A[MAX], cnt[MAX][MAX];
mint F[MAX][MAX], G[MAX][MAX];
mint pw2[MAX * MAX];

void testcase(){
    cin >> N;
    pw2[0] = 1;
    for(int i = 1; i <= N * N; ++i) pw2[i] = pw2[i - 1] + pw2[i - 1];
    for(int i = 1; i <= N; ++i){
        cin >> A[i];
    }

    for(int i = 1; i <= N; ++i){
        for(int j = i + 1; j <= N; ++j){
            for(int k = i + 1; k <= j; ++k){
                cnt[i][j] += A[k] > A[i];
            }
        }
    }

    for(int l = N; l >= 1; --l){
        for(int r = l; r <= N; ++r){
            if(l == r){
                F[l][r] = 1;
                G[l][r] = 1;
            } else{
                for(int k = l + 1; k <= r; ++k){
                    F[l][r] += G[l + 1][k] * F[k][r] * pw2[cnt[k][r]];
                }

                for(int k = l; k <= r; ++k){
                    //G(l, k) * F(k, r - 1) if A[k] < A[r]
                    if(A[k] < A[r]){
                        G[l][r] += G[l][k] * F[k][r - 1] * pw2[cnt[k][r - 1]];
                    }
                }
            }
            dbg(l, r, F[l][r], G[l][r]);
        }
    }
    cout << F[1][N] << '\n';
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