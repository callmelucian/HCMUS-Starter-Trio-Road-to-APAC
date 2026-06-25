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

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using tpl = tuple<int,int,int>;

template<class T> bool minimize(T& a, const T& b){  return (a > b ? a = b, 1 : 0); }
template<class T> bool maximize(T& a, const T& b){  return (a < b ? a = b, 1 : 0); }

const ll inf = LLONG_MAX;

#define ls (s << 1)
#define rs (s << 1 | 1)
struct SegTreeAnd{
    vector<ll> st, lz;
    SegTreeAnd(int n) : st(n << 2), lz(n << 2, inf) {}
    
    void build(int s, int l, int r, vector<ll>& A){
        if(l == r) st[s] = A[l];
        else{
            int mid = l + r >> 1;
            build(ls, l, mid, A);
            build(rs, mid + 1, r, A);
            st[s] = st[ls] & st[rs];
        }
        dbg(s, l, r, st[s]);
    }

    void apply(int s, ll val){
        st[s] &= val;
        lz[s] &= val;
    }

    void pushDown(int s){
        if(lz[s] != inf){
            apply(ls, lz[s]);
            apply(rs, lz[s]);
            lz[s] = inf;
        }
    }

    void applyRange(int s, int l, int r, int u, int v, ll val){
        if(u <= l && r <= v) apply(s, val);
        else{
            int mid = l + r >> 1;
            pushDown(s);
            if(u <= mid) applyRange(ls, l, mid, u, v, val);
            if(mid < v)  applyRange(rs, mid + 1, r, u, v, val);
            st[s] = st[ls] & st[rs];
        }
    }

    void modify(int s, int l, int r, int pos, ll val){
        if(l == r) st[s] = val;
        else{
            int mid = l + r >> 1;
            pushDown(s);
            if(pos <= mid) modify(ls, l, mid, pos, val);
            else modify(rs, mid + 1, r, pos, val);
            st[s] = st[ls] & st[rs];
        }
    }

    ll query(int s, int l, int r, int u, int v){
        if(u > v || v < l || u > r) return inf;
        if(u <= l && r <= v) return st[s];
        int mid = l + r >> 1;
        pushDown(s);
        return query(ls, l, mid, u, v) & query(rs, mid + 1, r, u, v);
    }   

    void debug(int s, int l, int r){
        if(l == r) cerr << st[s] << ' ';
        else{
            int mid = l + r >> 1;
            pushDown(s);
            debug(ls, l, mid);
            debug(rs, mid + 1, r);
        }
    }
};

struct Info{
    ll uniqueMask, badMask;
};  

void refine(Info& res){
    res.uniqueMask &= (inf ^ res.badMask);
}

Info comb(Info a, Info b){
    ll dup = a.uniqueMask & b.uniqueMask;
    Info res;
    res.badMask = a.badMask | b.badMask | dup;
    res.uniqueMask = (a.uniqueMask ^ b.uniqueMask);
    // dbg(res.uniqueMask);
    refine(res);
    return res;
}

struct SegTreeOr{
    vector<ll> st, lz;
    vector<Info> dat;
    SegTreeOr(int n) : st(n << 2), lz(n << 2), dat(n << 2, Info{0, 0}) {}

    void build(int s, int l, int r, vector<ll>& A){
        if(l == r){
            st[s] = A[l];
            dat[s].uniqueMask = A[l];
            dat[s].badMask = 0;
        } else{
            int mid = l + r >> 1;
            build(ls, l, mid, A);
            build(rs, mid + 1, r, A);
            st[s] = st[ls] | st[rs];
            dat[s] = comb(dat[ls], dat[rs]);
        }
        dbg(s, l, r, st[s], dat[s].uniqueMask, dat[s].badMask);
    }    

    void apply(int s, int l, int r, ll val){
        st[s] |= val;
        lz[s] |= val;
        if(l == r){
            dat[s].uniqueMask |= val;
            refine(dat[s]);
        } else{
            dat[s].badMask |= val;
            refine(dat[s]);
        }
    }

    void pushDown(int s, int l, int r, int mid){
        dbg(s, l, r, mid);
        if(lz[s] != 0){
            apply(ls, l, mid, lz[s]);
            apply(rs, mid + 1, r, lz[s]);
            lz[s] = 0;
        }
    }

