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
#define size(v) (v).size()
#define pb push_back
#define eb emplace_back

using ll = long long;
using db = double;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using tpl = tuple<int,int,int>;

template<class T> bool minimize(T& a, const T& b){  return (a > b ? a = b, 1 : 0); }
template<class T> bool maximize(T& a, const T& b){  return (a < b ? a = b, 1 : 0); }

const int MX = 1005;
int n, m, peak = 0;
int ans[MX*5];
string a[MX];
int vist[MX][MX];
int vi[MX][MX];
int gay[MX][MX];

const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};
void dfs(int x, int y) {
    vist[x][y] = peak;
    for(int i = 0; i < 4; ++i) {
        int u = x + dx[i];
        int v = y + dy[i];
        if(u >= 1 && u <= n && v >= 1 && v <= m && !vist[u][v] && a[u][v] == '.') {
            dfs(u, v);
        }
    }
}   

void bfs(int x, int y, int fx, int fy) {
    dbg(x, y, fx, fy);
    vi[x][y] = 1;
    for(int i = 0; i <= n + 1; ++i) {
        for(int j = 0; j <= m + 1; ++j) {
            if(i < 1 || j < 1 || i > n || j > m || a[i][j] == 'O' ) {
                int le = i - fx;
                int lam = j - fy;
                if(le >= 1 && le <= n && lam >= 1 && lam <= m) {
                    dbg(gay[le][lam], le, lam, i, j, a[i][j]);
                    gay[le][lam] = 1;
                }
            }
        }
    }

    for(int i = 0 ; i < 4; ++i) {
        int u = x + dx[i];
        int v = y + dy[i];
        if(vist[u][v] == vist[x][y] && !vi[u][v]) {
            bfs(u, v, fx + dx[i], fy + dy[i]);
        }
    }
}

void testcase() {
    cin >> n >> m;
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= m; ++j) {
            vist[i][j] = 0;
        }
    }
    for(int i = 1; i <= n; ++i) {
        cin >> a[i];
        a[i] = ' ' + a[i];
    }
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= m; ++j) if(a[i][j] == '.' && !vist[i][j]) {
            ++peak;
            dfs(i, j); 
        }
    }

    for(int i = 1; i <= n; ++i) {
        for(int j =  1; j <= m; ++j) {
            // dbg(i, j, a[i][j], vist[i][j]);
        }
    }

    memset(ans, -1, sizeof ans);
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= m; ++j) {
            if(a[i][j] == '.' && ans[vist[i][j]] == -1) {

                for(int x = 1; x <= n; ++x){
                    for(int y = 1; y <= m; ++y) {
                        gay[x][y] = a[x][y] == 'O';
                        vi[x][y] = 0;
                    }
                }

                
                bfs(i, j, 0, 0);
                for(int i = 1; i <= n; ++i) {
                    for(int j = 1; j <= m; ++j) {
                        dbg(gay[i][j], i, j);
                    }
                }
                
                int cnt = 0;
                for(int x = 1; x <= n; ++x) {
                    for(int y = 1; y <= m; ++y) {
                        cnt += gay[x][y] == 0;
                    }
                }
                dbg(i, j, gay[i][j], cnt);
                if(cnt == 1) ans[vist[i][j]] = 1;
                else ans[vist[i][j]] = 0;
            }   
        }
    }

    int result = 0;
    for(int i = 1;  i <= n; ++i) {
        for(int j = 1; j <= m; ++j) {
            if(a[i][j] == '.') {
                result += ans[vist[i][j]];
            }
        }
    }
    cout << result << '\n';
}

int main() {
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

4
2 5
.OO..
O..O.
1 3
O.O
1 3
.O.
2 3
OOO
OOO

1
1 3
O.O

*/