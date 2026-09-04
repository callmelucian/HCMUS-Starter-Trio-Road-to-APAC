#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
    #include "debug.hpp"
#else
    #define dbg(...) ((void)0)
#endif // LOCAL

#define all(v) begin(v), end(v)
#define rall(v) rbegin(v), rend(v)
#define compact(v) v.erase(unique(all(a)), a.end())
#define sz(v) (int)v.size()
#define pb push_back
#define eb emplace_back

using ll = long long;
using db = double;
using pii = pair<int,int>;
using pll = pair<ll,ll>;

template<class T> bool minimize (T &a, const T &b) { return a > b ? a = b, 1 : 0; }
template<class T> bool maximize (T &a, const T &b) { return a < b ? a = b, 1 : 0; }

void brute() {
    int n = 21;
    for (int mask = 0; mask < (1 << n); mask++) {
        int a = __builtin_popcount(mask), b = n - __builtin_popcount(mask), ans = 0;
        for (int i = 0; i <= a; i++)
            for (int j = 0; j <= b; j++) maximize(ans, i | j);


        bool found = false;
        for (int i = 0; i < n && !found; i++) {
            int currA = 0, currB = 0;
            for (int j = i; j < n && !found; j++) {
                ((mask >> j & 1) ? currA : currB)++;
                if ((currA | currB) == ans) found = true;
            }
        }
        if (!found) {
            cout << "WA\n";
            exit(0);
        }
        
        if (mask % 100) cout << "AC" << endl;
    }
}

bool getCur (int mask, int pos) { return mask >> pos & 1; }

void testcase() {
    int N; cin >> N;
    vector<int> cnt(N + 2);
    for (int i = 1; i <= N; i++) {
        int a; cin >> a;
        cnt[a]++;
    }

    vector<int> prf = cnt, sfx = cnt;
    for (int i = 1; i <= N; i++) maximize(prf[i], prf[i - 1]);
    for (int i = N; i >= 1; i--) maximize(sfx[i], sfx[i + 1]);

    int ans = 0;
    for (int i = 1; i <= N; i++) {
        int bound = max(prf[i - 1], sfx[i + 1]);
        auto trySolve = [&] (int mask) {
            int needMask = 0;
            for (int j = 19; j >= 0; j--) {
                if (getCur(mask, j)) continue;
                if ((needMask | (1 << j)) <= bound) needMask |= (1 << j);
            }
            maximize(ans, needMask | mask);
        };

        for (int j = 0; j < 20; j++) {
            if (!getCur(cnt[i], j)) continue;
            int newMask = cnt[i];
            newMask ^= (1 << j);
            for (int k = 0; k < j; k++)
                if (!getCur(newMask, k)) newMask |= (1 << k);
            trySolve(newMask);
        }
        trySolve(cnt[i]);
    }
    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    int tests = 1;
    cin >> tests;
    while (tests--) {
        testcase();
    }

    return 0;
}

/*
2
7
1 2 3 4 3 2 1
9
1 1 1 1 1 2 2 2 2
*/