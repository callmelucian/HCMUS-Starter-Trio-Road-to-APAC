#include <bits/stdc++.h>
using namespace std;

#define all(v) begin(v), end(v)
#define compact(v) v.erase(unique(all(v)), end(v))
using ll = long long;
using pii = pair<int, int>;

#ifdef LOCAL
    #include "debug.hpp"
#else 
    #define dbg(...) ((void)0)
#endif //LOCAL

const int LIM = (1 << 19);
void testcase(){
    int N;
    cin >> N;
    vector<int> A(N);
    vector<int> cnt(LIM), sum(LIM);
    for(int i = 0; i < N; ++i){
        cin >> A[i];
    }

    for(int i = 0; i < N; ++i){
        vector<pii> costs;
        for(int j = 1; j <= 18; ++j){
            //keep the highest j bits
            int mask = (A[i] >> (18 - j));
            int cur = 18 - j;
            for(int k = 0; k < 17; ++k){
                if(mask >= LIM) break;
                costs.emplace_back(mask, cur);
                ++cur;
                mask = mask * 2 + 1;
            }
        }

        sort(all(costs));
        int lastMask = -1;
        for(int i = 0; i < size(costs); ++i){
            auto [mask, cost] = costs[i];
            if(lastMask != mask){
                ++cnt[mask];
                sum[mask] += cost;
            }

            lastMask = mask;
        }
    }
    ll ans = 1e18;
    for(int i = 0; i < LIM; ++i){
        if(cnt[i] == N){
            ans = min(ans, (ll)sum[i]);
        }
    }
    cout << ans << '\n';
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