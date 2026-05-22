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
#define size(v) (v).size()
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

const int MAX = 1e5 + 5;

int N;
ll A[MAX];

#define ls (s << 1)
#define rs (s << 1 | 1)
struct LazySegTree{
    vector<ll> st, lazy;
    LazySegTree(int n) : st(n << 2), lazy(n << 2, -1) {}
    void apply(int s, int l, int r, ll val){
        st[s] = val * (r - l + 1);
        lazy[s] = val;
    }
    void push(int s, int l, int r, int mid){
        if(lazy[s] != -1){
            apply(ls, l, mid, lazy[s]);
            apply(rs, mid + 1, r, lazy[s]);
            lazy[s] = -1;
        }
    }
    void update(int s, int l, int r, int u, int v, ll val){
        if(u <= l && r <= v) apply(s, l, r, val);
        else{
            int mid = l + r >> 1;
            push(s, l, r, mid);
            if(u <= mid) update(ls, l, mid, u, v, val);
            if(mid < v)  update(rs, mid + 1, r, u, v, val);
            st[s] = st[ls] + st[rs];
        }
    }
    ll query(int s, int l, int r, int u, int v){
        if(v < l || u > r) return 0;
        if(u <= l && r <= v) return st[s];
        int mid = l + r >> 1;
        push(s, l, r, mid);
        return query(ls, l, mid, u, v) + query(rs, mid + 1, r, u, v);
    }
};

struct SegTree{
    vector<ll> mx;
    SegTree(int n) : mx(n << 2) {}
    void build(int s, int l, int r){
        if(l == r) mx[s] = A[l];
        else{
            int mid = l + r >> 1;
            build(ls, l, mid);
            build(rs, mid + 1, r);
            mx[s] = max(mx[ls], mx[rs]);
        }
    }
    ll query(int s, int l, int r, int u, int v){
        if(v < l || u > r) return 0;
        if(u <= l && r <= v) return mx[s];
        int mid = l + r >> 1;
        return max(query(ls, l, mid, u, v), query(rs, mid + 1, r, u, v));
    }
    void update(int s, int l, int r, int pos, ll val){
        if(l == r) mx[s] = val;
        else{
            int mid = l + r >> 1;
            if(pos <= mid) update(ls, l, mid, pos, val);
            else update(rs, mid + 1, r, pos, val);
            mx[s] = max(mx[ls], mx[rs]);
        }
    }

    int findLast(int _, int __, int ___, int u, int v, ll val){
        int last = -1;
        while(u <= v){
            int mid = u + v >> 1;
            if(query(1, 1, N, u, mid) <= val) last = mid, u = mid + 1;
            else v = mid - 1;
        }
        assert(last != -1);
        return last;
    }
};

struct FuncTree{
    int siz;
    vector<ll> value;
    SegTree f;
    LazySegTree s;
    FuncTree(int n) : siz(n), value(n + 1), f(n), s(n) {}

    void build(){
        f.build(1, 1, siz);
        for(int i = 1; i <= siz; ++i) value[i] = A[i];
        for(int i = 1; i <= siz; ){
            int j = f.findLast(1, 1, siz, i, siz, A[i]);
            s.update(1, 1, siz, i, j, value[i]);
            i = j + 1;
        }
    }   

    void add(int i, ll v){
        dbg(i, v);
        value[i] += v;
        f.update(1, 1, siz, i, value[i]);
        ll fv = f.query(1, 1, siz, 1, i);
        if(fv == value[i]){
            int j = f.findLast(1, 1, siz, i, siz, value[i]);
            dbg(i, j, value[i]);
            s.update(1, 1, siz, i, j, value[i]);
        }
    }

    ll querySum(int l, int r){
        if(l > r) return 0;
        return s.query(1, 1, siz, l, r);
    }
};

void testcase() {
    cin >> N;
    int pos = 1;
    ll sumTot = 0;
    for(int i = 1; i <= N; ++i){
        cin >> A[i];
        sumTot += A[i];
        if(A[pos] < A[i]) pos = i;
    }    
    FuncTree pref(N), suff(N);
    pref.build();
    reverse(A + 1, A + 1 + N);
    suff.build();
    reverse(A + 1, A + 1 + N);

    int Q;
    cin >> Q;
    while(Q--){
        int i, v;
        cin >> i >> v;
        pref.add(i, v);
        suff.add(N - i + 1, v);
        sumTot += v;
        A[i] += v;
        if(A[pos] < A[i]) pos = i;

        ll x = pref.querySum(1, pos);
        ll y = suff.querySum(1, N - pos);
        dbg(pos, x, y, sumTot);
        cout << x + y - sumTot << '\n';
    }
    for(int i = 1; i <= N; ++i){
        A[i] = 0;
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