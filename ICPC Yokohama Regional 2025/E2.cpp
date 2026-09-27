#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
    #include "debug.hpp"
#else
    #define dbg(...) (void(0))
#endif

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
using db = double;

struct Fraction {
    ll num, denom;

    Fraction (ll a = 0) : num(a), denom(1) {}
    Fraction (ll a, ll b) : num(a), denom(b) {}

    bool operator<= (const Fraction &o) const { return num * o.denom <= o.num * denom; }
    bool operator< (const Fraction &o) const { return num * o.denom < o.num * denom; }

    const Fraction& operator*= (const Fraction &o) {
        num *= o.num, denom *= o.denom;
        return *this;
    }

    friend Fraction operator* (Fraction a, const Fraction &b) { return a *= b; }

    void normalize() {
        ll g = __gcd(num, denom);
        num /= g, denom /= g;
    }
};

bool checking (int x, int y, int z, int k) {
    if (max({x, y, z}) >= k) return true;
    ll a = 1LL * x * y;
    if (a < k) a *= z;
    return a >= k;
}

bool check (int a, int b, int c, int k, double len) {
    int x = a / len, y = b / len, z = c / len;
    return checking(x, y, z, k);
}

bool ok (Fraction len, int a, int b, int c, int x, int y, int z) {
    return x * len <= a && y * len <= b && z * len <= c;
}

const int LIM = 2;

void testcase() {
    int a, b, c, k; cin >> a >> b >> c >> k;

    // find floating-point result
    double l = 0, r = min({a, b, c});
    for (int t = 0; t < 100; t++) {
        double mid = (l + r) / 2.0;
        if (check(a, b, c, k, mid)) l = mid;
        else r = mid;
    }
    double ans = l;
    // cout << fixed << setprecision(9) << ans << "\n";

    int x = a / ans, y = b / ans, z = c / ans;
    Fraction res;
    for (int dx = -LIM; dx <= LIM; dx++) {
        for (int dy = -LIM; dy <= LIM; dy++) {
            for (int dz = -LIM; dz <= LIM; dz++) {
                int xx = x + dx, yy = y + dy, zz = z + dz;
                if (xx < 1 || yy < 1 || zz < 1 || !checking(xx, yy, zz, k)) continue;
                if (ok(Fraction(a, xx), a, b, c, xx, yy, zz)) maximize(res, Fraction(a, xx));
                if (ok(Fraction(b, yy), a, b, c, xx, yy, zz)) maximize(res, Fraction(b, yy));
                if (ok(Fraction(c, zz), a, b, c, xx, yy, zz)) maximize(res, Fraction(c, zz));
            }
        }
    }

    res.normalize();
    cout << res.num << " " << res.denom << "\n";

    const double eps = 1e-6;
    double lmao = 1.0 * res.num / res.denom;
    assert(abs(ans - lmao) < eps);
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int tests = 1;
    cin >> tests;
    while(tests--){
        testcase();
    }
    return 0;
}