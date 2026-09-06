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

const int OFFSET = 1e4 + 5e3 + 1;

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

struct PrefixSum{
    vector<mint> pref;
    PrefixSum(vector<mint>& a) : pref(a) {
        for(int i = 1; i < sz(pref); ++i){
            pref[i] += pref[i - 1];
        }
    }
    mint query(int l, int r){
        if(l > r) return 0;
        return pref[r] - (l > 0 ? pref[l - 1] : 0);
    }
};


void brute(int N, int M){
    vector<mint> dp((1 << N) * M + 1, 0);
    int siz = sz(dp);
    dp[0] = 1;
    for(int i = 1; i <= N; ++i){
        int coef = (1 << i) - 1;
        vector<mint> nxt(siz);
        for(int j = coef; j <= M * coef; j += coef){
            // dbg(j);
            for(int k = j; k < siz; ++k){
                nxt[k] += dp[k - j];
            }
        }
        swap(nxt, dp);
        // for(int j = 0; j < siz; ++j) if(dp[j].v){
        //     dbg(i, j, dp[j]);
        // }
    }

    mint ans = 0, pref = 0;
    for(int i = 0; i < siz; ++i){
        // dbg(i, dp[i]);
        pref += dp[i];
        ans += pref * dp[i];
    }
    dbg(ans);
}

void testcase(){
    int N, M;
    cin >> N >> M;
    if(N == 1){
        mint ans = 0;
        for(int i = 1; i <= M; ++i){
            ans += mint(i);
        }
        cout << ans << '\n';
        return;
    }
    int OFFSET = M * 2;
    vector<mint> dp(OFFSET * 2);
    dp[OFFSET] = 1;
    
    auto trans = [&](){
        PrefixSum ds(dp);
        vector<mint> nxt(OFFSET * 2);
        for(int i = 0; i < 2 * OFFSET; ++i){
            nxt[i] = ds.query(max(0, i - M), i - 1);
        }
        ds = PrefixSum(nxt);
        for(int i = 0; i < 2 * OFFSET - 1; ++i){
            dp[i] = ds.query(i + 1, min(2 * OFFSET - 1, i + M));
        }
    };

    auto divi = [&](){
        vector<mint> nxt(2 * OFFSET);
        for(int v = -OFFSET; v < OFFSET; ++v){
            int go = (v < 0 ? (v - 1) / 2 : v / 2);
            nxt[go + OFFSET] += dp[v + OFFSET];
        }
        swap(nxt, dp);
    };

    trans();
    for(int i = 2; i <= N; ++i){
        divi();
        trans();
    }
    mint ans = 0;
    for(int v = OFFSET; v < 2 * OFFSET; ++v) ans += dp[v];
    cout << ans << '\n';
    brute(N, M);
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