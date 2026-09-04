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

const int MOD = 1e9 + 9;

int add(int a, int b) {
    return (a += b) + (a >= MOD ? -MOD : 0);
}

int mul(int a, int b) {
    return 1LL * a * b % MOD;
}

int bp(int a, int b) {
    int res = 1;
    for(; b; b>>= 1, a = mul(a, a)) if(b & 1) res = mul(res, a);
    return res;
}

int divi(int a, int b) {
    return mul(a, bp(b, MOD - 2));
}

int m, k;
int p[10000005];
int f[10000005];

int w(int i, int m) {
    return divi(i * m - i, (i + 1) * m - i);
}

int c(int i, int m) {
    return i * m - i + 1;
}

void testcase() {
    cin >> m >> k;

    if(k == 1) {
        cout << m;
        return;
    }
    if(k == 2) {
        cout << 3 * m;
        return;
    }

    f[2] = 3 * m;
    p[2] = 2;
    int temp = 1;
    for(int i = 3; i <= k; ++i) {
        temp = mul(temp, divi(m, c(i - 1, m)));
        p[i] = add(p[i - 1], temp);
        f[i] = add(f[i - 1], mul(m, p[i]));
    }  

    cout << mul(mul(m, k - 2), p[k]);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    cout << add(10, divi(4, 3)) << '\n';
    cout << add(divi(2, 3), 2) << '\n';
    // return 0;

    int tests = 1;
    // cin >> tests;
    while (tests--) {
        testcase();
    }

    return 0;
}