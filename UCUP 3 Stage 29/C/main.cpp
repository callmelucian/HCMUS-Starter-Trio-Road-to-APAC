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

bool dp[1 << 20][22];

void testcase() {
    for (int msk = 0; msk < (1 << 20); msk++) {
        int mask = msk << 1;
        for (int x = 1; x <= 20; x++) {
            // compute dp[msk][x]
            for (int j = x; j <= 20 && !dp[msk][x]; j += x)
                if ((mask >> j & 1) && !dp[msk ^ (1 << (j - 1))][x + 1]) dp[msk][x] = true;
        }
    }

    for (int l = 1; l <= 20; l++) {
        for (int r = l; r <= 20; r++) {
            int mask = 0;
            for (int i = l - 1; i <= r - 1; i++) mask |= (1 << i);
            if (dp[mask][l]) cout << l << " " << r << "\n";
        }
    }
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