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
using pii = pair<int, int>;
using pll = pair<ll, ll>;

#ifdef LOCAL 
    #include "debug.hpp"
#else
    #define dbg(...) (void(0))
#endif //LOCAL

void testcase(){
    int N; cin >> N;
    vector<int> W(N + 2), burn(N + 1);

    for (int i = 1; i <= N; i++) cin >> W[i];
    for (int i = 1; i <= N; i++)
        burn[i] = min(W[i], min(W[i - 1], W[i + 1]) + 1);

    if (*max_element(all(W)) == 0) return cout << 0 << "\n", void();

    vector<int> prf(N + 1), sfx(N + 1);
    for (int i = 1; i <= N; i++) {
        prf[i] = burn[i] - 1 - i;
        if (i > 1) minimize(prf[i], prf[i - 1]);
    }
    for (int i = N; i >= 1; i--) {
        sfx[i] = burn[i] - 1 + i;
        if (i < N) minimize(sfx[i], sfx[i + 1]);
    }

    int ans = 0;
    for (int i = 1; i <= N; i++)
        if (burn[i] > 1) maximize(ans, min(i + prf[i], sfx[i] - i));
    cout << ans + 1 << "\n";
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
5
2 3 4 2 3

13
2 5 6 6 4 3 4 3 1 2 4 8 4

3
1 0 2

1
0
*/