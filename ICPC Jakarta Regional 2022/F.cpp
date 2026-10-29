#include <bits/stdc++.h>
using namespace std;

#define int long long
#define all(v) begin(v), end(v)
#define sz(v) (int)v.size()
#define compact(v) v.erase(unique(all(v)), end(v))
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

#ifdef LOCAL
    #include "debug.hpp"
#else 
    #define dbg(...) ((void)0)
#endif //LOCAL

void testcase(){
    int n;
    cin >> n;
    priority_queue<pii, vector<pii>, greater<pii>> Q;

    for(int i = 1; i <= n; ++i) {
        int x; cin >> x;
        int e = __lg(-x & x);
        Q.push({e, x});
    }

    while(Q.size() > 1) {
        int a = Q.top().second; Q.pop();
        int b = Q.top().second; Q.pop();
        int c = __gcd(a, b) * 2;
        Q.push({__lg(-c & c), c});
    }

    cout << Q.top().second;
}
int32_t main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t = 1;
    // cin >> t;
    while(t--){
        testcase();
    }
    return 0;
}

/*

3
2 4 6

3
3 5 7

4
9 9 9 9

5
10 100 1000 10000 100000

*/