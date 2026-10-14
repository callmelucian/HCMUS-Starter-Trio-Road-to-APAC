#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MASK(x) (1LL << (x))
#define all(v) begin(v), end(v)
#define compact(v) v.erase(unique(all(v)), end(v))
using ll = long long;
using pii = pair<int, int>;

template<class T> bool minimize(T& a, const T& b){ return b < a ? a = b, true : false; }
template<class T> bool maximize(T& a, const T& b){ return b > a ? a = b, true : false; }

#ifdef LOCAL
    #include "debug.hpp"
#else 
    #define dbg(...) ((void)0)
#endif //LOCAL

pii solve(int n, int k) {
    int x = n - 1;
    while(k > (MASK(n - x) - 1) * (MASK(n - x) - 1)) --x;
    k -= (MASK(n - x - 1) - 1) * (MASK(n - x - 1) - 1);
    int row = 0, col = 0;
    int lim = MASK(n - x) - 1;
    for(int lo = 1, hi = lim; lo <= hi;) {
        int mid = (lo + hi) >> 1;
        int cnt = mid * (MASK(n - x) - 1) - (mid / 2) * (MASK(n - x - 1) - 1);
        if(cnt < k) row = mid, lo = mid + 1;
        else hi = mid - 1;
    }
    k -= row * (MASK(n - x) - 1) - (row / 2) * (MASK(n - x - 1) - 1);
    ++row;
    // dbg(k);
    for(int lo = 1, hi = lim; lo <= hi;) {
        int mid = (lo + hi) >> 1;
        int cnt = mid;
        if(row % 2 == 0) cnt -= mid / 2;
        if(cnt >= k) col = mid, hi = mid - 1;
        else lo = mid + 1;
    }
    // dbg(x, row, col);

    pii ans = {MASK(x) * row, MASK(x) * col};

    return ans;
}


void testcase(){
    int n, k;
    cin >> n >> k;
    pii res = solve(n, k);    
    cout << res.first << ' ' << res.second << '\n';
    // n = 4;
    // for(int k = 1; k <= 225; ++k) {
    //     dbg(n, k, res);
        
    // }
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