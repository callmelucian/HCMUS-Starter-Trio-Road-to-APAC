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

const int MX = 1 << 20 | 7;
int n, k;
int a[MX];
int f[MX];
int ans[MX];

void testcase(){
    cin >> n >> k;
    n = 1 << n;
    for(int i = 1; i <= n; ++i) cin >> a[i];

    vector<int> order(n);
    for(int i = 1; i <= n; ++i) order[i - 1] = i;
    sort(order.begin(), order.end(), [](const int &i, const int &j) -> bool {
        return a[i] > a[j];
    });

    int smaller = n;
    for(int i: order) {
        int result = 0, pos = i;
        smaller--;
        if(i & 1) i++;
        for(int bit = 2, cur = 1; bit <= n; bit <<= 1, ++cur) {
            int inside = 0;
            for(int j = i; j; j -= -j & j) inside += f[j];
            for(int j = i - bit; j; j -= -j & j) inside -= f[j];    
            if(smaller >= bit - 1 && inside <= k) result = cur;
            else break;
            if(i & bit) i += bit;
        }
        for(int j = pos; j <= n; j += -j & j) f[j]++;
        ans[pos] = result;
    }
    for(int i = 1; i <= n; ++i) cout << ans[i] << ' ';
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

/*

2 1
1 2 3 4
*/