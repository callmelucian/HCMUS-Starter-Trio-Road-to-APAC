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

using int128 = __int128_t;

namespace Solve3 {
    int solveQuad (ll a, ll b, ll c) {
        dbg(a, b, c);
        ll delta = b * b - 4 * a * c, s = sqrt(delta);
        if (s * s != delta) return 0;
        return (s > b) && ((s - b) % (2 * a) == 0);
    }

    void solve (ll N) {
        int ans = 0;
        for (int128 delta = 1; delta * delta * delta < N; delta++) {
            int128 a = 3 * delta, b = 3 * delta * delta, c = delta * delta * delta - N;
            if (b % a == 0 && c % a == 0) {
                b /= a, c /= a, a = 1;
                ans += solveQuad(a, b, c);
            }
        }
        cout << ans << "\n";
    }
};

namespace Solve2Pt {
    int128 binpow (int128 a, int k) {
        int128 ans = 1;
        for (; k; k >>= 1, a *= a)
            if (k & 1) ans *= a;
        return ans;
    }

    void solve (int128 N, int k) {
        int ans = 0;
        for (int L = 1, R = 1; binpow(R, k) - binpow(R - 1, k) <= N; R++) {
            while (binpow(R, k) - binpow(L, k) > N) L++;
            ans += (binpow(R, k) - binpow(L, k) == N);
        }
        cout << ans << "\n";
    }
};

void testcase() {
    ll N, k; cin >> N >> k;

    if (k == 3) return Solve3::solve(N), void();
    return Solve2Pt::solve(N, k), void();
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    int tests = 1;
    cin >> tests;
    while (tests--) {
        testcase();
    }

    return 0;
}

/*
3
7 3
15 4
31 5
*/