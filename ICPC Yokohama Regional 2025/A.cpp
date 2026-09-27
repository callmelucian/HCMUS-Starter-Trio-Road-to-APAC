#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
    #include "debug.hpp"
#else
    #define dbg(...) (void(0))
#endif

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
using pll = pair<ll,ll>;
using db = double;

const int maxN = 3e5 + 5;
bool obstac[2][maxN];
int dp[maxN][2][2];

struct Board : vector<vector<bool>> {
    Board() : vector<vector<bool>>(2, vector<bool>(2)) {}

    friend ostream& operator<< (ostream &o, const Board &b) {
        return o << b[0][0] << " " << b[0][1] << " " << b[1][0] << " " << b[1][1];
    }
};

void testcase() {
    int N; ll L; cin >> N >> L;
    vector<ll> cols = {0, L};
    vector<pll> obst(N);
    for (int i = 0; i < N; i++) {
        ll r, c; cin >> r >> c;
        cols.push_back(c - 1);
        cols.push_back(c);
        cols.push_back(c + 1);
        obst[i] = {r - 1, c};
    }

    // compress
    sort(all(cols)), compact(cols);
    for (auto [a, b] : obst)
        obstac[a][lower_bound(all(cols), b) - cols.begin()] = true;

    // run DP
    for (int i = 0; i < cols.size(); i++)
        for (int f = 0; f < 2; f++)
            for (int g = 0; g < 2; g++) dp[i][f][g] = INT_MAX;
    dp[0][1][1] = 0;

    for (int i = 0; i + 1 < cols.size(); i++) {
        if (cols[i] + 1 < cols[i + 1]) {
            bool isFlip = (cols[i + 1] - cols[i]) & 1;
            minimize(dp[i + 1][0 ^ isFlip][1 ^ isFlip], dp[i][0][1]);
            minimize(dp[i + 1][1 ^ isFlip][0 ^ isFlip], dp[i][1][0]);
            minimize(dp[i + 1][0][0], dp[i][1][1]);
            minimize(dp[i + 1][1][1], dp[i][1][1]);
        }
        else {
            for (int f = 0; f < 2; f++) {
                for (int g = 0; g < 2; g++) {
                    if (dp[i][f][g] == INT_MAX) continue;
                    Board curr;
                    curr[0][0] = f, curr[1][0] = g;
                    curr[0][1] = obstac[0][i + 1];
                    curr[1][1] = obstac[1][i + 1];

                    // dbg(curr);

                    function<void(int,int)> backtrack = [&] (int step, int cost) {
                        // dbg(step, cost);
                        if (step == 6) {
                            if (!curr[0][0] || !curr[1][0]) return;
                            minimize(dp[i + 1][curr[0][1]][curr[1][1]], dp[i][f][g] + cost);
                            return;
                        }

                        backtrack(step + 1, cost);
                        if (step == 0) { // move upper to left
                            if (curr[0][0] == 0 && curr[0][1] == 1) {
                                swap(curr[0][0], curr[0][1]);
                                backtrack(step + 1, cost + 1);
                                swap(curr[0][0], curr[0][1]);
                            }
                        }
                        if (step == 1) { // move lower to left
                            if (curr[1][0] == 0 && curr[1][1] == 1) {
                                swap(curr[1][0], curr[1][1]);
                                backtrack(step + 1, cost + 1);
                                swap(curr[1][0], curr[1][1]);
                            }
                        }
                        if (step == 2) { // move up or down
                            if ((curr[0][1] == 0 && curr[1][1] == 1) || (curr[0][1] == 1 && curr[1][1] == 0)) {
                                swap(curr[0][1], curr[1][1]);
                                backtrack(step + 1, cost + 1);
                                swap(curr[0][1], curr[1][1]);
                            }
                        }
                        if (step == 3) { // place upper
                            if (curr[0][0] == 0 && curr[0][1] == 0) {
                                curr[0][0] = curr[0][1] = 1;
                                backtrack(step + 1, cost);
                                curr[0][0] = curr[0][1] = 0;
                            }
                        }
                        if (step == 4) { // place lower
                            if (curr[1][0] == 0 && curr[1][1] == 0) {
                                curr[1][0] = curr[1][1] = 1;
                                backtrack(step + 1, cost);
                                curr[1][0] = curr[1][1] = 0;
                            }
                        }
                        if (step == 5) { // place right
                            if (curr[0][1] == 0 && curr[1][1] == 0) {
                                curr[0][1] = curr[1][1] = 1;
                                backtrack(step + 1, cost);
                                curr[0][1] = curr[1][1] = 0;
                            }
                        }
                    };
                    backtrack(0, 0);
                }
            }
        }
    }

    for (int i = 0; i < cols.size(); i++)
        for (int f = 0; f < 2; f++)
            for (int g = 0; g < 2; g++)
                if (dp[i][f][g] != INT_MAX) dbg(i, cols[i], f, g, dp[i][f][g]);

    int last = cols.size() - 1, ans = INT_MAX;
    for (int f = 1; f < 2; f++)
        for (int g = 1; g < 2; g++)
            minimize(ans, dp[last][f][g]);
    
    if (ans == INT_MAX) cout << "no\n";
    else cout << ans << "\n";
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

4 5
2 3
1 4
1 5
2 1

1 3
1 1

6 1000000000000
1 2
1 3
1 4
2 1
2 2
2 3

*/