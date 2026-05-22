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

bool check (ll g, ll p) {
    return ((g ^ (p - 1)) % p) == (1 % p);
}

void testcase() {
    ll p, bound; cin >> p >> bound;

    ll ans = 0;
    for (int j = 0; j <= bound; j++) {
        ans += check(j, p);
        if (check(j, p)) dbg(j, (j ^ (p - 1)) % p);
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