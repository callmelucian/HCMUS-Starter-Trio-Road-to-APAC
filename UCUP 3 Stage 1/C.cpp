#include <bits/stdc++.h>
using namespace std;

#define all(v) begin(v), end(v)
#define rall(v) rbegin(v), rend(v)
#define sz(v) (int)v.size()
#define pb push_back
#define eb emplace_back
#define compact(v) v.erase(unique(all(v)), end(v))
template<class T> bool minimize(T& a, const T& b){ return a > b ? a = b, 1 : 0; }
template<class T> bool maximize(T& a, const T& b){ return a < b ? a = b, 1 : 0; }
using ll = long long;
using db = double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#ifdef LOCAL 
    #include "debug.hpp"
#else 
    #define dbg(...) ((36))
#endif //LOCAL

int add (int a, int b) { return min(a, b) == INT_MIN ? INT_MIN : a + b; }

struct Node {
    int sum, best, prf, sfx;

    Node() : sum(0), best(INT_MIN), prf(INT_MIN), sfx(INT_MIN) {}
    Node (int v) : sum(v), best(max(0, v)), prf(max(0, v)), sfx(max(0, v)) {}

    friend Node operator+ (const Node &a, const Node &b) {
        Node ans;
        ans.sum = add(a.sum, b.sum);
        ans.best = max({a.best, b.best, add(a.sfx, b.prf)});
        ans.prf = max(a.prf, add(a.sum, b.prf));
        ans.sfx = max(add(a.sfx, b.sum), b.sfx);
        return ans;
    }
};

struct IT {
    vector<Node> tr;
    int n;
    IT (int sz) : tr(sz << 2), n(sz) {}

    void update (int pos, int value) {
        int k = 1;
        for (int l = 1, r = n; l < r;) {
            int mid = (l + r) >> 1;
            if (pos <= mid) k <<= 1, r = mid;
            else k = k << 1 | 1, l = mid + 1;
        }
        tr[k] = value;
        for (k >>= 1; k; k >>= 1) {
            tr[k] = tr[k << 1] + tr[k << 1 | 1];
            // dbg(k, tr[k].best, tr[k].sum, tr[k].prf, tr[k].sfx);
        }
    }

    int get() { return tr[1].best; }
};

void testcase(){
    int N, K; cin >> N >> K;
    vector<int> A(N + 1), ord(N);
    for (int i = 1; i <= N; i++) cin >> A[i];
    string s; cin >> s;
    s = " " + s;

    iota(all(ord), 1);
    sort(all(ord), [&] (int i, int j) {
        return A[i] < A[j];
    });

    IT tree(N);
    for (int i = 1; i <= N; i++)
        tree.update(i, (s[i] == '1' ? 1 : INT_MIN));

    dbg(tree.get());
    
    int ans = 0;
    if (tree.get() >= K) ans = A[ord[0]];

    for (int i = 0; i < (int)ord.size(); i++) {
        tree.update(ord[i], 0);
        if (i + 1 < (int)ord.size() && A[ord[i]] == A[ord[i + 1]]) continue;
        if (tree.get() >= K) ans = A[ord[i + 1]];
        dbg(ord[i], A[ord[i]], tree.get());
    }

    cout << ans << "\n";
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int tests = 1;
    // cin >> tests;
    while(tests--){
        testcase();
    }
    return 0;
}

/*
5 2
1 2 3 4 5
01101

5 2
3 4 5 2 1
10101
*/