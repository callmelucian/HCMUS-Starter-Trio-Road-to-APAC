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
    int n, f, rmax = 0; cin >> n >> f;
    vector<pii> people(n);

    ll sumCost = 0;
    for (auto &[l, r] : people)
        cin >> l >> r, maximize(rmax, r), sumCost += r - l;
    
    vector<int> ord(n), ans;
    vector<bool> picked(n);
    iota(all(ord), 0), sort(all(ord), [&] (int i, int j) {
        return people[i].first < people[j].first;
    });

    // phase 1: get to rmax
    int iter = 0;
    pii bestR = {0, 0};
    while (f < rmax) {
        while (iter < n && people[ord[iter]].first <= f)
            maximize(bestR, {people[ord[iter]].second, ord[iter]}), iter++;
        if (bestR.first <= f) {
            if (iter == n) { cout << "Quit CP\n"; exit(0); }
            picked[ord[iter]] = true, ans.push_back(ord[iter]);
            sumCost += people[ord[iter]].first - f;
            f = people[ord[iter++]].second;
        }
        else {
            picked[bestR.second] = true;
            ans.push_back(bestR.second);
            f = bestR.first;
        }
    }

    
    // phase resolve others
    ord.clear();
    for (int i = 0; i < n; i++)
    if (!picked[i]) ord.push_back(i);
    dbg(ans, ord);
    sort(all(ord), [&] (int i, int j) {
        return people[i].second > people[j].second;
    });
    ans.insert(ans.end(), all(ord));

    // print result
    cout << sumCost << "\n";
    for (int u : ans) cout << u + 1 << " ";
    cout << "\n";
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