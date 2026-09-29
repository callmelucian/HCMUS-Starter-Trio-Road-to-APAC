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
    int N, M; cin >> N >> M;
    vector<int> A(N);
    for (int i = 0; i < N; i++) cin >> A[i];

    vector<int> fullRows;
    int bound = (M + 1) / 2;
    for (int i = 0; i < N; i++) {
        if (A[i] > bound) return cout << -1 << "\n", void();
        if (A[i] == bound) fullRows.push_back(i);
    }

    vector<vector<bool>> vec(N, vector<bool>(M));
    auto fillRow = [&] (int i, int start, int fillCnt, bool fromLeft, bool reset) {
        for (int j = 0; reset && j < M; j++) vec[i][j] = false;
        for (int j = start, cnt = 0; fromLeft && cnt < fillCnt; j += 2, cnt++) vec[i][j] = true;
        for (int j = M - 1 - start, cnt = 0; !fromLeft && cnt < fillCnt; j -= 2, cnt++) vec[i][j] = true;
    };
    auto calcBound = [&] (int prt) {
        return M / 2 + (prt ^ 1);
    };

    if ((M & 1) && fullRows.size()) {
        dbg(0);
        for (int i : fullRows)
            for (int j = 0; j < M; j += 2) vec[i][j] = true;

        for (int it = 0; it + 1 < fullRows.size(); it++) {
            if ((fullRows[it + 1] - fullRows[it]) & 1) {
                // try to insert a chain of >= 2 rows that flips the parity
                bool found = false;
                for (int r = fullRows[it] + 1, start = 1; r + 1 < fullRows[it + 1] && !found; r++, start ^= 1) {
                    // chain starts at r
                    fillRow(r, start, A[r], true, true);

                    int freeRight = calcBound(start) - A[r], need = 0;
                    for (int i = r + 1, prt = start; i < fullRows[it + 1] && !found; i++, prt ^= 1) {
                        need = max(0, A[i] - freeRight);
                        fillRow(i, prt, min(A[i], freeRight), false, true); // fill from right
                        fillRow(i, prt ^ 1, need, true, false); // fill from left
                        freeRight = calcBound(prt ^ 1) - need;
                    }
                    if (!need) found = true;
                }
                if (!found) return cout << -1 << "\n", void();
            }
            else {
                for (int i = fullRows[it] + 1, start = 1; i < fullRows[it + 1]; i++, start ^= 1) fillRow(i, start, A[i], true, false);
            }
        }

        for (int i = fullRows.front() - 1, start = 1; i >= 0; i--, start ^= 1) fillRow(i, start, A[i], true, false);
        for (int i = fullRows.back() + 1, start = 1; i < N; i++, start ^= 1) fillRow(i, start, A[i], true, false);
    }
    else {
        for (int i = 0; i < N; i++) fillRow(i, i & 1, A[i], true, false);
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) cout << vec[i][j];
        cout << "\n";
    }
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
6 7
4 3 2 2 3 4

6 7
4 1 1 4 3 3

6 9
5 2 3 4 4 5

6 9
5 2 4 4 3 5

6 9
5 2 4 4 4 5

8 9
5 2 4 4 4 4 2 5
*/