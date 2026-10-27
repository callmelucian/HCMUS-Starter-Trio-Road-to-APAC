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

ll C(ll n){
    return 1LL * n * (n - 1);
}

void testcase(){
    ll n;
    cin >> n;
    vector<pair<ll, int>> divs;
    for(ll i = 2; i * i <= n; ++i){
        if(n % i == 0){
            int cnt = 0;
            while(n % i == 0){
                n /= i;
                ++cnt;
            }

            divs.emplace_back(i, cnt);
        }
    }
    if(n > 1) divs.emplace_back(n, 1);
    

    vector<pair<ll, ll>> nums; //[x, d(x)];
    nums.emplace_back(1, 1);
    for(auto [p, k] : divs){
        vector<pair<ll, ll>> newNums = nums;
        ll s = p;
        for(int j = 1; j <= k; ++j, s *= p){
            for(auto [x, dx] : nums){
                newNums.emplace_back(x * s, dx * (j + 1));
            }
        }
        swap(nums, newNums);
    }

    sort(all(nums));
    dbg(nums);
    ll ans = 0;
    for(auto [x, dx] : nums){
        vector<int> q(sz(divs));
        ll y = x, ways = 1;
        for(int j = 0; j < sz(divs); ++j){
            while(y % divs[j].first == 0){
                ++q[j];
                y /= divs[j].first;
            }
            if(q[j] == 0){
                ways *= (divs[j].second + 1);
            }
        }
        ans += ways;
        dbg(x, ways);
    }
    ans /= 2;
    ++ans;
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