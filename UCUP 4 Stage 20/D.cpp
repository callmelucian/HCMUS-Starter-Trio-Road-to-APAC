#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
    #include "debug.hpp"
#else
    #define dbg(...) (void(0))
#endif // LOCAL

#define all(v) begin(v), end(v)
#define rall(v) rbegin(v), rend(v)
#define sz(v) (int)v.size()
#define pb push_back
#define eb emplace_back
#define compact(v) v.erase(unique(all(v)), end(v))
template<class T> bool minimize(T& a, const T& b){ return a > b ? a = b, 1 : 0; }
template<class T> bool maximize(T& a, const T& b){ return a < b ? a = b, 1 : 0; }

using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

const int MX = 5005;
int n;
int P[MX];
int f[MX][MX], sum[MX];
void testcase(){
    cin >> N;
    for(int i = 1; i <= n; ++i) cin >> P[i];

    for(int i = 1; i <= n; ++i) {
        int mx = a[i];
        for(int j = i; j >= 1; --j) {
            mx = max(mx, P[j]);
            if((i - j) % 2 == 0) {
                f[i][mx] +=
            }
        }
    }

    for(int i = 1; i <= N; ++i) sum[i] = 0;
    for(int i = 0; i <= N; ++i) {
        for(int j = 0; j < = N; ++j) {
            f[i][j] = 0;
        }
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int tests = 1;
    cin >> tests;
    while(tests--){
        testcase();
    }
    return 0;
}