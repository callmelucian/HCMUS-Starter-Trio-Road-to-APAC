#include <bits/stdc++.h>
using namespace std;

#define all(v) begin(v), end(v)
#define compact(v) v.erase(unique(all(v)), end(v))
using ll = long long;
using pii = pair<int, int>;

template<class T> bool minimize(T& a, const T& b){ return b < a ? a = b, true : false; }
template<class T> bool maximize(T& a, const T& b){ return b > a ? a = b, true : false; }

#ifdef LOCAL
    #include "debug.hpp"
#else 
    #define dbg(...) ((void)0)
#endif //LOCAL

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
    mint power(ll n) const {
        mint res(1), bs = *this;
        for(; n > 0; n /= 2, bs *= bs){
            if(n & 1) res *= bs;
        }
        return res;
    }
    mint inv() const {
        return power(mod - 2);
    }
    mint& operator /= (const mint& o){
        return *this *= o.inv();
    }
    friend mint operator + (mint a, const mint& b){ return a += b; }
    friend mint operator - (mint a, const mint& b){ return a -= b; }
    friend mint operator * (mint a, const mint& b){ return a *= b; }
    friend mint operator / (mint a, const mint& b){ return a /= b; }
    friend ostream& operator << (ostream& op, const mint& o){ return op << o.v; }
};

const int MX = 100005;
mint f[MX];

void brute(){
    ll factorial = 1;
    for(int n = 2; n < 6; ++n){
        factorial *= n;
        vector<int> p(n);
        iota(all(p), 1);
        ll sumSec = 0, sumThird = 0;
        map<vector<int>, int> cnt;
        do{
            vector<int> q = p;
            int ans = 0;
            for(int i = 0; i < n; ++i){
                for(int j = 0; j < n; ++j){
                    if(q[i] < q[j]){
                        swap(q[i], q[j]);
                        ++ans;
                    }
                }
            }
            q = p;
            int sec = 0, third = 0;
            for(int i = 0; i < 1; ++i){
                for(int j = 0; j < n; ++j){
                    if(q[i] < q[j]){
                        swap(q[i], q[j]);
                        ++sec;
                    }
                }
            }
            vector<int> bef = q;
            for(int i = 0; i < n; ++i){
                for(int j = i + 1; j < n; ++j){
                    third += q[i] > q[j];
                }
            }
            // dbg(p, ans, sec);
            // assert(ans == sec);
            sumSec += sec;
            sumThird += third;
            dbg(bef);
            ++cnt[bef];
        } while(next_permutation(all(p)));
        // dbg(n, sumSec, sumThird);
        for(auto [p, c] : cnt){
            int u = 0;
            #define sz(v) (int)v.size()
            int mx = 0;
            for(int j = 1; j < sz(p); ++j){
                u += mx < p[j];
                mx = max(mx, p[j]);
            }
            dbg(p, c, u);
        }
    }
}

void testcase(){
    
    int N;
    cin >> N;
    // mint n = N;
    // cout << f[N - 1] + (n - 1) * (1 / n) + n * ((n - 1) / n) << '\n';

    // mint cur = 0;
    // vector<mint> cost(N + 1), fact(N + 1);
    // fact[0] = 1;
    // for(int i = 1; i <= N; ++i) fact[i] = fact[i - 1] * mint(i);
    // cost[1] = 0;
    // for(int i = 2; i <= N; ++i){
    //     for(int j = 1; j < i; ++j){
    //         cost[i] += cost[j - 1] + fact[i - j].inv();
    //     }
    // }

    // mint ans = cost[N] + f[N - 1] + (N - 1);
    // dbg(cost[N], f[N - 1] + N - 1);
    // cout << ans << '\n';

    mint ans = 0;
    for(int i = 2; i <= N; ++i) ans += mint(1) / mint(i);
    // dbg(N, ans, f[N - 1] + N - 1, (ans + f[N - 1] + N - 1) * N);

    cout << ans * 2 + f[N] << endl;

    /*
    
    14 / 

    1/2 + 2 = 5/2

    5/6 + 14/6

    */
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    for(int i = 2; i < MX; ++i) {
        f[i] = f[i - 1] + mint(i - 1) / mint(2);
    }
    

    brute();
    int tests = 1;
    cin >> tests;
    while(tests--){
        testcase();
    }
    return 0;
}

/*

F(1) = (n - 1)!
F(2) = n! - (n - 1)!
F(3) = n! 

*/