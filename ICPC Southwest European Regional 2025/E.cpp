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

const int MX = 200005;
int n, q;
string s;
int f[MX];

void testcase(){
    cin >> n >> q;
    cin >> s;
    s = ' ' + s;
    for(int i = 1; i <= n; ++i) {
        f[i] = f[i - 1] + (s[i] == '8');
    }

    while(q--) {
        int l, r, x, y;
        cin >> l >> r >> x >> y;
        x = abs(x), y = abs(y);
        int c8 = f[r] - f[l - 1];
        int c4 = r - l + 1 - c8;
        if(max(x, y) <= c8) cout << "YES\n";
        else if(max(0, x - c8) + max(0, y - c8) <= c4) cout << "YES\n";
        else cout << "NO\n";
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

/*

10 6
4884884888
8 10 3 3
4 7 5 1
4 7 3-3
1 7-7-5
1 10 0 0
1 1 1 1

*/