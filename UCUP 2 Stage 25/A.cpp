#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
    #include "debug.hpp"
#else
    #define dbg(...) ((void)0)
#endif // LOCAL

#define all(v) begin(v), end(v)
#define rall(v) rbegin(v), rend(v)
#define compact(v) v.erase(unique(all(a)), a.end())
#define sz(v) (int)v.size()
#define pb push_back
#define eb emplace_back

using ll = long long;
using db = double;
using pii = pair<int,int>;
using pll = pair<ll,ll>;

template<class T> bool minimize (T &a, const T &b) { return a > b ? a = b, 1 : 0; }
template<class T> bool maximize (T &a, const T &b) { return a < b ? a = b, 1 : 0; }

int b[1005];

void solve(int l, int r, vector<pii> &a, vector<pii> &ans) {
    if(l >= r) return;
    int mid = (l + r) >> 1;
    int u = mid, v = mid;
    while(u > l && a[u - 1].first == a[mid].first) --u;
    while(v < r && a[v].first == a[mid].first) ++v;
    dbg(l, r, u, v);
    if(a[u].first != 0) {
        for(int i = u; i < r; ++i) {
            ans.push_back({2, a[i].second});
            ++b[i];
        }
        while(b[u] != a[u].first) {
            ans.push_back({1, b[u]});
            for(int i = l; i < r; ++i) if(b[i] == ans.back().second) {
                ++b[i];
            }
        }
    }
    solve(l, u, a, ans);
    solve(v, r, a, ans);
}

void testcase() {
    int n;
    cin >> n;
    vector<pii> a(n);
    for(int i = 0; i < n; ++i) {
        cin >> a[i].first;
        a[i].second = i + 1;
    }
    sort(a.begin(), a.end());

    vector<pii> ans;
    solve(0, n, a, ans);
    dbg();
    for(int i = 0; i < n; ++i) {
        if(b[i] != a[i].first) assert(0);
    }
    cout << ans.size() << '\n';
    for(pii x: ans) cout << x.first << ' ' << x.second << endl;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int tests = 1;
    // cin >> tests;
    while (tests--) {
        testcase();
    }

    return 0;
}

/*

5
5 4 3 2 1





*/