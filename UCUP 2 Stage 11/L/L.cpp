#include <bits/stdc++.h>
#ifdef LOCAL
    #include "../debug.hpp"
#else 
    #define dbg(...)
#endif // LOCAL

using namespace std;

#define all(v) begin(v), end(v)
#define rall(v) rbegin(v), rend(v)
#define compact(v) v.erase(unique(all(v)), end(v))
#define sz(v) (v).size()
#define pb push_back
#define eb emplace_back
#define int long long

using ll = long long;
using db = double;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using tpl = tuple<int,int,int>;

template<class T> bool minimize(T& a, const T& b){  return (a > b ? a = b, 1 : 0); }
template<class T> bool maximize(T& a, const T& b){  return (a < b ? a = b, 1 : 0); }

const int MX = 200005;
int n, k;
int g[3][MX];

void upd(int &sum, int &cnt) {
    if(sum == 1) sum = 0, ++cnt;
}

void squirtle(int &cnt, int &w1) {
    int d = min(cnt, w1);
    cnt -= d;
    w1 -= d;
}

void charmander(int &sum, int &cnt, int &w2) {
    int d = min(sum/2, w2);
    sum -= 2 * d;
    w2 -= d;
    upd(sum, cnt);
}

void bulbasaur(int &sum, int &cnt, int &w1) {
    int d = min(sum, w1);
    sum -= d;
    w1 -= d;
    upd(sum, cnt);
}

void testcase() {
    cin >> n >> k;
    vector<int> vt;
    for(int i = 1; i <= n; ++i){
        int c, w, f;
        cin >> c >> w >> f;
        g[w][f] += c;
        vt.push_back(f);
    }
    sort(vt.begin(), vt.end());
    compact(vt);
    reverse(vt.begin(), vt.end());

    int cnt = 0, sum = 0, ans = 0;
    for(int i: vt) {
        int w1 = g[1][i];
        int w2 = g[2][i];
        dbg(w1, w2);
        squirtle(cnt, w1);
        charmander(sum, cnt, w2);
        bulbasaur(sum, cnt, w1);

        if(w2 > 0) {
            int d = k / 2; // const 
            int e = w2 / d;  // dynamic 
            ans += i * (e + !!(w2 % d));
            if(k & 1) cnt += d;
            if(w2 % d) sum = k - 2 * (w2 % d);
            upd(sum, cnt);
        }

        if(w1 > 0) {
            squirtle(cnt, w1);
            bulbasaur(sum, cnt, w1);
        }

        if(w1 > 0) {
            int d = w1 / k;
            ans += i * d;
            if(w1 % k) {
                ans += i;
                sum = k - (w1 % k);
            }
            upd(sum, cnt);
        }

        dbg(i, ans, sum, cnt);
    }
    cout << ans << '\n';

    for(int i: vt) g[1][i] = g[2][i] = 0;
}

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
  
    int tests = 1;
    cin >> tests;
    while(tests--){
        testcase();
    }
    return 0;
}

/*

2
2 10
4 2 100
3 1 100
2 10
4 2 100
1 1 100

1
4 6
1 1 8
7 2 5
1 1 7
3 2 6

2
4 6
1 1 8
7 2 5
1 1 7
3 2 6
8 1200000
100000 1 100000
100000 1 12345
100000 2 100000
100000 2 12345
100000 1 100000
100000 1 12345
100000 2 100000
100000 2 12345

*/