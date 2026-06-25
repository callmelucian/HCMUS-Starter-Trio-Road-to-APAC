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

const int MX = 200005;
int n, k, q, peak;
int id[MX];
bitset<MX> vist = 0;
vector<int> G[MX], rG[MX];
vector<int> a[MX];
vector<vector<int>> pf[MX];
vector<int> pos[MX], R[MX];
vector<int> topo;

struct Node {
    int sum;
    Node *l, *r;
    Node() : sum(0), l(nullptr), r(nullptr) {}
    Node(const Node *o) : sum(o->sum), l(o->l), r(o->r) {}
};

struct SMT {
    int N;
    vector<Node*> root;

    SMT(int n = 0) : N(n) {
        root.assign(n + 5, nullptr);
        root[0] = new Node();
    }

    void copy(int id) {
        root[id] = new Node(root[id - 1]);
    }

    void update(Node *p, int l, int r, vector<int> &pos) {
        if(pos.size() == 0) return;
        if(pos.back() < l) return;
        if(l == r) {
            p->sum++;
            pos.pop_back();
            return;
        }
        int mid = (l + r) >> 1;
        p->l = p->l ? new Node(p->l) : new Node();
        p->r = p->r ? new Node(p->r) : new Node();
        update(p->r, mid + 1, r, pos);
        update(p->l, l, mid, pos);
        p->sum = p->l->sum + p->r->sum;
    }

    void update(vector<int> &pos, int id) {
        update(root[id], 1, N, pos);
    }

    int get(Node *p, int l, int r, const int &u, const int &v) {
        if(p == nullptr || l > v || r < u) return 0;
        if(l >= u && r <= v) return p->sum;
        int mid = (l + r) >> 1;
        return get(p->l, l, mid, u, v) + get(p->r, mid + 1, r, u, v);
    }

    int get(int u, int v, int id) {
        return get(root[id], 1, N, u, v);
    }
};

SMT small[MX];

void dfs(int u) {
    vist[u] = 1;
    for(int v: G[u]) if(!vist[v]) {
        dfs(v);
    }
    topo.push_back(u);  
}

void bfs(int u) {
    id[u] = peak;
    for(int v: rG[u]) if(!id[v]) {
        bfs(v);
    }
}

void testcase() {
    cin >> n >> k >> q;
    for(int i = 1; i <= k; ++i) {
        a[i].assign(n + 1, 0);
        for(int j = 1; j <= n; ++j) cin >> a[i][j];
        for(int j = 2; j <= n; ++j) {   
            G[a[i][j - 1]].push_back(a[i][j]);
            rG[a[i][j]].push_back(a[i][j - 1]);
        }
    }

    topo.clear();
    for(int i = 1; i <= n; ++i) if(!vist[i]) dfs(i);
    reverse(topo.begin(), topo.end());
    peak = 0;
    for(int &i: topo) if(!id[i]) {
        peak++;
        bfs(i);
    }
    
    int srt = sqrt(n);

    for(int i = 1; i <= k; ++i) {
        vector<int> cnt(n + 5, 0);
        for(int j = 1; j <= peak; ++j) pos[j].clear();
        for(int j = 1; j <= n; ++j) R[j].clear();
        for(int j = 1; j <= n; ++j) {
            int x = id[a[i][j]];
            cnt[x]++;
            pos[x].push_back(j);
        }
        for(int t = 1; t <= peak; ++t) {
            if(cnt[t] <= srt) {
                for(int u = 0; u < (int)pos[t].size(); ++u) {
                    for(int v = u + 1; v < (int)pos[t].size(); ++v) {
                        R[pos[t][v]].push_back(pos[t][u]);
                    }
                }
            }
            else {
                vector<int> f(n + 1, 0);
                for(int j = 1; j <= n; ++j) {
                    f[j] += f[j - 1];
                    if(id[a[i][j]] == t) f[j]++;
                }
                pf[i].push_back(f);
            }
        }
        small[i] = SMT(n);
        for(int j = 1; j <= n; ++j) {
            sort(R[j].begin(), R[j].end());
            small[i].copy(j);
            small[i].update(R[j], j);
        }
    }

    ll ans = 0;
    for(int i = 1; i <= q; ++i) {
        int id, l, r;
        cin >> id >> l >> r;
        id = (id + ans) % k + 1;
        l = (l + ans) % n + 1;
        r = (r + ans) % n + 1;
        if(l > r) swap(l, r);
        ans = small[id].get(l, r, r);
        for(int j = 0; j < (int)pf[i].size(); ++j) {
            ll x = pf[i][j][r] - pf[i][j][l - 1];
            ans += x * (x - 1) / 2;
        }
        dbg(l, r, ans);
        cout << ans << '\n';
    }

    topo.clear();
    for(int i = 1; i <= k; ++i) {
        a[i].clear();
        pf[i].clear();
    }
    for(int i = 1; i <= n; ++i) {
        id[i] = 0;
        vist[i] = 0;
        G[i].clear();
        rG[i].clear();
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
  
    int TC = 1; cin >> TC;
    while (TC--) {
        testcase();
    }

    return 0;
}

/*

6
5 2 2
1 2 3 4 5
5 4 3 2 1
1 0 2
1 2 1
5 3 3
1 2 3 4 5
1 3 2 4 5
1 2 3 5 4
0 0 2
0 2 3
1 0 3
5 2 2
1 2 3 4 5
5 4 3 2 1
1 0 2
1 2 1
5 3 3
1 2 3 4 5
1 3 2 4 5
1 2 3 5 4
0 0 2
0 2 3
1 0 3
5 2 2
1 2 3 4 5
5 4 3 2 1
1 0 2
1 2 1
5 3 3
1 2 3 4 5
1 3 2 4 5
1 2 3 5 4
0 0 2
0 2 3
1 0 3



1
5 2 2
1 2 3 4 5
5 4 3 2 1
1 0 2
1 2 1

1
5 3 3
1 2 3 4 5
1 3 2 4 5
1 2 3 5 4
0 0 2
0 2 3
1 0 3

1
5 3 3
1 3 4 5 2
3 2 4 1 5
4 3 5 2 1
0 2 3
1 0 2
2 1 3

*/