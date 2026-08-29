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
using db = double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#ifdef LOCAL 
    #include "debug.hpp"
#else 
    #define dbg(...) ((36))
#endif //LOCAL

const int MAX = 50005;
bitset<MAX> icpc;
bitset<MAX> full;
bitset<MAX> dwuy[MAX];

void testcase(){
    int n, m;
    cin >> n >> m;
    vector<int> a(n + 5, 0);
    vector<int> b(n + 5, 0);
    for(int i = 1; i <= n; ++i) full[i] = 1;
    for(int i = 1; i <= n; ++i) cin >> a[i];
    for(int i = 1; i <= n; ++i) b[a[i]] = i;
    for(int i = 1; i <= n; ++i) {
        if(i > 1) icpc[b[i - 1]] = 1;
        dbg(icpc);
        dwuy[b[i]] = (icpc << (n - b[i])) | (full >> b[i]);
    }
    dbg();
    icpc = full;
    long long ans = 0;
    for(int i = 1; i <= n; ++i) dbg(dwuy[i]);
    for(int i = 2; i <= n; ++i) {
        icpc &= dwuy[i];
        ans += (icpc >> (n - i + m)).count();
    }
    cout << ans;
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
/*
5 2
3 1 4 2 5

10 2
1 3 2 4 5 7 6 8 9 10
*/