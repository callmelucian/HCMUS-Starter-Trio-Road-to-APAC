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
#define size(v) (v).size()
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

ll countMultiple (ll p, ll bound) {
    return bound / p + 1;
}

ll countMultiple (ll p, ll L, ll R) {
    if (R == -1) return 0;
    L = max(L, 0LL);
    return countMultiple(p, R) - (L ? countMultiple(p, L - 1) : 0);
}

void testcase() {
    ll p, bound; cin >> p >> bound;
    bound++;
    
    ll filterMask = 0, ans = 0;
    for (int k = 62; k >= 0; k--) {
        filterMask |= (1LL << k);
        if (bound >> k & 1) {
            ll newMask = (bound ^ (1LL << k) ^ (p - 1)) & filterMask;
            // cout << "Count 1 + kP in range " << newMask << " " << newMask + (1LL << k) - 1 << "\n";
            ans += countMultiple(p, newMask - 1, newMask + (1LL << k) - 1 - 1);
        }
    }
    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
  
    int tests = 1;
    cin >> tests;
    while(tests--){
        testcase();
    }
    return 0;
}