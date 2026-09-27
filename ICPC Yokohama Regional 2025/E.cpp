#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
    #include "debug.hpp"
#else
    #define dbg(...) (void(0))
#endif

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
using db = double;

#define int long long

const int LIM = 100;
const long long OO = 1e18;

int cnt(int a, int b, int c, double mid) {
    if(OO * mid < (db)a) return OO;
    if(OO * mid < (db)b) return OO;
    if(OO * mid < (db)c) return OO;
    int x = a / mid;
    int y = b / mid;
    int z = c / mid;
    if(x == 0 || y == 0 || z == 0) return 0;
    ll re = OO;
    re /= x;
    re /= y;
    re /= z;
    if(re > 0) return x * y * z;
    return OO;
}

void testcase() {
    int a, b, c, k;
    cin >> a >> b >> c >> k;
    
    if(a > b) swap(a, b);
    if(a > c) swap(a, c);
    if(b > c) swap(b, c);
    
    double res = 0;
    for(double lo = 0, hi = a, t = 0; t < 100; ++t) {
        double mid = (lo + hi) / 2;
        if(cnt(a, b, c, mid) >= k) res = mid, lo = mid;
        else hi = mid;
    }

    dbg(res);

    int A = a / res;
    int B = b / res;
    int C = c / res;

    pair<double, pair<int, int>> ans = {0, {0, 0}};
    for(int delta = -LIM; delta <= LIM; ++delta) if(A + delta > 0){
        double mid = 1.0 * a / (A + delta); 
        if(cnt(a, b, c, mid) >= k) ans = max(ans, {mid, {a, A + delta}});
    }
    for(int delta = -LIM; delta <= LIM; ++delta) if(B + delta > 0){
        double mid = 1.0 * b / (B + delta); 
        if(cnt(a, b, c, mid) >= k) ans = max(ans, {mid, {b, B + delta}});
    }
    for(int delta = -LIM; delta <= LIM; ++delta) if(C + delta > 0){
        double mid = 1.0 * c / (C + delta); 
        if(cnt(a, b, c, mid) >= k) ans = max(ans, {mid, {c, C + delta}});
    }   
    dbg(ans.first);
    dbg(ans.second);

    auto [p, q] = ans.second;
    dbg(p, q);
    int x = gcd(p, q);
    cout << p / x << ' ' << q / x << '\n';
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