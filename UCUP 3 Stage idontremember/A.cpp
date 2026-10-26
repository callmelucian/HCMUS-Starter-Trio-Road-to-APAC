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

template<int MOD>
struct mint{
    static const int mod = MOD;
    int v;
    mint(int _v = 0) : v(_v) {refine();}

    void refine() {
        if (abs(v) >= mod) v %= mod;
        if (v < 0) v += mod;
    }

    mint& operator+= (const mint& o){
        v += o.v;
        if(v >= mod) v -= mod;
        return *this;
    }
    mint& operator-= (const mint& o){
        v -= o.v;
        if(v < 0) v += mod;
        return *this;
    }
    mint& operator*= (const mint& o){
        v = 1LL * v * o.v % mod;
        return *this;
    }
    mint& operator/= (const mint &o) {
        return operator*=(o);
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

    bool operator== (const mint &o) const { return v == o.v; }

    friend mint operator+ (mint a, const mint& b){ return a += b; }
    friend mint operator- (mint a, const mint& b){ return a -= b; }
    friend mint operator* (mint a, const mint& b){ return a *= b; }
    friend mint operator/ (mint a, const mint& b){ return a /= b; }
    friend ostream& operator<< (ostream& op, const mint& o){ return op << o.v; }
    friend istream& operator>> (istream &i, mint& m) { return i >> m.v, m.refine(), i; }
};

template<int MOD>
struct Item {
    mint<MOD> v;
    int len;

    Item() : v(0), len(0) {}
    Item (mint<MOD> a, int b) : v(a), len(b) {}
};

template<int BASE, int MOD>
struct SMT {
    vector<mint<MOD>> lazy, basePow, fullOne;
    vector<Item<MOD>> tr;
    int n;

    Item<MOD> combine (const Item<MOD> &a, const Item<MOD> &b) {
        return Item<MOD>(a.v + basePow[a.len] * b.v, a.len + b.len);
    }

    SMT (int sz) : lazy(sz << 2), basePow(sz + 1), fullOne(sz + 1), tr(sz << 2), n(sz) {
        basePow[0] = fullOne[0] = 1;
        for (int i = 1; i <= n; i++) basePow[i] = basePow[i - 1] * BASE;
        // for (int i = 1; i <= n; i++) fullOne[i] += fullOne[i - 1];
        partial_sum(all(basePow), fullOne.begin());
    }

    void build (int k, int l, int r, const vector<int> &a) {
        if (l == r) return tr[k] = Item(mint<MOD>(a[l]), 1), void();
        int mid = (l + r) >> 1;
        build(k << 1, l, mid, a);
        build(k << 1 | 1, mid + 1, r, a);
        tr[k] = combine(tr[k << 1], tr[k << 1 | 1]);
        dbg(k, tr[k].v, tr[k].len);
    }

    void build (const vector<int> &a) { build(1, 1, n, a); }

    void apply (int k, mint<MOD> incr, int l, int r) {
        lazy[k] += incr, tr[k].v += incr * fullOne[r - l];
    }

    void pushDown (int k, int l, int r, int mid) {
        if (!lazy[k].v) return;
        apply(k << 1, lazy[k], l, mid);
        apply(k << 1 | 1, lazy[k], mid + 1, r);
        lazy[k] = 0;
    }

    void update (int a, int b, mint<MOD> incr, int k, int l, int r) {
        if (b < l || r < a) return;
        if (a <= l && r <= b) return apply(k, incr, l, r), void();
        int mid = (l + r) >> 1;
        pushDown(k, l, r, mid);
        update(a, b, incr, k << 1, l, mid);
        update(a, b, incr, k << 1 | 1, mid + 1, r);
        tr[k] = combine(tr[k << 1], tr[k << 1 | 1]);
    }

    void update (int a, int b, mint<MOD> incr) {
        update(a, b, incr, 1, 1, n);
    }

    Item<MOD> query (int a, int b, int k, int l, int r) {
        if (b < l || r < a) return Item<MOD>();
        if (a <= l && r <= b) return tr[k];
        int mid = (l + r) >> 1;
        pushDown(k, l, r, mid);
        return combine(query(a, b, k << 1, l, mid), query(a, b, k << 1 | 1, mid + 1, r));
    }

    mint<MOD> query (int a, int b) { 
        // assert(query(a, b, 1, 1, n).len == b - a + 1);
        return query(a, b, 1, 1, n).v;
    }
};

const int BASE1 = 21121;
const int BASE2 = 1e5 + 19;

const int MOD1 = 1e9 + 7;
const int MOD2 = 998'244'353;

void testcase(){
    int N, Q, K, B; cin >> N >> Q >> K >> B;
    vector<int> A(N + 1), C(N + 1);
    for (int i = 1; i <= N; i++)
        cin >> A[i], C[N - i + 1] = A[i];
    for (int i = 1, curr = K + B; i <= N; i++, curr += K) C[i] += curr;

    SMT<BASE1, MOD1> a1(N), b1(N);
    SMT<BASE2, MOD2> a2(N), b2(N);

    dbg(A, C);

    a1.build(A), b1.build(C);
    a2.build(A), b2.build(C);

    auto check = [&] (int pos, int rad) {
        int l = pos - rad, r = pos - 1, u = pos + 1, v = pos + rad;
        dbg("compare", l, r, u, v);
        l = N - l + 1, r = N - r + 1, swap(l, r);
        mint<MOD1> uv1 = a1.query(u, v), lr1 = b1.query(l, r) - (b1.fullOne[r - l] * mint<MOD1>(l - 1) * mint<MOD1>(K));
        mint<MOD2> uv2 = a2.query(u, v), lr2 = b2.query(l, r) - (b2.fullOne[r - l] * mint<MOD2>(l - 1) * mint<MOD2>(K));
        dbg(uv1, lr1, uv2, lr2);
        return uv1 == lr1 && uv2 == lr2;
    };

    for (int i = 0; i < Q; i++) {
        int type; cin >> type;
        if (type == 1) {
            int l, r, v; cin >> l >> r >> v;
            // for R-trees
            a1.update(l, r, mint<MOD1>(v));
            a2.update(l, r, mint<MOD2>(v));
            // for L-trees
            l = N - l + 1, r = N - r + 1, swap(l, r);
            b1.update(l, r, mint<MOD1>(v));
            b2.update(l, r, mint<MOD2>(v));
        }
        else {
            dbg(A, C);
            int p; cin >> p;
            int ans = 0;
            for (int mask = 1 << 17; mask; mask >>= 1)
                if ((mask | ans) <= min(p - 1, N - p) && check(p, ans | mask)) ans |= mask;
            cout << ans << "\n";
        }
    }
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

/*
6 6 6 2
1 5 9 10 15 18
2 2
1 3 3 -3
2 2
1 3 4 3
2 3
2 4
*/