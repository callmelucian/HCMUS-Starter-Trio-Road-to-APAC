#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using tpl = tuple<int,int,int>;

#define all(v) begin(v), end(v)
#define sz(v) (int)v.size()
#define compact(v) v.erase(unique(all(v)), end(v))

template<class T> bool maximize (T &a, const T &b) { return b > a ? a = b, true : false; }
template<class T> bool minimize (T &a, const T &b) { return b < a ? a = b, true : false; }

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

const int MAX = 1e5 + 5;
int N, K, A[MAX];
mint pref[MAX], suff[MAX];

int add(int a, int b, int m){
    a += b;
    if(a >= m) a -= m;
    return a;
}

int subtract(int a, int b, int m){
    a -= b;
    if(a < 0) a += m;
    return a;
}

int mul(int a, int b, int m){
    return 1LL * a * b % m;
}

int binpow(int a, int b, int m){
    int c = 1;
    for(; b > 0; b /= 2, a = mul(a, a, m)){
        if(b & 1) c = mul(c, a, m);
    }
    return c;
}

mint getProd(int l, int r){
    // dbg(l, r);
    if(l <= r){
        if(l == 0) return pref[r];
        return pref[r] / pref[l - 1];
    } else{
        return suff[l] * pref[r];
    }
}

int phi(int n){
    int sum = n;
    for(int i = 2; i * i <= n; ++i){
        if(n % i == 0){
            sum -= sum / i;
            while(n % i == 0) n /= i;
        }
    }
    if(n > 1) sum -= sum / n;
    return sum;
}

void testcase(){
    cin >> N >> K;
    for(int i = 0; i < N; ++i){
        cin >> A[i];
        pref[i] = (i > 0 ? pref[i - 1] : 1) * A[i];
    }
    for(int i = N - 1; i >= 0; --i){
        suff[i] = (i + 1 < N ? suff[i + 1] : 1) * A[i];
    }    

    // for(int i = 0; i < N; ++i){
    //     cerr << pref[i] << " \n"[i == N - 1];
    // }
    
    // for(int i = 0; i < N; ++i){
    //     cerr << suff[i] << " \n"[i == N - 1];
    // }

    if(K <= 30 && (1 << K) <= N){
        for(int i = 0; i < N; ++i){
            cout << getProd(i, (i + ((1 << K) - 1)) % N) << ' ';
        }
        cout << '\n';
        return;
    } 

    int mod2 = phi(mod);
    for(int i = 0; i < N; ++i){
        int x = (i == 0 ? 0 : N - i);
        int y = subtract(binpow(2, K, N), x, N);
        mint base = (i == 0 ? 1 : suff[i]) * (y > 0 ? pref[y - 1] : 1);
        dbg(x, y);
        int target = subtract(binpow(2, K, mod - 1), (x + y) % (mod - 1), mod - 1);
        dbg(target);
        dbg(binpow(N, mod2, mod - 1));
        int k = mul(target, binpow(N, mod2, mod - 1), mod - 1);
        base *= mint(pref[N - 1]).power(k);
        dbg(k);
        cout << base << ' ';
    }
    cout << '\n';
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t = 1;
    // cin >> t;
    while(t--){
        testcase();
    }
    return 0;
}