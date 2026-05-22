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

using ll = long long;
using db = double;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using tpl = tuple<int,int,int>;

template<class T> bool minimize(T& a, const T& b){  return (a > b ? a = b, 1 : 0); }
template<class T> bool maximize(T& a, const T& b){  return (a < b ? a = b, 1 : 0); }

const int MX = 100005;
int n;
string s;
int a[MX];
vector<int> G[MX];

int ans[MX];
int result[MX];
multiset<int> f[MX];
multiset<int, greater<int>> mf[MX];

void dfs(int u) {
    if(G[u].size() == 0) {
        if(a[u] == 0) f[u].insert(1);
        else mf[u].insert(1);
        f[u].insert(0);
    }
    else{
        int fern = G[u][0];
        dfs(fern);
        ans[u] = ans[fern];
        swap(f[u], f[fern]);
        swap(mf[u], mf[fern]);

        for(int v: G[u]) if(v != fern) {
            dfs(v);
            // dbg(v);
            // dbg(f[v]);
            // dbg(mf[v]);

            if(f[u].size() + mf[u].size() > f[v].size() + mf[v].size()) {
                swap(f[u], f[v]);
                swap(mf[u], mf[v]);
                swap(ans[u], ans[v]);
                
            }
            
            vector<int> vt;
            auto iu = mf[u].size() ? mf[u].begin() : f[u].begin();
            auto iv = mf[v].size() ? mf[v].begin() : f[v].begin();
            int result = 2e9;
            int tu = mf[u].size() ? -1 : 1;
            int tv = mf[v].size() ? -1 : 1;
            int sumu = 0;
            int sumv = 0;
            for(int x: mf[u]) sumu += x;
            for(int x: mf[v]) sumv += x;
            while(iu != f[u].end()) {
                if(tu == 1) sumu += *iu;
                if(tv == 1) sumv += *iv;
                vt.push_back(sumu  + sumv);
                result = min(result, vt.back());
                if(tu == -1) sumu -= *iu;
                if(tv == -1) sumv -= *iv;
                iu++, iv++;
                if(iu == mf[u].end()) iu = f[u].begin(), tu = 1;
                if(iv == mf[v].end()) iv = f[v].begin(), tv = 1;
            }
            
            dbg(u, v, vt);
            
            ans[u] += ans[v] + result;
            bool flag = 1;
            multiset<int> g;
            multiset<int, greater<int>> mg;
            for(int x: vt) {
                if(x == result) flag = 0;
                
                    if(flag) mg.insert(x - result);
                    else g.insert(x - result);
                
            }
            f[u] = g;
            mf[u] = mg;
            dbg(u, ans[u], mf[u], f[u]);

        }
        
        if(a[u] == 0) {
            f[u].insert(1);
        }
        else {
            mf[u].insert(1);
        }
        
    }
    result[u] = ans[u];
    dbg(u, ans[u]);
    dbg(mf[u]);
    dbg(f[u]);
}

void testcase() {
    cin >> n;
    cin >> s; 
    for(int i = 1; i <= n; ++i) a[i] = s[i - 1] - '0';
    for(int i = 2; i <= n; ++i) {
        int p; cin >> p;
        G[p].push_back(i);
    }

    dfs(1);
    for(int i = 1; i <= n; ++i) cout << result[i] << ' '; cout << '\n';

    for(int i = 1; i <= n; ++i) {
        ans[i] = result[i] = 0;
        f[i].clear();
        mf[i].clear();
        G[i].clear();
    }
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
1
16
0110100101011001
1 1 2 2 3 3 5 5 5 6 8 8 9 11 11


1
6
110101
1 2 3 4 4

2
9
101011110
1 1 3 3 3 6 2 2
4
1011
1 1 3

1
4
1011
1 1 3

1
9
101011110
1 1 3 3 3 6 2 2

*/