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

ll penalty (ll start, ll single, ll amount) {
    return start * amount + single * amount * (amount + 1) / 2;
}

void testcase() {
    int n, l[3]; cin >> n >> l[0] >> l[1] >> l[2];
    vector<pii> arr(n);
    ll sum = 0;
    for (auto &[a, b] : arr) cin >> a >> b, sum += b, a--;
    sort(all(arr));
    ll bound; cin >> bound;

    // compress array
    vector<vector<pii>> a(3, vector<pii>(1));
    vector<vector<ll>> pref(3);
    for (int j = 0; j < 3; j++) {
        int hold = -1, cnt = 0;
        for (int i = 0; i < n; i++) {
            if (arr[i].first != j) continue;
            if (hold != arr[i].second && cnt)
                a[j].emplace_back(hold, cnt), cnt = 0;
                cnt++, hold = arr[i].second;
            }
        if (cnt) a[j].emplace_back(hold, cnt);
        if (a[j].empty()) continue;

        pref[j] = vector<ll>(a[j].size());
        for (int i = 1; i < a[j].size(); i++)
            pref[j][i] = pref[j][i - 1] + 1LL * a[j][i].first * a[j][i].second;
    }
    
    // bubble sort
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            if (l[j] > l[j + 1]) swap(l[j], l[j + 1]), swap(a[j], a[j + 1]);
    if (sum > l[2]) return cout << "NO\n", void();
    
    
    // first phase
    vector<vector<ll>> dp(a[1].size() + 1, vector<ll>(a[2].size() + 1, LLONG_MAX));
    for (int j = 0; j < a[1].size(); j++) {
        int k = 0;
        for (; k < a[2].size() && pref[0].back() + pref[1][j] + pref[2][k] <= l[0] &&
               pref[0].back() + pref[1].back() + pref[2][k] <= l[1]; k++);
        k--;
        if (k < 0) continue;
        
        vector<ll> freq(301);
        for (int ii = 1; ii < a[0].size(); ii++) freq[a[0][ii].first] += a[0][ii].second;
        for (int jj = 1; jj <= j; jj++) freq[a[1][jj].first] += a[1][jj].second;
        for (int kk = 1; kk <= k; kk++) freq[a[2][kk].first] += a[2][kk].second;
        
        ll curPenalty = 0, pre = 0;
        for (int p = 1; p <= 300; p++)
            curPenalty += penalty(pre, p, freq[p]), pre += p * freq[p];

        dbg(j, k, curPenalty);
        dp[j][k] = curPenalty;
    }

    for (int j = 0; j < a[1].size(); j++) {
        for (int k = 0; k < a[2].size(); k++) {
            if (dp[j][k] == LLONG_MAX) continue;
            ll curTime = pref[0].back() + pref[1][j] + pref[2][j];
            if (j + 1 < a[1].size()) {
                // try to extend j
                if (curTime + 1LL * a[1][j + 1].first * a[1][j + 1].second <= l[1])
                    minimize(dp[j + 1][k], dp[j][k] + penalty(curTime, a[1][j + 1].first, a[1][j + 1].second));
            }
            if (k + 1 < a[2].size()) {
                // try to extend k
                minimize(dp[j][k + 1], dp[j][k] + penalty(curTime, a[2][k + 1].first, a[2][k + 1].second));
            }
        }
    }

    int n1 = (int)a[1].size() - 1, n2 = (int)a[2].size() - 1;
    cout << (dp[n1][n2] < bound ? "YES" : "NO") << "\n";
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
1
3 100 150 175
1 100
2 25
3 50
401
*/

/*
1
5 100 200 300
1 30
1 30
1 40
2 110
3 50
1275
*/

/*
3
3 100 150 175
1 100
2 25
3 50
401
5 100 200 300
1 30
1 30
1 40
2 110
3 50
1275
1 100 300 300
1 300
300
*/