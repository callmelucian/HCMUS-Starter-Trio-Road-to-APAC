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
#define int long long

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using tpl = tuple<int,int,int>;

template<class T> bool minimize(T& a, const T& b){  return (a > b ? a = b, 1 : 0); }
template<class T> bool maximize(T& a, const T& b){  return (a < b ? a = b, 1 : 0); }

const int INF = 4e18;
const int MX = 100005;
int n;
int a[MX], b[MX], c[MX];
int pf[MX], sf[MX];

bool check(int mid) {
    for(int i = 0; i <= n + 1; ++i) pf[i] = sf[i] = 0;
    int cur = 0;
    for(int i = 1; i <= n; ++i) {
        if(a[i] == 0 && b[i] >= mid) cur++;
        else if(a[i] < 0) {
            int x = floor(1.0l * (mid - b[i]) / a[i]);
            int itr = upper_bound(c + 1, c + 1 + n, x) - c - 1;
            ++pf[itr];
        }
        else if(a[i] > 0) {
            int x = ceil(1.0l * (mid - b[i]) / a[i]);
            int itr = lower_bound(c + 1, c + 1 + n, x) - c;
            ++sf[itr];
        }
    }

    int pivot = 0;
    { // a[i] < 0
        int quantity = 0;
        int used = 0;
        for(int i = 1; i <= n; ++i) quantity += pf[i];
        for(int i = 1; i <= n; ++i) {
            if(quantity) ++cur, ++used, --quantity;
            else {
                pivot = i - 1;
                break;
            }
            while(pf[i]) {
                if(used) --used;
                else --quantity;
                --pf[i];
            }
        }
    }

    { // a[i] > 0
        int quantity = 0;
        int used = 0;
        for(int i = n; i >= 1; --i) quantity += sf[i];
        for(int i = n; i > pivot; --i) {
            if(quantity) ++cur, ++used, --quantity;
            else break;
            while(sf[i]) {
                if(used) --used;
                else --quantity;
                --sf[i];
            }
        }
    }

    return cur >= ((n + 1) >> 1);
}

void testcase() {
    cin >> n;
    for(int i = 1; i <= n; ++i) cin >> a[i];
    for(int i = 1; i <= n; ++i) cin >> b[i];
    for(int i = 1; i <= n; ++i) cin >> c[i];

    sort(c + 1, c + 1 + n);

    int res = 0;
    for(int lo = -INF, hi=INF; lo<=hi; ){
        int mid = (lo + hi) >> 1;
        if(check(mid)) res = mid, lo = mid + 1;
        else hi = mid - 1;
    }
    cout << res << '\n';
}

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
  
    int TC = 1;
    cin >> TC;
    while (TC--) {
        testcase();
    }


    return 0;
}

/*

3
5
0 5 -2 1 2
9 -4 0 10 5 
-4 -1 4 -2 4
10 
-6 3 1 0 6 -2 -4 3 0 10
22 65 11 1 -34 -1 -39 -28 25 24
10 9 1 -2 -5 8 -7 -10 -7 -7
1
101
48763
651

1
1
101
48763
651

*/
