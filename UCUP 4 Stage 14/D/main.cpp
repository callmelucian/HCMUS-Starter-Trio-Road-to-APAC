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
    int N;
    cin >> N;
    vector<ll> A(N + 1);
    for(int i = 1; i <= N; ++i) cin >> A[i];

    vector<vector<ll>> dp(N + 1, vector<ll>(2, 0));
    dp[1][1] = 3 * A[1];
    dp[1][0] = 2 * A[1];
    for(int i = 2; i <= N; ++i){
        dp[i][1] = max(dp[i - 1][1] + 5 * A[i], dp[i - 1][0] + 5 * A[i]);
        dp[i][0] = max(dp[i - 1][1] + 3 * A[i], dp[i - 1][0] + 5 * A[i]);
    }
    cout << max(dp[N - 1][0] + 3 * A[N], dp[N - 1][1] + 2 * A[N]) << '\n'; 
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

4
3
1 2 3
4 -1 3 7 6
5
4 1 0 5 2
6
4 -3 7 5 -9 3

*/