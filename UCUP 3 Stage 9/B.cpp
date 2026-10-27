#include <bits/stdc++.h>
#define int long long
using namespace std;

#define all(v) begin(v), end(v)
#define compact(v) v.erase(unique(all(v)), end(v))
#define sz(v) (int)v.size()
#define MASK(x) (1LL<<(x))
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

#ifdef LOCAL
    #include "debug.hpp"
#else 
    #define dbg(...) ((void)0)
#endif //LOCAL

const int MOD = 1e9 + 7;

int add(int a, int b) {
    return (a += b) + (a >= MOD ? -MOD : a < 0 ? MOD : 0);
}

int f(int n, int x, int y, vector<int> &state) {
    if(n == 0) return x == 0;
    if(n == 1) return (x & y) == x;
    int p = 2;
    int result = 0;
    while(p * 2 <= n) p *= 2;
    int itr = upper_bound(state.begin(), state.end(), x / p) - state.begin() - 1;
    while(itr >= 0) {
        int mask = state[itr];
    // }
    // for(int mask = y; ; mask = (mask - 1) & y) {
        if(x >= mask * p) result = add(result, f(n - p, x - mask * p, y, state));
        if(x - mask * p > y * (n - p)) break;
        // if(mask == 0) break;
        itr--;
    }
    return result;
}

void testcase(){
    int n, x, y;
    cin >> n >> x >> y;
    vector<int> sos(y + 1, 0);
    for(int mask = y; ;mask = (mask - 1) & y) {
        vector<int> state;
        for(int i = mask; ; i = (i - 1) & mask){
            state.push_back(i);
            if(i == 0) break;
        } 
        reverse(state.begin(), state.end());
        sos[mask] = f(n, x, mask, state);
        // dbg(bitset<10>(mask), sos[mask]);
        if(mask == 0) break;
    }
    for(int i = 0; MASK(i) <= y; ++i) if(y & MASK(i)) {
        for(int mask = y; ; mask = (mask - 1) & y) {
            if(mask & MASK(i)) sos[mask] = add(sos[mask], -sos[mask ^ MASK(i)]);
            if(mask == 0) break;
        }
    }
    for(int mask = 0; mask <= y; ++mask) if((mask & y) == mask) cout << sos[mask] << ' ';
    cout << '\n';
}
int32_t main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t = 1;
    cin >> t;
    while(t--){
        testcase();
    }
    return 0;
}

/*

1
7 10 7

1
9 16 7

2
7 10 7
9 16 7

*/