    void applyRange(int s, int l, int r, int u, int v, ll val){
        if(u <= l && r <= v) apply(s, l, r, val);
        else{
            int mid = l + r >> 1;
            pushDown(s, l, r, mid);
            if(u <= mid) applyRange(ls, l, mid, u, v, val);
            if(mid < v)  applyRange(rs, mid + 1, r, u, v, val);
            st[s] = st[ls] | st[rs];
            dat[s] = comb(dat[ls], dat[rs]);
        }
    }

    void modify(int s, int l, int r, int pos, ll val){
        dbg(s, l, r, pos, val);
        if(l == r){
            st[s] = val;
            dat[s] = Info{val, 0};
        } else{
            int mid = l + r >> 1;
            pushDown(s, l, r, mid);
            if(pos <= mid) modify(ls, l, mid, pos, val);
            else modify(rs, mid + 1, r, pos, val);
            st[s] = st[ls] | st[rs];
            dat[s] = comb(dat[ls], dat[rs]);
        }
        dbg(s, l, r, dat[s].uniqueMask, dat[s].badMask);
    }

    Info queryInfo(int s, int l, int r, int u, int v){
        if(v < l || u > r) return Info{0, 0};
        if(u <= l && r <= v) return dat[s];
        int mid = l + r >> 1;
        pushDown(s, l, r, mid);
        return comb(queryInfo(ls, l, mid, u, v), queryInfo(rs, mid + 1, r, u, v));
    }

    int walk(int s, int l, int r, int u, int v, ll highest){
        dbg(s, l, r, highest, st[s]);
        if(v < l || u > r || ((st[s] & highest) == 0)) return -1;
        if(l == r) return l;
        int mid = l + r >> 1;
        pushDown(s, l, r, mid);
        int d = walk(ls, l, mid, u, v, highest);
        if(d == -1) d = walk(rs, mid + 1, r, u, v, highest);
        return d;
    }

    void debug(int s, int l, int r){
        dbg(s, l, r, dat[s].uniqueMask, dat[s].badMask);
        if(l < r){
            int mid = l + r >> 1;
            pushDown(s, l, r, mid);
            debug(ls, l, mid);
            debug(rs, mid + 1, r);
        }
    }
};

void testcase() {
    int N, Q;
    cin >> N >> Q;
    vector<ll> A(N), B(N);
    for(int i = 0; i < N; ++i){
        cin >> A[i];
        B[i] = inf ^ A[i];
    }
    SegTreeAnd andTree(N);
    SegTreeOr orTree(N);
    dbg(A, B);
    andTree.build(1, 0, N - 1, A);
    orTree.build(1, 0, N - 1, B);

    while(Q--){
        int t;
        cin >> t;
        dbg(t);
        if(t == 1){
            int l, r; ll v;
            cin >> l >> r >> v;
            --l, --r;
            andTree.applyRange(1, 0, N - 1, l, r, v);
            orTree.applyRange(1, 0, N - 1, l, r, v ^ inf);
        } else if(t == 2){
            int i; ll v;
            cin >> i >> v;
            --i;
            andTree.modify(1, 0, N - 1, i, v);
            orTree.modify(1, 0, N - 1, i, inf ^ v);
        } else{
            int l, r;
            cin >> l >> r;
            --l, --r;

            Info qt = orTree.queryInfo(1, 0, N - 1, l, r);
            dbg(qt.uniqueMask, qt.badMask);
            if(qt.uniqueMask == 0){
                cout << andTree.query(1, 0, N - 1, l, r) << '\n';
                continue;
            }

            int x = 63 - __builtin_clzll(qt.uniqueMask);
            dbg(x, 1LL << x);
            ll highest = 1LL << x;
            int pos = orTree.walk(1, 0, N - 1, l, r, highest);
            dbg(pos);
            ll ans = inf;
            if(l < pos) ans &= (andTree.query(1, 0, N - 1, l, pos - 1));
            if(pos < r) ans &= (andTree.query(1, 0, N - 1, pos + 1, r));
            cout << ans << '\n';
        }
        // andTree.debug(1, 0, N - 1);
        // cerr << '\n';
        // orTree.debug(1, 0, N - 1);
        // cerr << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
  
    // Info a{3 ^ inf, 0}, b{8 ^ inf, 0}, d{7 ^ inf, 0};
    // Info c = comb(a, b);
    // c = comb(c, d);
    // cout << c.uniqueMask << ' ' << c.badMask << '\n';
    // cout << bitset<7>(c.uniqueMask) << ' ' << bitset<7>(c.badMask) << '\n';
    // return 0;

    int TC = 1;
    while (TC--) {
        testcase();
    }

    return 0;
}