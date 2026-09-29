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
using pii = pair<int, int>;
using pll = pair<ll, ll>;

#ifdef LOCAL 
    #include "debug.hpp"
#else
    #define dbg(...) (void(0))
#endif //LOCAL

#define int long long
#define MASK(x) (1LL<<(x))
void testcase(){
    int n, a, b;
    cin >> n >> a >> b;
    if(a != b) {
        cout << "NO\n";
        return;
    }
    bool pre = 0;
    bool needOr = 0;
    for(int i = 0; MASK(i) <= n; ++i) {
        if(!(n & MASK(i + 1)) && (n & MASK(i)) && !pre) {
            needOr = 1;
        }
        pre = n & MASK(i);
    }

    if(!needOr) cout << "YES\n";
    else {
        bool pre = 0;
        bool onlyBall = 0;
        for(int i = 0; MASK(i) <= n; ++i) {
            if((n & MASK(i + 1)) && !(n & MASK(i)) && pre) {
                onlyBall = 1;
            }
            pre = n & MASK(i);
        }   
        if(onlyBall) cout << "NO\n";
        else cout << "YES\n";
    }
}

int32_t main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int tests = 1;
    // cin >> tests;
    while(tests--){
        testcase();
    }
    return 0;
}