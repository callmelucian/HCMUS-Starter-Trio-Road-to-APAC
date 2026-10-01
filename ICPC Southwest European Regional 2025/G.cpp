#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
    #include "debug.hpp"
#else
    #define dbg(...) ((void)0)
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

void testcase(){
    int N;
    cin >> N;
    vector<pair<int, int>> result;
    for(int k = 0; (1 << k) <= N; ++k){
        vector<pii> layer;
        for(int j = (1 << k); j < N; j += (1 << (k + 1))){
            layer.eb(j, (1 << k));
        }
        reverse(all(layer));
        // dbg(k, layer);
        if(layer.empty()) break;
        result.eb(layer.front().first, min(N - layer.front().first, (1 << k)));
        for(int j = 1; j < sz(layer); ++j){
            result.pb(layer[j]);
        }
    }
    
    cout << sz(result) << '\n';

    int last = 1e9;
    ll sumCost = 0;
    for(auto [x, y] : result){
        cout << x << ' ' << y << '\n';
        if(x <= last){
            sumCost += y;
        } else{
            sumCost += y + 1000;
        }
        last = x;
    }
    dbg(sumCost);
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