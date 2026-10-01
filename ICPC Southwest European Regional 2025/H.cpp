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

void testcase(){

}

const int MX = 5005;
bitset<MX> f[MX];
bitset<MX> vist[MX];

bool dwuy(int n, int m, int k) {
    if(vist[n][k]) return f[n][k];
    vist[n][k] = 1;
    if(k != m && n - m <= 0) return f[n][k] = 1;
    else if(k == m && n - m + 1 <= 0) return f[n][k] = 1;
    for(int i = 1; i <= min(n, m); ++i) if(i != k) {
        if(dwuy(n - i, m, i) == 0) return f[n][k] = 1;
    }
    return f[n][k] = 0;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);

    for(int m = 1; m <= 300; m += 2) {
        vector<int> primes;
        for(int i = 2, j = m + 1; i <= j; ++i) {
            while(j % i == 0) primes.push_back(i), j /= i;
        }        
        // dbg(primes, bitset<16>(m + 1));
        int pre = 0;
        for(int i = 0; i < MX; ++i) f[i] = vist[i] = 0;
        int cnt = 20;
        string s = "";
        for(int n = 1; n <= 5000; ++n) {
            if(!dwuy(n, m, 0)) {
                s += n - pre - (m + 1) ? 'X' : '_';
                // dbg(n, m, n - pre - (m + 1)),
                pre = n, --cnt;
            }
            if(cnt == 0) break;
        }
        dbg(s, m, bitset<15>(m + 1), primes);
    }
    
    
    return 0;
    
    int tests = 1;
    // cin >> tests;
    while(tests--){
        testcase();
    }
    return 0;  
}