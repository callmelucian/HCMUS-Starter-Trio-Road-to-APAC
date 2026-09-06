#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
    #include "debug.hpp"
#else
    #define dbg(...) (void(0))
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

const int mod = 998244353;
struct mint{
    int v;
    mint(int _v = 0) : v(_v) {}
    mint& operator += (const mint& o){
        v += o.v;
        if(v >= mod) v -= mod;
        return *this;
    }
    mint& operator -= (const mint& o){
        v -= o.v;
        if(v < 0) v += mod;
        return *this;
    }
    mint& operator *= (const mint& o){
        v = 1LL * v * o.v % mod;
        return *this;
    }
    friend mint operator + (mint a, const mint& b){ return a += b; }
    friend mint operator - (mint a, const mint& b){ return a -= b; }
    friend mint operator * (mint a, const mint& b){ return a *= b; }
    friend istream& operator >> (istream& in, mint& o){ return in >> o.v; }
    friend ostream& operator << (ostream& out, const mint& o){ return out << o.v; }
};

void testcase(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; ++i) cin >> a[i];
    sort(all(a));
    vector<int> b = a;
    for(int i = 1; i < n; ++i) b[i] = max(b[i - 1] + 1, b[i]);
    vector<int> v = a;
    v.insert(end(v), all(b));
    sort(all(v));
    compact(v);
    vector<mint> dp(sz(v));
    mint ans = 0;
    for(int i = 0; i < n; ++i){
        vector<mint> nxt(sz(v));
        a[i] = lower_bound(all(v), a[i]) - begin(v);
        for(int last = 0; last < sz(v); ++last){
            if(last < a[i]){
                nxt[a[i]] += dp[last];
            } else if(last + 1 < sz(v)){
                nxt[last + 1] += dp[last];
            }
        }
        nxt[a[i]] += 1;
        for(int last = 0; last < sz(v); ++last){
            ans += mint(v[last]) * nxt[last];
            nxt[last] += dp[last];
        }
        dbg(nxt);
        swap(nxt, dp);
    }
    cout << ans << '\n';
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