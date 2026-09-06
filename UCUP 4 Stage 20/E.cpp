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

void testcase(){
    int N;
    cin >> N;
    string S;
    cin >> S;
    string ans = "";
    auto check = [&](){
        int i = 0, j = 0;
        while(i < sz(ans) || j < sz(ans)){
            
        }
    };
    for(int len = 1; len <= N; ++len){
        ans += char('a');
        int l = 0, r = 25, chosen = -1;
        while(l <= r){
            int mid = l + r >> 1;
            ans.back() = char('a' + mid);
            if(check()){
                chosen = mid;
                r = mid - 1;
            } else l = mid + 1;
        }
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