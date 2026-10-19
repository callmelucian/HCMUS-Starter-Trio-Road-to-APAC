#include <bits/stdc++.h>
using namespace std;

#define all(v) begin(v), end(v)
#define sz(v) (int)v.size()
#define compact(v) v.erase(unique(all(v)), end(v))
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
template<class T> bool minimize(T& a, const T& b){ return a > b ? a = b, 1 : 0; }
template<class T> bool maximize(T& a, const T& b){ return a < b ? a = b, 1 : 0; }

#ifdef LOCAL
    #include "debug.hpp"
#else 
    #define dbg(...) ((void)0)
#endif //LOCAL

const int maxN = 1e5 + 5;
int lo[maxN], hi[maxN];
vector<int> blocks[maxN];

struct IT {
    vector<int> tr;
    int n;
    IT (int siz) {
        n = 1;
        while(n < siz) n <<= 1;
        tr.resize(2 * n, INT_MAX);
    }

    void incr (int pos, int amount, bool increase = true) {
        int k = pos + n;
        if (increase) tr[k] += amount;
        else tr[k] = amount;
        for (k >>= 1; k; k >>= 1)
            tr[k] = min(tr[k << 1], tr[k << 1 | 1]);
    }

    int get() { return tr[1]; }
};

void testcase(){
    int N; cin >> N;
    for (int i = 0; i < N; i++) {
        int k; cin >> k >> lo[i] >> hi[i];
        blocks[i] = vector<int>(k);
        for (int &u : blocks[i]) cin >> u;
        reverse(all(blocks[i]));
    }

    IT tree(N);
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    for (int i = 0; i < N; i++) {
        tree.incr(i, hi[i], false);
        for (int u : blocks[i]) tree.incr(i, -u);
        if (blocks[i].size()) pq.emplace(lo[i] + blocks[i].back(), i);
    }

    int maxLo = *max_element(lo, lo + N), ans = max(0, tree.get() - maxLo);
    while (pq.size()) {
        int i = pq.top().second; pq.pop();
        lo[i] += blocks[i].back();
        maximize(maxLo, lo[i]);
        tree.incr(i, blocks[i].back());
        blocks[i].pop_back();
        if (blocks[i].size()) pq.emplace(lo[i] + blocks[i].back(), i);
        maximize(ans, tree.get() - maxLo);
    }
    cout << ans << "\n";
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
2
2 2 11 3 2
3 4 12 1 1 2

2
2 0 7 2 4
1 4 9 4

4
4 2 14 2 3 4 1
2 1 9 3 2
3 3 10 4 1 1
0 1 10
*/