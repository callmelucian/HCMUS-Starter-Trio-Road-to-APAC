#include <bits/stdc++.h>
using namespace std;
#define int long long
#define all(v) begin(v), end(v)
#define compact(v) v.erase(unique(all(v)), end(v))
using ll = long long;
using pii = pair<int, int>;

#ifdef LOCAL
    #include "debug.hpp"
#else 
    #define dbg(...) ((void)0)
#endif //LOCAL

void testcase(){
    int n;
    cin >> n;
    vector<pair<int, int>> a;
    int pre = 0;
    for(int i = 1; i <= n; ++i) {
        int x; cin >> x;
        if(x != pre) a.push_back({x, 0}), pre = x;
        ++a.back().second;
    }

    int ans = 0, cur = 0;
    for(int i = 0; i < (int)a.size(); ++i) {
        if(i > 1) {
            if(a[i].first > a[i - 1].first && a[i - 1].first > a[i - 2].first) cur = a[i - 1].second;
            if(a[i].first < a[i - 1].first && a[i - 1].first < a[i - 2].first) cur = a[i - 1].second;
        }
        ans += a[i].second * (a[i].second - 1) / 2;
        ans += a[i].second * cur;
        cur += a[i].second;
        dbg(i, cur, a[i]);
    }
    cout << ans;
}
int32_t main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int tests = 1;
    // cin >> tests;
    while(tests--){
        testcase();
    }
    return 0;
}