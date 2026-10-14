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

const int maxN = 2e5 + 5;
int spt[maxN][21];

int query (int l, int r) {
    int p = 31 - __builtin_clz(r - l + 1);
    return min(spt[l][p], spt[r - (1 << p) + 1][p]);
}

void testcase(){
    int N; cin >> N;
    for (int i = 1; i <= N; i++) cin >> spt[i][0];
    for (int s = 1; (1 << s) <= N; s++) {
        int p = s - 1;
        for (int i = 1; i + (1 << s) - 1 <= N; i++)
            spt[i][s] = min(spt[i][p], spt[i + (1 << p)][p]);
    }

    int ans = 0;
    for (int L = 1; L <= N; L++) {
        for (int R = L; R <= N; R++) {
            bool flag = 0;
            int mx = 0;
            for (int p = L; p < R; p++) {
                maximize(mx, spt[p][0]);
                if (mx < query(p + 1, R)) flag = true;
            }
            ans += !flag;
            // if (!flag) dbg(L, R);
        }
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