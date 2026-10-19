#include <bits/stdc++.h>
using namespace std;

#define all(v) begin(v), end(v)
#define sz(v) (int)v.size()
#define compact(v) v.erase(unique(all(v)), end(v))
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
template<class T> bool minimize(T& a, const T& b){ return a > b ? a = b, 1 : 0; }
template<class T> bool maximize(T& a, const T& b){ return a < b ? a = b, 1 : 0; }

#ifdef LOCAL
    #include "debug.hpp"
#else 
    #define dbg(...) ((void)0)
#endif //LOCAL

const int MX = 100005;
int n, L[MX], R[MX];

void testcase(){
    cin >> n;
    for(int i = 1; i <= n; ++i) cin >> L[i] >> R[i];
    vector<pii> vt;
    for(int i = 1; i <= n; ++i) {
        vt.push_back({L[i], i});
        vt.push_back({R[i], -i});
    }
    map<int, int> mp;
    sort(vt.begin(), vt.end());
    vt.insert(vt.begin(), {-1, -1});
    for(size_t i = 1; i < vt.size(); ++i) mp[vt[i].first] = i;
    
    int ans = -1;
    bool goRight = false;
    for(int i = vt.size() / 2 + 1; i < (int)vt.size(); ++i) if(vt[i].second > 0) goRight = true;
    if(goRight) {
        for(int i = vt.size() / 2 + 1; i < (int)vt.size(); ++i) ans += vt[i].first * 2;
        int mx = 0;
        for(int i = 1; i <= (int)vt.size() / 2; ++i) {
            if(vt[i].second < 0) mx = vt[i].first;
            ans -= vt[i].first * 2; 
        }
        ans += mx;
    }
    else {
        for(int i = 1; i < (int)vt.size() / 2; ++i) ans -= vt[i].first * 2;
        int mn = -1;
        for(int i = vt.size() / 2 + 1; i < (int)vt.size(); ++i) {
            if(vt[i].second < 0 && mn == -1) mn = -vt[i].first;
            ans += vt[i].first * 2;
        }
        ans += mn;
    }
    cout << ans << '\n';
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t = 1;
    cin >> t;
    while(t--){
        testcase();
    }
    return 0;
}