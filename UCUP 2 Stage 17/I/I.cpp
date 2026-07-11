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

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using tpl = tuple<int,int,int>;

template<class T> bool minimize(T& a, const T& b){  return (a > b ? a = b, 1 : 0); }
template<class T> bool maximize(T& a, const T& b){  return (a < b ? a = b, 1 : 0); }

void testcase() {
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; ++i){
        cin >> a[i];
    }
    vector<pii> sol;
    for(int i = 0; i < n; ++i){
        int chosen = -1;
        for(int j = i + 1; j < n; ++j){
            if(a[j] < a[i]){
                chosen = j;
            }
        }
        if(chosen == -1) continue;
        sol.emplace_back(i, chosen);
        vector<int> select(n + 1);
        dbg(i, chosen);
        for(int k = i; k <= chosen; ++k) select[a[k]] = 1;

        int cnt = i;
        dbg(select);
        for(int k = 1; k <= n; ++k) if(select[k]){
            dbg(cnt, k);
            a[cnt++] = k;
        }
        dbg(a);
    }
    cout << sz(sol) << '\n';
    for(auto [u, v] : sol) cout << u + 1 << ' ' << v + 1 << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
  
    int TC = 1;
    cin >> TC;
    while (TC--) {
        testcase();
    }

    return 0;
}