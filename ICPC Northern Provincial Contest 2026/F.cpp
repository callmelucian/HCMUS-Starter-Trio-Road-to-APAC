#include <bits/stdc++.h>
using namespace std;

#define all(v) begin(v), end(v)
#define compact(v) v.erase(unique(all(v)), end(v))
using ll = long long;
using pii = pair<int, int>;

template<class T> bool minimize(T& a, const T& b){ return b < a ? a = b, true : false; }
template<class T> bool maximize(T& a, const T& b){ return b > a ? a = b, true : false; }

#ifdef LOCAL
    #include "debug.hpp"
#else 
    #define dbg(...) ((void)0)
#endif //LOCAL

struct BIT {
    vector<int> tr;
    BIT (int sz) : tr(sz + 1) {}

    int p (int k) { return k & -k; }

    void update (int k, int val) {
        for (; k < tr.size(); k += p(k)) tr[k] += val;
    }

    int query (int k) {
        int ans = 0;
        for (; k; k -= p(k)) ans += tr[k];
        return ans;
    }

    int query (int l, int r) { return query(r) - query(l - 1); }
};

const int maxN = 2e5 + 5;
int A[maxN], L[maxN], R[maxN], U[maxN], V[maxN], nxt[maxN];

void testcase(){
    int N; cin >> N;
    for (int i = 1; i <= N; i++) cin >> A[i];

    BIT smallPos(N + 1);
    vector<int> ord(N);
    iota(all(ord), 1), sort(all(ord), [&] (int i, int j) { return A[i] < A[j]; });

    for (int i : ord) {
        smallPos.update(i, 1);
        L[i] = R[i] = i;
        for (int step = N; step >= 1; step /= 2) {
            while (L[i] - step >= 1 && smallPos.query(L[i] - step, i) == (i - (L[i] - step) + 1)) L[i] -= step;
            while (R[i] + step <= N && smallPos.query(i + 1, R[i] + step) == (R[i] + step - i)) R[i] += step;
        }
        U[i] = R[i] + 1, V[i] = R[i];
        for (int step = N; step >= 1; step /= 2)
            while (V[i] + step <= N && smallPos.query(U[i], V[i] + step) == 0) V[i] += step;
        R[i] = i;
    }

    set<int> s;
    reverse(all(ord));
    for (int i : ord) {
        auto it = s.lower_bound(i);
        if (it != s.end()) nxt[i] = *it;
        s.insert(i);
    }

    auto intersect = [&] (int a, int b, int c, int d) {
        return max(0, min(b, d) - max(a, c) + 1);
    };
    auto exclude = [&] (int &a, int &b, int c, int d) {
        maximize(c, a), minimize(d, b);
        if (c <= d) {
            if (a < c && d < b) {
                cout << "Quit CP\n";
                dbg(a, c, d, b);
                exit(0);
            }
            if (a == c) a = d + 1;
            else b = c - 1;
        }
    };
    auto contain = [&] (int l, int r, int p) { return l <= p && p <= r; };

    // compute result
    ll ans = 1LL * N * (N + 1) / 2;
    for (int i = N; i >= 1; i--) {
        // if (nxt[i]) {
        //     exclude(L[i], R[i], L[nxt[i]], R[nxt[i]]);
        //     exclude(U[i], V[i], U[nxt[i]], V[nxt[i]]);
        // }
        ll curr = 1LL * (R[i] - L[i] + 1) * (V[i] - U[i] + 1);
        for (int u = L[i]; u <= R[i]; u++)
            for (int v = U[i]; v <= V[i]; v++)
                if (!contain(L[nxt[i]], R[nxt[i]], u) || !contain(U[nxt[i]], V[nxt[i]], v)) dbg(i, u, v);
        if (nxt[i]) curr -= 1LL * intersect(L[i], R[i], L[nxt[i]], R[nxt[i]]) * intersect(U[i], V[i], U[nxt[i]], V[nxt[i]]);
        dbg(i, L[i], R[i], U[i], V[i], curr);
        ans -= curr;
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
3
3 1 2

4
1 2 3 4

4
4 3 2 1
*/