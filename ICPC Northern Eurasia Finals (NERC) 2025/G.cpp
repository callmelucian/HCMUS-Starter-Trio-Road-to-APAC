#include <bits/stdc++.h>
using namespace std;

#define all(v) begin(v), end(v)
#define sz(v) (int)v.size()
#define compact(v) v.erase(unique(all(v)), end(v))
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
template<class T> bool minimize(T& a, const T& b){ return a > b ? a = b, 1 : 0; }
template<class T> bool maximize(T& a, const T& b){ return a < b ? a = b, 1 : 0; }

#define terminate { cout << "Rethink life choices"; exit(0); }

#ifdef LOCAL
    #include "debug.hpp"
#else 
    #define dbg(...) ((void)0)
#endif //LOCAL

ll calc (ll sum, int n) {
    return sum / n + (sum % n ? 1 : 0);
}

ll cost (const vector<ll> &a) {
    return calc(accumulate(all(a), 0LL), (int)a.size() - 2);
}

void testcase(){
    int N; cin >> N;
    vector<ll> B(N + 1);
    for (int i = 1; i <= N; i++) cin >> B[i];

    // edge case
    if (*max_element(all(B)) == 0)
        return cout << 0 << "\n", void();
    if (N == 2) {
        if (B[1] != B[2]) terminate;
        cout << B[1] << "\n";
        return;
    }
    
    // Gaussian eliminitation
    rotate(B.begin() + 1, B.begin() + 2, B.end());
    for (int i = 1, mult = -1; i < N; i++, mult = -mult) B[N] += mult * B[i];

    // deterministic SOEs
    if (N & 1) {
        if (B[N] < 0 || B[N] % 2) terminate;
        B[N] /= 2;
        for (int i = N - 1; i >= 1; i--) {
            B[i] -= B[i + 1];
            if (B[i] < 0) terminate;
        }
        cout << max(*max_element(all(B)), cost(B)) << "\n";
        return;
    }

    // non-deterministic SOEs
    if (B[N]) terminate;
    vector<ll> f(N + 1);
    for (int i = N - 1; i >= 1; i--) f[i] = B[i] - f[i + 1];

    ll minS = LLONG_MAX, minT = LLONG_MAX, cntS = 0;
    ll maxS = LLONG_MIN, maxT = LLONG_MIN, cntT = 0;
    ll sumS = 0, sumT = 0;
    for (int i = 1; i < N; i += 2)
        minimize(minT, f[i]), maximize(maxT, f[i]), cntT++, sumT += f[i];
    for (int i = 2; i  < N; i += 2)
        minimize(minS, f[i]), maximize(maxS, f[i]), cntS++, sumS += f[i];

    auto sumShift = [&] (ll delta) {
        return calc(sumS + delta * cntS + sumT - delta * cntT + delta, cntT + cntS);
    };

    // dbg(minS, maxS, minT, maxT);

    auto ok = [&] (ll M) {
        ll ub = min({M, -maxS + M, minT});
        ll lb = max({0LL, maxT - M, -minS});
        // dbg(lb, ub, min(sumShift(lb), sumShift(ub)));
        return lb <= ub && min(sumShift(lb), sumShift(ub)) <= M;
    };

    ll ans = 0;
    for (ll mask = 1LL << 35; mask; mask >>= 1)
        if (!ok(mask | ans)) ans |= mask;
    cout << ans + 1 << "\n";
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t = 1;
    cin >> t;
    while(t--){
        testcase();
    }
    return 0;
}

/*
1
4
1 2 4 3

5
2
3 3
3
2 2 2
4
1 2 4 3
5
0 2 3 5 4
6
5 8 3 10 14 4

3
4
0 0 0 0
3
0 0 0
7
0 1 1 0 1 1 0
*/