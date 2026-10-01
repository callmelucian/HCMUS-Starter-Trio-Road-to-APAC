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
    int N, K;
    cin >> N >> K;
    vector<int> cnt(4 * N + 1);
    for(int i = 0; i < N; ++i){
        int x; cin >> x;
        ++cnt[x];
    }

    int ans = 0;
    int last = 0, conseq = 0;
    for(int i = 1; i <= 4 * N; ++i){
        if(last == 0){
            if(cnt[i] > K){
                ++conseq;
                last = cnt[i] - 1;
                cnt[i] = 1;
            } 
        } else{
            if(cnt[i] + last > K){
                ++conseq;
                cnt[i] += last;
                last = cnt[i] - 1;
                cnt[i] = 1;
            } else{
                conseq = 0;
                last = 0;
            }
        }
        maximize(ans, conseq);
    }
    cout << ans << '\n';
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