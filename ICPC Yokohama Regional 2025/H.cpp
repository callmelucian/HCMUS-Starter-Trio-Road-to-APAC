#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
    #include "debug.hpp"
#else if
    #define dbg(...) (void(0))
#endif

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
using db = double;

const int MX = 1005;
int n, m, k;
char a[MX][MX];

bool check(int x, int y, int u, int v) {
    int cnt = 0;
    for(int i = x; i <= u; ++i) {
        for(int j = y; j <= v; ++j) {
            if(a[i][j] == '#') ++cnt;
        }   
    }
    if(cnt == max(u - x + 1, v - y + 1)) {
        for(int i = x; i <= u; ++i) {
            for(int j = y; j <= v; ++j) {
                bool sameA = i == x && j == y;
                bool sameB = i == u && j == v;
                if(!sameA && !sameB) a[i][j] = '.';
            }   
        }   
        return true;
    }
    return false;
}

void testcase(){
    cin >> n >> m >> k; k--;
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= m; ++j) {
            cin >> a[i][j];
        }
    }
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= m; ++j) {
            if(a[i][j] == '#') {
                if(i + k > n || j + k > m) {
                    cout << "no\n";
                    return;
                }
                int cnt = 0;
                cnt += check(i, j, i + k, j);
                cnt += check(i, j, i, j + k);
                cnt += check(i + k, j, i + k, j + k);
                cnt += check(i, j + k, i + k, j + k);
                if(cnt != 3) {
                    cout << "no\n";
                    return;
                }
                a[i][j] = a[i + k][j] = a[i][j + k] = a[i + k][j + k] = '.';
            }
        }
    }
    dbg(n, m, k);
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= m; ++j) {
            if(a[i][j] == '#') {
                cout << "no\n";
                return;
            }
        }
    }
    cout << "yes\n";
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

/*

1
10 10 5
..........
..........
....#####.
..#.#.#.#.
..#.#.#.#.
..#.#.#.#.
..#.#.#.#.
..#####...
..........
..........


*/