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
    int n, l[3]; cin >> n >> l[0] >> l[1] >> l[2];
    vector<pii> arr(n);
    ll sum = 0;
    for (auto &[pic, cost] : arr) cin >> pic >> cost, pic--, sum += cost;
    ll bound; cin >> bound;
    sort(all(arr), [&] (pii a, pii b) { return a.second < b.second; });

    // bubble sort
    function<void(int,int)> swaps = [&] (int ii, int jj) {
        swap(l[ii], l[jj]);
        for (auto &[pic, cost] : arr) {
            if (pic == ii) pic = jj;
            else if (pic == jj) pic = ii;
        }
    };
    if (l[0] > l[1]) swaps(0, 1);
    if (l[1] > l[2]) swaps(1, 2);
    if (l[0] > l[1]) swaps(0, 1);

    // edge case
    if (sum > l[2]) return cout << "NO\n", void();

    // compute suffix sum
    vector<vector<ll>> sfx(3, vector<ll>(n + 1));
    for (int j = 0; j < 3; j++) {
        for (int i = n - 1; i >= 0; i--)
            sfx[j][i] = sfx[j][i + 1] + (arr[i].first == j ? arr[i].second : 0);
    }

    ll prevTake = 0, ans = 0;
    vector<bool> taken(n);
    
    // first round
    for (int i = 0; i < n; i++) {
        bool check = true;
        if (prevTake + arr[i].second + sfx[0][i + 1] > l[0]) check = false;
        if (prevTake + arr[i].second + sfx[0][i + 1] + sfx[1][i + 1] > l[1]) check = false;
        if (!check && arr[i].first == 0) return cout << "NO\n", void();
        if (check) prevTake += arr[i].second, ans += prevTake, arr[i].second = 0, taken[i] = true;
    }

    // recompute
    for (int j = 0; j < 3; j++) {
        for (int i = n - 1; i >= 0; i--)
            sfx[j][i] = sfx[j][i + 1] + (arr[i].first == j ? arr[i].second : 0);
    }

    // second round
    for (int i = 0; i < n; i++) {
        if (taken[i]) continue;
        bool check = true;
        if (prevTake + arr[i].second + sfx[1][i + 1] > l[1]) check = false;
        if (!check && arr[i].first == 1) return cout << "NO\n", void();
        if (check) prevTake += arr[i].second, ans += prevTake, arr[i].second = 0, taken[i] = true;
    }

    // third round
    for (int i = 0; i < n; i++) {
        if (!taken[i]) prevTake += arr[i].second, ans += prevTake;
    }

    cout << (ans < bound ? "YES" : "NO") << "\n";
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