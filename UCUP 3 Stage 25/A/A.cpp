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

struct DSU {
    vector<int> lab;
    DSU (int sz) : lab(sz + 1, -1) {}

    int get (int u) {
        if (lab[u] < 0) return u;
        return lab[u] = get(lab[u]);
    }

    bool unite (int a, int b) {
        a = get(a), b = get(b);
        if (a == b) return false;
        if (-lab[a] < -lab[b]) swap(a, b);
        lab[a] += lab[b], lab[b] = a;
        return true;
    }

    bool same (int a, int b) {
        return get(a) == get(b);
    }
};

void testcase() {
    string a, b, c; cin >> a >> b >> c;
    if (a.size() != b.size()) return cout << "NO\n", void();
    if (a.size() != c.size()) return cout << "YES\n", void();

    bool ans = false;
    DSU dsu(30);
    for (int i = 0; i < a.size(); i++)
        dsu.unite(a[i] - 'a', b[i] - 'a');
    
    for (int i = 0; i < a.size(); i++)
        if (!dsu.same(a[i] - 'a', c[i] - 'a'))
            return cout << "YES\n", void();
    cout << "NO\n";
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