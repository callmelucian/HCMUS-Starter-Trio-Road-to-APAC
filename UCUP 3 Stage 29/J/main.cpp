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

const int MAX = 5e5 + 5;

#define ls (s << 1)
#define rs (s << 1 | 1)
struct SegTree{
    vector<int> st;
    SegTree(int n) : st(n << 2) {}
    
    void down(int s, int l, int r, int mid){
        if(st[s] != -1){
            st[ls] = st[s];
            st[rs] = st[s];
            st[s] = -1;
        }
    }

    void update(int s, int l, int r, int u, int v, int val){
        if(u <= l && r <= v) st[s] = val;
        else{
            int mid = l + r >> 1;
            down(s, l, r, mid);
            if(u <= mid) update(ls, l, mid, u, v, val);
            if(mid < v)  update(rs, mid + 1, r, u, v, val);
        }
    }

    int query(int s, int l, int r, int pos){
        if(l == r) return st[s];
        int mid = l + r >> 1;
        down(s, l, r, mid);
        if(pos <= mid) return query(ls, l, mid, pos);
        else return query(rs, mid + 1, r, pos);
    }
};

struct Rectangle{
    int xl, xr, yl, yr;
} rect[MAX];

struct FenwickTree{
    int offset = 0;
    vector<int> bit;
    FenwickTree(int n, int offset) : offset(offset), bit(n + 10, 0) {}
    void update(int i, int v){
        dbg(i, v);
        i += offset;
        for(; i < sz(bit); i += i & (-i)) bit[i] += v;
    }
    int query(int i){
        int sum = 0;
        i += offset;
        for(; i > 0; i -= i & (-i)) sum += bit[i];
        return sum;
    }
    int query(int l, int r){
        return query(r) - query(l - 1);
    }
    void update(int l, int r, int v){
        if(l > r) swap(l, r);
        dbg(l, r, v);
        update(l, v);
        update(r + 1, -v);
    }
} ftSum(0, 0), ftCnt(0, 0); 
int N, Q, parent[MAX], siz[MAX], head[MAX], dep[MAX], lift[22][MAX], chosen[MAX];
int tin[MAX], tout[MAX], timerDfs;
vector<int> adj[MAX];

void dfs(int u){
    siz[u] = 1;
    for(auto v : adj[u]){
        dep[v] = dep[u] + 1;
        lift[0][v] = u;
        for(int i = 1; (1 << i) <= dep[v]; ++i){
            lift[i][v] = lift[i - 1][lift[i - 1][v]];
        }
        dfs(v);
        if(siz[v] > siz[chosen[u]]) chosen[u] = v;
        siz[u] += siz[v];
    }
}

void dfsHLD(int u, int hd){
    tin[u] = ++timerDfs;
    head[u] = hd;
    dbg(u, hd, chosen[u]);
    if(chosen[u] == 0){
        // return;
    } else{
        dfsHLD(chosen[u], hd);
        for(auto v : adj[u]) if(v != chosen[u]){
            dfsHLD(v, v);
        }
    }
    tout[u] = timerDfs;
}

bool inside(int u, int v){
    return tin[u] <= tin[v] && tout[v] <= tout[u];
}

void updateChain(int u, int v, int det){
    dbg(u, v, det);
    if(dep[u] > dep[v]) swap(u, v);
    ftSum.update(dep[u], dep[v], det);
}

void testcase() {
    cin >> N >> Q;
    vector<tuple<int, int, int>> events;
    vector<int> coord;
    for(int i = 1; i <= N; ++i){
        cin >> rect[i].xl >> rect[i].yl >> rect[i].xr >> rect[i].yr;
        coord.emplace_back(rect[i].yl);
        coord.emplace_back(rect[i].yr);
        events.emplace_back(rect[i].xl, i, -1);
        events.emplace_back(rect[i].xr, i, +1);
    }
    sort(all(coord)); compact(coord);
    sort(all(events));
    for(int i = 1; i <= N; ++i){
        rect[i].yl = lower_bound(all(coord), rect[i].yl) - begin(coord);
        rect[i].yr = lower_bound(all(coord), rect[i].yr) - begin(coord);
    }

    SegTree T(sz(coord));
    vector<int> roots;

    for(auto [x, id, type] : events){
        if(type == -1){
            int par = T.query(1, 0, sz(coord) - 1, rect[id].yl);
            if(par < 1){
                roots.emplace_back(id);
            } else{
                parent[id] = par;
            }
            T.update(1, 0, sz(coord) - 1, rect[id].yl, rect[id].yr, id);
        } else{
            T.update(1, 0, sz(coord) - 1, rect[id].yl, rect[id].yr, parent[id]);
        }
    }

    for(int i = 1; i <= N; ++i) if(parent[i] > 0){
        adj[parent[i]].emplace_back(i);
    }
    for(auto r : roots){
        dfs(r);
        dfsHLD(r, r);
    }

    for(int i = 1; i <= N; ++i) dbg(i, parent[i], tin[i], tout[i]);

    ftCnt = FenwickTree(N, 0);
    ftSum = FenwickTree(N, 1);
    vector<int> A(N + 1);
    while(Q--){
        char tp; int u; 
        cin >> tp >> u;
        if(tp == '^'){
            A[u] ^= 1;
            if(A[u] == 1){
                int base = u;
                if(ftCnt.query(tin[u], tout[u]) == 0){
                    int low = u;
                    for(int i = 19; i >= 0; --i){
                        int p = lift[i][u];
                        // dbg(p, u, i);
                        if(dep[u] >= (1 << i) && ftCnt.query(tin[p], tout[p]) == 0){
                            dbg(p, tin[p], tout[p], ftCnt.query(tin[p], tout[p]));
                            u = p;
                        }
                    }
                    updateChain(low, u, +1);
                }
                dbg(tin[base]);
                ftCnt.update(tin[base], +1);
            } else{
                ftCnt.update(tin[u], -1);
                if(ftCnt.query(tin[u], tout[u]) == 0){
                    int low = u;
                    for(int i = 19; i >= 0; --i){
                        int p = lift[i][u];
                        if(dep[u] >= (1 << i) && ftCnt.query(tin[p], tout[p]) == 0){
                            u = p;
                        }
                    }
                    updateChain(low, u, -1);
                }
            }
        } else{
            cout << ftSum.query(u) << '\n';
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
  
    int TC = 1;
    while (TC--) {
        testcase();
    }

    return 0;
}