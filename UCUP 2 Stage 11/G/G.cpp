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
#define int long long

using ll = long long;
using db = double;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using tpl = tuple<int,int,int>;

template<class T> bool minimize(T& a, const T& b){  return (a > b ? a = b, 1 : 0); }
template<class T> bool maximize(T& a, const T& b){  return (a < b ? a = b, 1 : 0); }

const int MX = 200005;
int n, W, k;
pair<int, int> a[MX];
int f[MX], g[MX];

void testcase() {
    cin >> n >> W >> k;
    for(int i = 1; i <= n; ++i) {
        cin >> a[i].first >> a[i].second;
    }
    sort(a + 1, a + 1 + n);
    priority_queue<int, vector<int>, greater<int>> Q;
    for(int i = n; i >= 1; --i) {
        g[i] = g[i + 1] + a[i].second;       
        Q.push(a[i].second);
        if(Q.size() > k) {
            g[i] -= Q.top();
            Q.pop();
        }
    }
    int ans = 0;
    for(int i = 1; i <= n; ++i) {
        for(int j = W; j >= a[i].first; j--) {
            f[j] = max(f[j], f[j - a[i].first] + a[i].second);
        }
        ans = max(ans, g[i + 1] + f[W]);
    }
    cout << ans;
}

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
  
    int tests = 1;
    // cin >> tests;
    while(tests--){
        testcase();
    }
    return 0;
}

/*

4 10  1
9 10
10 1
3 5
5 20

5 13 2
5 16
5 28
7 44
8 15
8 41

*/