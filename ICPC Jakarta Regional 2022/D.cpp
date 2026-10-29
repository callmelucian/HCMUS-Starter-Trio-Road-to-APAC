#include <bits/stdc++.h>
using namespace std;

#define int long long
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

const int MX = 100005;
int n, m, S, T;
int d[2][MX], a[MX];
vector<pii> G[MX];

struct Line {
    mutable ll k, m, p;
    bool operator < (const Line &o) const { return k < o.k; }
    bool operator < (ll x) const { return p < x; }
};

struct LineContainer : multiset<Line, less<>> {
    static const ll inf = LLONG_MAX;
    
    ll div (ll a, ll b) {
        return a / b - ((a ^ b) < 0 && a % b); 
    }

    bool isect(iterator x, iterator y) {
        if (y == end()) return x->p = inf, 0;
        if(x->k == y->k) x->p = x->m > y->m ? inf : -inf;
        else x->p = div(y->m - x->m, x->k - y->k);
        return x->p >= y->p;
    }

    void add(ll k, ll m) {
        auto z = insert({k, m, 0}), y = z++, x = y;
        while(isect(y, z)) z = erase(z);
        if(x != begin() && isect(--x, y)) isect(x, y = erase(y));
        while((y = x) != begin() && (--x)->p >= y->p)
            isect(x, erase(y));
    }
    ll query(ll x) {
        assert(!empty());
        auto l = *lower_bound(x);
        return l.k * x + l.m;
    }
};

int sqr(int x) {
    return x * x;
}

double sqrd(int x) {
    return x * x;
}

void dijkstra(int Source, int *d) {
    priority_queue<pii, vector<pii>, greater<pii>> Q;
    for(int i = 0; i <= n; ++i) d[i] = 1e18;
    Q.push({d[Source] = 0, Source});
    while(Q.size()) {
        auto [du, u] = Q.top();
        Q.pop();
        if(du != d[u]) continue;
        for(auto [v, w] : G[u]) {
            if(d[v] > d[u] + w) {
                d[v] = d[u] + w;
                Q.push({d[v], v});
            }
        }
    }
}

void testcase(){
    cin >> n >> m >> S >> T;
    for(int i = 1; i <= n; ++i) cin >> a[i];
    for(int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        int w = (a[u] - a[v]) * (a[u] - a[v]);
        G[u].push_back({v, w});
        G[v].push_back({u, w});
    }

    dijkstra(S, d[0]);
    dijkstra(T, d[1]);

    // Must double the value
    for(int i = 1; i <= n; ++i) d[0][i] <<= 1;
    for(int i = 1; i <= n; ++i) d[1][i] <<= 1;

    int ans = d[0][T];
    for(auto [v, _] : G[T]) ans = min(ans, d[0][v]);
    for(auto [v, _] : G[S]) ans = min(ans, d[1][v]);
    for(int u = 1; u <= n; ++u) {
        LineContainer DWUY;
        // take u as the middle of the path
        for(auto [v, _]: G[u]) {
            // y = mx + k
            int m = -2 * a[v];
            int k = d[0][v] + sqr(a[v]);
            dbg(m, k);
            DWUY.add(-m, -k);
        }
        for(auto [v, _]: G[u]) {
            // query: f(x) + C
            int x = a[v];
            int C = d[1][v] + sqr(a[v]);
            
            ans = min(ans, -DWUY.query(x) + C);
        }
    }

    cout << ans / 2 << (ans & 1 ? ".5" : ".0");

    // for(int i = 1; i <= n; ++i) cout << d[0][i] << ' '; cout << '\n';
    // for(int i = 1; i <= n; ++i) cout << d[1][i] << ' '; cout << '\n';

    // dbg(S, d[0]);
    // dbg(T, d[1]);
}

int32_t main(){
    ios_base::sync_with_stdio(0); cin.tie(0);

    int t = 1;
    // cin >> t;
    while(t--){
        testcase();
    }
    return 0;
}

/*

5 6 1 3
5 100 8 2 10
1 2
2 3
2 5
1 4
4 5
3 5

5 5 1 5
100 2 10 10 4
1 2
2 3
2 4
3 5
4 5

5 4 1 4
8 8 8 8 100
1 2
2 3
3 4
4 5

*/