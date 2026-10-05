#include <bits/stdc++.h>
using namespace std;

#define all(v) begin(v), end(v)
#define compact(v) v.erase(unique(all(v)), end(v))
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

#define double long double

void testcase(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(int &x: a) cin >> x;

    int center = 0;
    while(a[center] > a[center + 1]) ++center;

    double res = 0;
    for(double lo = 0, hi = 1e9, cnt = 200; cnt > 0; --cnt) {
        double mid = (lo + hi) / 2;
        double maxLeft = a[center - 1] - mid;
        double maxRight = a[center] + a[center + 1] - 2 * mid;
        double cur = maxLeft;
        for(int i = center - 2; i >= 0; --i) {
            cur += a[i] - mid;
            maxLeft = max(maxLeft, cur);    
        }
        cur = maxRight;
        for(int i = center + 2; i < n; ++i) {
            cur += a[i] - mid;
            maxRight = max(maxRight, cur);
        }
        if(maxLeft + maxRight >= 0) res = mid, lo = mid;
        else hi = mid;
    }
    cout << setprecision(15) << fixed << res << '\n';
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