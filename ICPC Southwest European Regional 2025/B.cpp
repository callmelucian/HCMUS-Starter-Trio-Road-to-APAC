#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
    #include "debug.hpp"
#else
    #define dbg(...) ((void)0)
#endif // LOCAL 

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

void testcase(){
    int N, l, r; cin >> N >> l >> r;
    vector<int> A(N + 2);
    for (int i = 1; i <= N; i++) cin >> A[i];
    sort(A.begin() + 1, A.begin() + N + 1);

    vector<ll> prf(N + 2), sfx(N + 2);
    for (int i = 1; i <= N; i++) prf[i] = prf[i - 1] + A[i];
    for (int i = N; i >= 1; i--) sfx[i] = sfx[i + 1] + A[i];

    ll ans = 0;
    for (int alpha = -N; alpha <= N; alpha++) {
        int takeX = (N + alpha) / 2, takeY = (N - alpha) / 2;
        ll cst = sfx[N - takeY + 1] - prf[takeX];
        maximize(ans, 1LL * alpha * (alpha >= 0 ? l : r) + cst);
    }
    cout << ans << "\n";
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int tests = 1;
    cin >> tests;
    while(tests--){
        testcase();
    }
    return 0;  
}

/*
4
1 1 5
3
2 100 100
50 200
5 1 10
5 7 3 9 1
5 6 10
9 3 1 7 5
*/