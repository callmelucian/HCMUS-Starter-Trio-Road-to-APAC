#include <bits/stdc++.h>
using namespace std;

#define all(v) begin(v), end(v)
#define compact(v) v.erase(unique(all(v)), end(v))
#define sz(v) (int)v.size()
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

#ifdef LOCAL
    #include "debug.hpp"
#else 
    #define dbg(...) ((void)0)
#endif //LOCAL

void trim (vector<int> &a) {
    while (a.size() && !a.back()) a.pop_back();
}

vector<int> div2 (const vector<int> &a) {
    vector<int> res;
    int carry = 0;
    for (int i = (int)a.size() - 1; i >= 0; i--) {
        carry *= 10, carry += a[i];
        res.push_back(carry / 2);
        carry %= 2;
    }
    reverse(all(res)), trim(res);
    return res;
}

vector<int> convert (vector<int> a) {
    vector<int> res;
    trim(a);
    while (a.size()) {
        res.push_back(a[0] & 1);
        a = div2(a);
    }
    return res;
}

void testcase(){
    vector<int> vec = {1, 2, 3, 4};
    vector<int> v = convert(vec);
    int ans = 0;
    for (int i = 0; i < v.size(); i++)
        ans += (1 << i) * v[i];
    dbg(ans);
}
int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t = 1;
    // cin >> t;
    while(t--){
        testcase();
    }
    return 0;
}