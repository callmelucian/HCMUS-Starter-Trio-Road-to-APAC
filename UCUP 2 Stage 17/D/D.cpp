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
#define pb push_back
#define eb emplace_back

using ll = long long;
using db = double;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using tpl = tuple<int,int,int>;

template<class T> bool minimize(T& a, const T& b){  return (a > b ? a = b, 1 : 0); }
template<class T> bool maximize(T& a, const T& b){  return (a < b ? a = b, 1 : 0); }

int getMaxDigit (int x) {
    int ans = 0;
    while (x) maximize(ans, x % 10), x /= 10;
    return ans;
}

void testcase() {
    int a, b, c, d; cin >> a >> b >> c >> d;
    if (b - a < 10 && d - c < 10) {
        int ans = 0;
        for (int i = a; i <= b; i++)
            for (int j = c; j <= d; j++)
                maximize(ans, getMaxDigit(i + j));
        cout << ans << "\n";
    }
    else cout << 9 << "\n";
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
  
    int TC = 1; cin >> TC;
    while (TC--) {
        testcase();
    }

    return 0;
}