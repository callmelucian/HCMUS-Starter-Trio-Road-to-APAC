#include <bits/stdc++.h>
#ifdef LOCAL
    #include "../debug.hpp"
#else 
    #define dbg(...) (36)
#endif // LOCAL

using namespace std;

#define all(v) begin(v), end(v)
#define rall(v) rbegin(v), rend(v)
#define compact(v) v.erase(unique(all(v)), end(v))
#define pb push_back
#define eb emplace_back
#define int long long

using ll = long long;
using db = double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
template<class T> bool minimize(T& a, const T& b){  return (a > b ? a = b, 1 : 0); }
template<class T> bool maximize(T& a, const T& b){  return (a < b ? a = b, 1 : 0); }

const int MX = 100005;
int n, m, a[MX], b[MX], t[MX], x[MX];
vector<int> G[MX];

void testcase(){
    cin >> n >> m;
    for(int i = 0; i <= n; ++i) G[i].clear(), a[i] = 0, b[i] = 0;
    t[m + 1] = x[m + 1] = 0;
    for(int i = 1; i <= n; ++i) cin >> a[i], b[i] = a[i];
    for(int i = 1; i <= m; ++i) {
        cin >> x[i] >> t[i];
        G[t[i]].push_back(i);
    }
    for(int i = 1; i <= n; ++i) reverse(G[i].begin(), G[i].end());
    set<int> pos;
    pos.insert(m + 1);
    for(int i = 1; i <= n; ++i) {
        if(G[i].size()) {
            pos.insert(G[i].back());
            G[i].pop_back();
            // cout << " ?? " << G[i].size() << ' ' << i << endl;
        }
        else b[0] += b[i], b[i] = 0;
    }
    int ans = 0;
    // cout << endl;
    // for(int i = 0; i <= n; ++i) cout << b[i] << ' '; cout << endl;
    for(int i = 1; i <= m; ++i) {
        while(pos.size() && *pos.begin() < i) {
            int j = *pos.begin();
            pos.erase(pos.begin());
            if(G[t[j]].size()) {
                pos.insert(G[t[j]].back());
                G[t[j]].pop_back();
            }
            else {
                b[0] += b[t[j]], b[t[j]] = 0;
                pos.insert(m + 1);
            }
        }
        while(ans < x[i] && pos.size()) {
            int j = *pos.begin();
            int d = min(b[t[j]], x[i] - ans);
            // cout << " ?? " << j << endl;
            ans += d;
            b[t[j]] -= d;
            if(b[t[j]] == 0) pos.erase(pos.begin());
        }
        // cout << ans << " __ " << t[i] << " __ ";
        // cout << endl;
        if(ans < x[i]) break;
        if(b[t[i]] == 0) {
            b[t[i]] = a[t[i]];
            if(G[t[i]].size()) {
                pos.insert(G[t[i]].back());
                G[t[i]].pop_back();
            }
            else {
                b[0] += a[t[i]];
                b[t[i]] = 0;
                pos.insert(m + 1);
            }
        }
        else b[t[i]] = a[t[i]];
        // for(int i = 0; i <= n; ++i) cout << b[i] << ' ';
        // cout << endl;
    }
    for(int i = 0; i <= n; i++) ans += b[i];
    cout << ans << '\n';
}

int32_t main(){
  ios_base::sync_with_stdio(0); cin.tie(0);
  
  int tests = 1;
  cin >> tests;
  while(tests--){
    testcase();
  }
  return 0;
}

/*

1
3 1
3 3 3
8 1

2
3 1
3 3 3
8 1
2 2
5 2
1 2
2 1

1
5 10
2 1 3 2 1
3 3
5 1
8 4
9 2
10 2
15 4
17 1
21 5
25 5
26 1

*/