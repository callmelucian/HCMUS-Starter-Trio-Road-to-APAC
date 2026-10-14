#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MASK(x) (1LL << (x))
#define all(v) begin(v), end(v)
#define compact(v) v.erase(unique(all(v)), end(v))
using ll = long long;
using pii = pair<int, int>;

template<class T> bool minimize(T& a, const T& b){ return b < a ? a = b, true : false; }
template<class T> bool maximize(T& a, const T& b){ return b > a ? a = b, true : false; }

#ifdef LOCAL
    #include "debug.hpp"
#else 
    #define dbg(...) ((void)0)
#endif //LOCAL

const int MX = 100005;
int C, Cx, n;
int a[MX];

int cost(int x) {
    if(x <= 1) return 1;
    return __lg(x - 1) + 2;
}

int solve1() {
    int ans = 0;
    for(int i = Cx, cur = 0; i >= 1; --i) {
        cur += a[i];
        ans += cost(cur);
    }
    for(int i = Cx + 1, cur = 0; i <= n; ++i) {
        cur += a[i];
        ans += cost(cur);
    }
    cout << ans;
    return ans;
}

int f[MX], g[MX];
int pf[MX], sf[MX], offset[MX];

void solve2() {
    priority_queue<pii, vector<pii>, greater<pii>> Q;
    for(int i = 1, cur = 0; i < n; ++i) {
        cur += a[i];
        f[i] = f[i - 1] + cost(a[i]);
        while(Q.size() && Q.top().first < cur) {
            auto [w, j] = Q.top();
            Q.pop();
            f[i] -= cost(pf[j]);
            pf[j] += cur - offset[j];
            f[i] += cost(pf[j]);
            offset[j] = cur;
            Q.push({MASK(__lg(pf[j] - 1) + 1) - pf[j] + cur, j});
        }
        offset[i] = cur;
        pf[i] = a[i];
        Q.push({MASK(__lg(pf[i] - 1) + 1) - pf[i] + cur, i});
    }

    // for(int i = 1; i < n; ++i) dbg(f[i], i);

    while(Q.size()) Q.pop();
    for(int i = n, cur = 0; i > 1; --i) {
        cur += a[i];
        g[i] = g[i + 1] + cost(a[i]);
        while(Q.size() && Q.top().first < cur) {
            auto [w, j] = Q.top();
            Q.pop();
            g[i] -= cost(sf[j]);
            sf[j] += cur - offset[j];
            g[i] += cost(sf[j]);
            offset[j] = cur;
            Q.push({MASK(__lg(sf[j] - 1) + 1) - sf[j] + cur, j});
        }
        offset[i] = cur;
        sf[i] = a[i];
        Q.push({MASK(__lg(sf[i] - 1) + 1) - sf[i] + cur, i});
    }
    // for(int i = 2; i <= n; ++i) dbg(g[i], i);

    pii ans = {2e18, -1};
    for(int i = 1; i < n; ++i) {
        ans = min(ans, {f[i] + g[i + 1], i});
        Cx = i;
    }
    cout << ans.second;
}

void testcase(){
    cin >> C;
    cin >> n;
    for(int i = 1; i <= n; ++i) cin >> a[i];
    if(C == 1) cin >> Cx;

    switch (C) {
        case 1:
            solve1();
            break;
        case 2:
            solve2();
            break;
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

/*

1
4
1 3 1 3
2

*/