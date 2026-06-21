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
        v = 1LL * o.v * v % mod;
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

void testcase() {
    int N;
    cin >> N;
    vector<mint> fact(N + 1), ifact(N + 1);
    fact[0] = 1; ifact[0] = 1;
    for(int i = 1; i <= N; ++i) fact[i] = fact[i - 1] * mint(i);
    ifact[N] = fact[N].inv();
    for(int i = N - 1; i >= 1; --i) ifact[i] = ifact[i + 1] * mint(i + 1);

    dbg(fact, ifact);
    for(int i = 0; i <= N; ++i) assert((fact[i] * ifact[i]).v == 1);
    vector<int> p(N + 1);
    int last = 0, mx = 0;
    mint ans = 0;
    auto solve = [&](int n){
        dbg(n);
        if(n == 1) return mint(0);
        mint A = ifact[n];

        mint u = (fact[n] - 1) * ifact[n];
        mint P = (u + ((u * u) / (mint(1) - u))) / (mint(1) - u); 
        // dbg(A * B);
        return P / (ifact[n] - 1);
    };
    for(int i = 1; i <= N; ++i){
        cin >> p[i];
        maximize(mx, p[i]);
        if(mx == i){
            ans += solve(i - last);
            last = i;
        }
    }
    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
  
    int TC = 1;
    while (TC--) {
        testcase();
    }

    return 0;
}