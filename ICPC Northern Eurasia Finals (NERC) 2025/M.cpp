#include <bits/stdc++.h>
using namespace std;

#define all(v) begin(v), end(v)
#define sz(v) (int)v.size()
#define compact(v) v.erase(unique(all(v)), end(v))
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
template<class T> bool minimize(T& a, const T& b){ return a > b ? a = b, 1 : 0; }
template<class T> bool maximize(T& a, const T& b){ return a < b ? a = b, 1 : 0; }

#ifdef LOCAL
    #include "debug.hpp"
#else 
    #define dbg(...) ((void)0)
#endif //LOCAL

const int MX = 1000005;
string s, t;
int f[MX][2];

void testcase(){
    cin >> s >> t;
    int n = s.size();
    s = ' ' + s;
    t = ' ' + t;
    for(int i = 0; i <= n; ++i) f[i][0] = f[i][1] = 1e9;
    f[0][0] = 0;
    for(int i = 1; i <= n; ++i) {
        if(s[i] == '0') {
            if(t[i] == '0') {
                f[i][0] = min(f[i - 1][0], f[i - 1][1] + 1);
                f[i][1] = min(f[i - 1][1] + 1, f[i - 1][0] + 2);
            }
            else {
                f[i][0] = min(f[i - 1][0] + 1, f[i - 1][1] + 2);
                f[i][1] = min(f[i - 1][1], f[i - 1][0] + 1);
            }
        }
        else {
            if(t[i] == '0') {
                f[i][0] = min(f[i - 1][0] + 1, f[i - 1][1]);
                f[i][1] = min(f[i - 1][1] + 2, f[i - 1][0] + 1);
            }
            else {
                f[i][0] = min(f[i - 1][0] + 2, f[i - 1][1] + 1);
                f[i][1] = min(f[i - 1][1] + 1, f[i - 1][0]);
            }
        }
    }
    cout << min(f[n][0], f[n][1]) << '\n';
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