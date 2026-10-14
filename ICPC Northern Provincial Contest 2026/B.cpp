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

ll prf[1010][1010], cell[1010][1010], A[1010];

ll query (int i, int j, int L) {
    return prf[i][j] - prf[i - L][j] - prf[i][j - L] + prf[i - L][j - L];
}

ll rangeSum (int l, int r) { return A[r] - A[l - 1]; }

int maxLength (int L, int R, ll ub) {
    A[L - 1] = 0;
    for (int i = L; i <= R; i++) A[i] += A[i - 1];

    int ans = 0;
    for (int l = L, r = L - 1; l <= R; l++) {
        while (r + 1 <= R && rangeSum(l, r + 1) <= ub) r++;
        maximize(ans, r - l + 1);
    }
    return ans;
}

int counting (int L, int R, ll lb, ll ub) {
    A[L - 1] = 0;
    for (int i = L; i <= R; i++) A[i] += A[i - 1];

    int ans = 0;
    for (int i = L, l = L, r = L - 1; i <= R; i++) {
        while (l < i || (l <= R && rangeSum(i, l) < lb)) l++;
        while (r + 1 <= R && rangeSum(i, r + 1) <= ub) r++;
        // dbg(i, l, r);
        ans += r - l + 1;
    }
    return ans;
}

int bruteCount (int L, int R, ll lb, ll ub) {
    int ans = 0;
    for (int l = L; l <= R; l++) {
        ll sum = 0;
        for (int r = l; r <= R; r++)
            sum += A[r], ans += (lb <= sum && sum <= ub);
    }
    return ans;
}

void testcase(){
    int N, M, q, p; cin >> N >> M >> q >> p;
    for (int i = 1; i <= N; i++) {
        ll sum = 0;
        for (int j = 1; j <= M; j++) {
            cin >> cell[i][j];
            sum += cell[i][j];
            prf[i][j] = prf[i - 1][j] + sum;
        }
    }

    for (int i = 0; i < q; i++) {
        int L, row; ll maxVal; cin >> L >> row >> maxVal;
        for (int j = 1; j <= M; j++) A[j] = query(row, j, L) * cell[row][j];
        // cout << "? ";
        cout << maxLength(L, M, maxVal) << "\n";
    }

    for (int i = 0; i < p; i++) {
        int L, row; ll minVal, maxVal; cin >> L >> row >> minVal >> maxVal;
        for (int j = L; j <= M; j++) A[j] = query(row, j, L) * cell[row][j];
        // dbg(bruteCount(L, M, minVal, maxVal));
        // cout << bruteCount(L, M, minVal, maxVal) << " ";
        cout << counting(L, M, minVal, maxVal) << "\n";
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
4 4 0 1
1 3 5 2
4 3 1 2
7 8 1 1
2 2 3 1
1 4 8 10

4 4 2 2
1 3 5 2
4 3 1 2
7 8 1 1
2 2 3 1
2 4 20
1 4 16
2 2 30 100
1 4 8 10

4 4 2 3
1 3 5 2
4 3 1 2
7 8 1 1
2 2 0 1
2 4 20
1 4 16
1 4 0 100
2 2 30 100
1 4 8 10

4 4 2 0
1 3 5 2
4 3 1 2
7 8 1 1
2 2 3 1
2 4 20
1 4 16
*/