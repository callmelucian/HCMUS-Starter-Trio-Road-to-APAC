#include <bits/stdc++.h>
using namespace std;

#define all(v) begin(v), end(v)
#define compact(v) v.erase(unique(all(v)), end(v))
#define sz(v) (int)v.size()
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

#ifdef LOCAL
    #include "debug.hpp"
#else 
    #define dbg(...) ((void)0)
#endif //LOCAL

using ull = unsigned long long;

vector<ull> factorize(ull n){
    vector<ull> num;
    for(ull i = 2; i * i <= n; ++i){
        if(n % i == 0){
            num.push_back(i);
            while(n % i == 0) n /= i;
        }
    }
    sort(all(num));
    if(n > 1) num.push_back(n);
    return num;
}

ull binpow(ull a, ull b, ull m){
    ull res = 1;
    for(; b > 0; b /= 2, a = 1ULL * a * a % m){
        if(b & 1) res = 1ULL * res * a % m;
    }
    return res;
}

ull primitiveRoot(ull p){
    if(p == 2) return 1;
    vector<ull> factors = factorize(p - 1);
    dbg(p);
    for(ull res = 2;; ++res){
        bool ok = true;
        for(ull factor : factors){
            if(binpow(res, (p - 1) / factor, p) == 1){
                ok = false;
                break;
            }
        }
        if(ok) return res;
    }
    return -1;
}


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

template<int root, int maxSize>
struct NTT{
    vector<mint> rt,out;
    vector<int> rev;
    int s, LG;
    NTT(){
        LG = 32 - __builtin_clz(maxSize - 1);
        s = 1 << LG;
        assert(s > 1);
        assert(LG <= __builtin_ctz(mod - 1));
        rt.assign(s, mint(0));
        rev.assign(s, 0);
        rt[0] = rt[1] = mint(1);
        for(int k = 2, t = 2; k < s; k <<= 1, ++t){
            mint z = mint(root).power((mod - 1) >> t);
            for(int i = k; i < 2 * k; ++i){
                rt[i] = (i & 1) ? rt[i >> 1] * z : rt[i >> 1];
            }
        }
        for(int i = 0; i < s; ++i){
            rev[i] = (rev[i >> 1] | ((i & 1) << LG)) >> 1;
        }
    }

    void ntt(vector<mint>& a){
        int n = sz(a);
        assert((n & (n - 1)) == 0);
        assert(n <= s);
        int shift = __builtin_clz(n) - __builtin_clz(s);
        for(int i = 0; i < n; ++i){
            int j = rev[i] >> shift;
            if(i < j) swap(a[i], a[j]);
        }
        for(int k = 1; k < n; k <<= 1){
            for(int i = 0; i < n; i += 2 * k){
                for(int j = 0; j < k; ++j){
                    mint u = rt[j + k] * a[i + j + k];
                    mint v = a[i + j];
                    tie(a[i + j], a[i + j + k]) = make_pair(v + u, v - u);
                }
            }
        }
    }
    vector<mint> conv(vector<mint> a, vector<mint> b){
        if(a.empty() || b.empty()) return {};
        int need = sz(a) + sz(b) - 1;
        int n = 1;
        while(n < need) n <<= 1;
        assert(n <= s);
        a.resize(n); b.resize(n);
        out.assign(n, mint(0));
        ntt(a); ntt(b);
        mint invN = mint(n).inv();
        for(int i = 0; i < n; ++i){
            out[-i & (n - 1)] = a[i] * b[i] * invN;
        }
        ntt(out);
        out.resize(need);
        return out;
    }
    vector<mint> convCyclic(const vector<mint>& a, const vector<mint>& b, int n){
        vector<mint> c = conv(a, b);
        for(int i = n; i < sz(c); ++i) c[i - n] += c[i];
        c.resize(n);
        return c;
    }
};

void trim (vector<int> &a) {
    while (a.size() && !a.back()) a.pop_back();
}

vector<int> div2 (const vector<int> &a) {
    vector<int> res;
    int carry = 0;
    for (int i = (int)a.size() - 1; i >= 0; i--) {
        carry *= 10, carry += a[i];
        res.push_back(carry / 2);
        carry %= 2;
    }
    reverse(all(res)), trim(res);
    return res;
}

vector<int> convert (vector<int> a) {
    vector<int> res;
    trim(a);
    while (a.size()) {
        res.push_back(a[0] & 1);
        a = div2(a);
    }
    return res;
}

NTT<3, (int)1e4 + 10> nttInst;

void testcase(){
    // {
    //     int K, P, X;
    //     cin >> K >> P >> X;
    //     int pk = 1, ans = 0;
    //     for(int i = 0; i < K; ++i) pk *= P;
    //     vector<vector<int>> comb(pk, vector<int>(pk));
    //     for(int a = 0; a < pk; ++a){
    //         comb[a][0] = 1;
    //         for(int b = 1; b <= a; ++b){
    //             comb[a][b] = comb[a - 1][b - 1] + comb[a - 1][b];
    //             comb[a][b] %= P;
    //         }

    //         for(int b = 0; b <= a; ++b){
    //             if(comb[a][b] == X){
    //                 ++ans;
    //             }
    //         }
    //     }
    //     cout << ans << '\n';
    //     exit(0);
    // }

    string K; int P, X;
    cin >> K >> P >> X;

    // vector<int> bin = convert(digits);
    // {
    //     ll num = 0, pw = 1;
    //     for(auto d : bin){
    //         num += pw * d;
    //         pw *= 2;
    //     }
    //     dbg(num);
    // }


    int G = primitiveRoot(P);
    vector<int> q(P, -1);
    dbg(G);
    for(int pw = 0, s = 1; pw < (P - 1); ++pw, s = 1LL * s * G % P){
        q[s] = pw;
        // dbg(s, pw);
    }
    for(int i = 1; i < P; ++i) assert(q[i] != -1);

    vector<vector<int>> comb(P, vector<int>(P));
    vector<mint> poly(P - 1);
    for(int a = 0; a < P; ++a){
        comb[a][0] = 1;
        for(int b = 1; b <= a; ++b){
            comb[a][b] = comb[a - 1][b - 1] + comb[a - 1][b];
            if(comb[a][b] >= P) comb[a][b] -= P;
        }        

        for(int b = 0; b <= a; ++b){
            int num = q[comb[a][b]];
            // dbg(a, b, comb[a][b]);
            poly[num] += 1;
        }
    }

    vector<mint> ans = {1};
    reverse(all(K));
    for(auto b : K){
        b -= '0';
        if(b == 1){
            ans = nttInst.convCyclic(ans, poly, P - 1);
        }
        poly = nttInst.convCyclic(poly, poly, P - 1);
    }
    
    // dbg(poly);
    int pos = q[X];
    cout << ans[pos] << '\n';
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