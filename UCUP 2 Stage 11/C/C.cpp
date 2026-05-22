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

const ll inf = 1e18;
int brute(ll P, int m){
    int ans = 0;
    for(int i = 0; i <= m; ++i){
        if(((i ^ (P - 1)) % P) == 1){
            cerr << i << " || " << (i % (P - 1)) << '\n';
            ++ans;
        }
    }
    return ans;
}
void testcase() {
    ll P, m;
    cin >> P >> m;
    int ans = brute(P, m);
    cout << ans << "\n";
    // ll l = 1, r = min(100ll, (inf / P) + 1), ans = 0;
    // while(l <= r){
    //     ll mid = l + r >> 1;
    //     dbg(l, r, mid);
    //     ll target = mid * P + 1;
    //     ll last = -1;
    //     for(ll i = 0; i <= mid; ++i){
    //         ll cur = (i * P + 1) ^ (P - 1);
    //         cerr << cur << " \n"[i == mid];
    //         if(last > (cur)){
    //             cerr << "failed\n";
    //             exit(1);
    //         }
    //         last = cur;
    //     }
    //     if((target ^ (P - 1)) <= m) ans = mid, l = mid + 1;
    //     else r = mid - 1;
    // }
    // cout << ans << '\n';
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