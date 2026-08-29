#include <bits/stdc++.h>
#ifdef LOCAL
    #include "debug.hpp"
    const bool local = false;
#else 
    #define dbg(...)
    const bool local = false;
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

template<class T> bool minimize (T& a, const T& b) { return (a > b ? a = b, 1 : 0); }
template<class T> bool maximize (T& a, const T& b) { return (a < b ? a = b, 1 : 0); }

mt19937 rng(21);

int rr (int l, int r) { return uniform_int_distribution<int>(l, r)(rng); }

vector<int> genSeq (int n, int sum) { // n << sum
    set<int> s = {sum};
    while (s.size() < n) s.insert(rr(1, sum - 1));

    vector<int> v;
    int last = 0;
    for (int u : s) v.push_back(u - last), last = u;
    shuffle(all(v), rng);
    return v;
}

const int M = 1e9;

vector<int> gen (int n) {
    vector<int> v = genSeq(n / 2, M), tmp = genSeq(n / 2, M);
    v.insert(v.end(), all(tmp));
    shuffle(all(v), rng);
    return v;
}

void testcase() {
    int N = 100;
    if (!local) cin >> N;

    vector<int> A(N), ord(N), ans;
    if (local) A = gen(N);
    else {
        for (int &u : A) cin >> u;
    }
    iota(all(ord), 0);
    sort(all(ord), [&] (int i, int j) { return A[i] > A[j]; });

    while (ans.empty()) {
        int curr = 0;
        for (int i = 0; i < ord.size(); i++)
        if (curr + A[ord[i]] <= M) curr += A[ord[i]], ans.push_back(ord[i]);
        if (curr != M) ans.clear();
        shuffle(all(ord), rng);
    }

    cout << ans.size() << " ";
    for (int u : ans) cout << u + 1 << " ";
    cout << "\n";
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