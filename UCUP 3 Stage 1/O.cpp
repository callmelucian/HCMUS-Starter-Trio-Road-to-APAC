#include <bits/stdc++.h>
using namespace std;

#define all(v) begin(v), end(v)
#define rall(v) rbegin(v), rend(v)
#define sz(v) (int)v.size()
#define pb push_back
#define eb emplace_back
#define compact(v) v.erase(unique(all(v)), end(v))
template<class T> bool minimize(T& a, const T& b){ return a > b ? a = b, 1 : 0; }
template<class T> bool maximize(T& a, const T& b){ return a < b ? a = b, 1 : 0; }
using ll = long long;
using db = double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#ifdef LOCAL 
    #include "debug.hpp"
#else 
    #define dbg(...) ((36))
#endif //LOCAL

using ld = long double;
using pld = pair<ld, ld>;

pld operator + (pld a, pld b){
    return make_pair(a.first + b.first, a.second + b.second);
}
pld operator * (ld x, pld a){
    return make_pair(x * a.first, x * a.second);
} 
void testcase(){
    ld A, B, x1, xn; int n;
    cin >> A >> B >> n >> x1 >> xn;
    vector<pld> f(n);
    f[0] = {1, 0};
    f[1] = {0, 1};
    for(int i = 2; i < n; ++i){
        f[i] = B * f[i - 2] + A * f[i - 1];
    }

    double x2 = (xn - x1 * f[n - 1].first) / f[n - 1].second;

    vector<ld> x(n);
    x[0] = x1;
    x[1] = x2;
    for(int i = 2; i < n; ++i){
        x[i] = B * x[i - 2] + A * x[i - 1];
    }
    cout << fixed << setprecision(10);
    for(int i = 0; i < n; ++i){
        cout << x[i] << "\n";
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int tests = 1;
    // cin >> tests;
    while(tests--){
        testcase();
    }
    return 0;
}