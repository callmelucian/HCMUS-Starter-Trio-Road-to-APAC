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

void testcase() {
    int n, k;
    cin >> n >> k;
    vector<pii> vt;
    vector<int> p(n + 1, 0);
    for(int i = 1; i <= k; ++i) {
        int l, r;
        cin >> l >> r;
        for(int j = l + 1; j <= r; ++j) p[j] = j - 1;
        vt.push_back({r - l, l});
    }
    
    sort(vt.begin(), vt.end(), greater<pii>());
    
    if(vt.size() == 1) {
        for(int i = 0; i < n; ++i) cout << i << " \n"[i + 1 == n];
    }
    else if(vt[0].first != vt[1].first) {
        for(int i = 1; i < (int)vt.size(); ++i) p[vt[i].second] = vt[0].second;
        for(int i = 1; i <= n; ++i) cout << p[i] << " \n"[i == n];
    }
    else if(vt.back().first + 1 < vt[0].first) {
        for(int i = 1; i + 1 < vt.size(); ++i) {
            p[vt[i].second] = vt[0].second;
        }
        p[vt.back().second] = vt[0].second + 1;
        for(int i = 1; i <= n; ++i) cout << p[i] << " \n"[i == n];
    }
    else {
        cout << "IMPOSSIBLE\n";
    }
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

/*

3
12 5
1 5
9 11
7 8
6 6
12 12
4 3
1 1
4 4
2 3
2 2
1 1
2 2

1
12 5
1 5
9 11
7 8
6 6
12 12

*/