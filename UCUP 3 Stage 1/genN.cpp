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

mt19937 rng(113231);
int randint(int l, int r){
    return uniform_int_distribution<int>(l, r)(rng);
}

int ceilLog(int n){
    int k = 0;
    while((1 << k) < n) ++k;
    return k;
}

vector<vector<int>> ans;
void testcase(){
    ofstream op("N.in");
    int n = randint(3, 10), m = n + ceilLog(n) + 3;
    for(int i = 0; i < n; ++i){
        for(int j = i + 1; j < n; ++j){
            ans[i][j] = ans[j][i] = randint(0, 1);
        }
    }
    ans = vector<vector<int>>(n, vector<int>(n));
    
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            output << ans[i][j];
        }
    }
}

int main(){
    while(true){
        gen();

    }
    return 0;
}