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
#define int long long

using ll = long long;
using db = double;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using tpl = tuple<int,int,int>;

template<class T> bool minimize(T& a, const T& b){  return (a > b ? a = b, 1 : 0); }
template<class T> bool maximize(T& a, const T& b){  return (a < b ? a = b, 1 : 0); }

struct BIT {
    int n;
    vector<int> tree;

    BIT(int n = 0) : n(n), tree(n + 5, 0) {}

    void update(int idx, int val) {
        for(; idx <= n; idx += -idx & idx) tree[idx] += val;
    }

    int get(int idx) {
        int res = 0;
        for(; idx; idx -= -idx & idx) res += tree[idx];
        return res;
    }

    int walk(int k) {
        int pos = 0;
        for(int mask = (1LL << 19); mask; mask >>= 1) {
            if(pos + mask <= n && k > tree[pos + mask]) {
                pos += mask;
                k -= tree[pos];
            }
        }
        return pos + 1;
    }
};

int n, k;
const int MX = 500005;
int a[MX], b[MX];
vector<int> rv;
BIT cnt(n), sum(n);

int cost(int sz, int total) {
    if(sz == 1) return 0;
    int mid = (sz + 1) / 2;
    int pos = cnt.walk(mid);
    int lhs = cnt.get(pos);
    int rhs = sz - lhs;
    int lh = sum.get(pos);
    int rh = total - lh;
    return (rv[pos - 1] * lhs - lh) + (rh - rhs * rv[pos - 1]);
}

void testcase() {
    cin >> n >> k;
    for(int i = 1; i <= n; ++i) cin >> a[i], a[i] -= i;
    rv.resize(n);

    for(int i = 1; i <= n; ++i) rv[i - 1] = a[i];
    sort(rv.begin(), rv.end());
    rv.erase(unique(rv.begin(), rv.end()), rv.end());
    for(int i = 1; i <= n; ++i) b[i] = lower_bound(rv.begin(), rv.end(), a[i]) - rv.begin() + 1;
    

    cnt = sum = BIT(n);
    
    int ans = 0;
    for(int l = 1, r = 1; l <= n; ++l) {
        while(r <= n) {
            cnt.update(b[r], 1);
            sum.update(b[r], a[r]);
            if(cost(r - l + 1, sum.get(n)) > k) {
                cnt.update(b[r], -1);
                sum.update(b[r], -a[r]);
                break;
            }
            ++r;
        }
        ans = max(ans, r - l);
        cnt.update(b[l], -1);
        sum.update(b[l], -a[l]);
    }

    cout << ans << '\n';
}

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
  
    int TC = 1; cin >> TC;
    while (TC--) {
        testcase();
    }

    return 0;
}

/*

5
7 5
7 2 5 5 4 11 7
6 0
100 3 4 5 99 100
5 6
1 1 1 1 1
5 50
100 200 300 400 500
1 100
3

1
7 5
7 2 5 5 4 11 7

*/