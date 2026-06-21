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

const int MOD = 998244353;

void testcase() {
    int n, k;
    cin >> n >> k;
    int mx = 0;
    int cnt = 0;
    vector<int> vt;
    for(int i = 1; i <= n; ++i) {
        int x; cin >> x;
        mx = max(mx, x);
        if(x > 0) vt.push_back(x);
    }
    
    if(mx == 0) cout << 0 << '\n';
    else {
        sort(vt.begin(), vt.end(), greater<int>());
        int ans = mx;
        int prod = 1;
        int cnt = k;
        for(int x: vt) {
            prod = 1LL * prod * x % MOD;
            cnt--;
            if(cnt == 0) {
                cnt = k - 1;
                ans = prod;
            }
        }

        cout << ans % MOD << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
  
    int TC = 1;
    cin >> TC;
    while (TC--) {
        testcase();
    }

    return 0;
}

/*

3
8 3
44 5 2018 8 8 2024 8 28
5 4
4 5 5 1 0
5 2
0 0 0 0 0

*/