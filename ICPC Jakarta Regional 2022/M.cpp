#include <bits/stdc++.h>
using namespace std;

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

void testcase(){
    int N, Q; cin >> N >> Q;
    vector<ll> A(N + 1), B(N + 1);
    for (int i = 1; i <= N; i++) cin >> A[i];
    for (int i = 1; i <= N; i++) cin >> B[i];
    bool negLoop = false;

    rotate(B.begin() + 1, B.begin() + N, B.end());
    // dbg(B);

    // case 1
    if (accumulate(all(A), 0LL) < 0) negLoop = true;
    if (accumulate(all(B), 0LL) < 0) negLoop = true;

    // case 2
    for (int i = 1; i <= N; i++) {
        int j = (i + 1 <= N ? i + 1 : 1);
        if (A[i] + B[j] < 0) negLoop = true;
    }

    partial_sum(all(A), A.begin());
    partial_sum(all(B), B.begin());

    auto queryA = [&] (int l, int r) { return A[r] - A[l - 1]; };
    auto queryB = [&] (int l, int r) { return B[r] - B[l - 1]; };

    while (Q--) {
        int s, t; cin >> s >> t;
        if (negLoop) {
            cout << "flawed\n";
            continue;
        }
        if (s == t) {
            cout << 0 << "\n";
            continue;
        }
        ll goRight = (s < t ? queryA(s, t - 1) : queryA(s, N) + queryA(1, t - 1));
        ll goLeft = (s > t ? queryB(t + 1, s) : queryB(1, s) + queryB(t + 1, N));
        // dbg(1, s, queryB(1, s), t + 1, N, queryB(t + 1, N));
        // dbg(goRight, goLeft);
        cout << min(goRight, goLeft) << "\n";
    }
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
4 4
2 3 -4 3
1 2 7 -1
1 3
3 1
1 4
1 1

4 3
1 2 -3 4
4 -3 2 1
1 1
2 4
3 1

6 2
-6 8 -3 5 -9 4
9 -2 8 -4 12 -1
2 6
3 3
*/