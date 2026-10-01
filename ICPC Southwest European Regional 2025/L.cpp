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

const int maxN = 5e5 + 5;
vector<pii> qry[maxN];
ll posSet[26][2][maxN], hashVal[maxN];
int ans[maxN], freq[26][maxN];

mt19937 rng(21);

void testcase() {
    // input
    int N, Q; cin >> N >> Q;
    string s; cin >> s;
    s = " " + s;

    for (int i = 0; i < Q; i++) {
        int l, r; cin >> l >> r;
        if (l == r) ans[i] = 1;
        else qry[r].emplace_back(l, i);
    }

    // random hash values
    for (int i = 1; i <= N + 1; i++) hashVal[i] = rng();

    // prepare hashes
    for (int ch = 0; ch < 26; ch++) {
        for (int delta = 0; delta < 2; delta++) {
            for (int i = 1; i <= N; i++) {
                int curr = (s[i] - 'a' == ch ? hashVal[i + delta] : 0);
                posSet[ch][delta][i] = posSet[ch][delta][i - 1] + curr;
            }
        }
        for (int i = 1; i <= N; i++)
            freq[ch][i] = freq[ch][i - 1] + (s[i] - 'a' == ch);
    }
    auto getHash = [&] (int ch, int delta, int l, int r) {
        return posSet[ch][delta][r] - posSet[ch][delta][l - 1];
    };
    auto count = [&] (int ch, int l, int r) {
        return freq[ch][r] - freq[ch][l - 1];
    };

    dbg();

    // process queries
    vector<int> last(26);
    for (int r = 1; r <= N; r++) {
        last[s[r] - 'a'] = r;
        for (const auto &[l, idx] : qry[r]) {
            vector<int> nxtChar(26, -1), dp(26, -1);
            int frequent = 0;

            for (int j = 0; j < 26; j++) {
                maximize(frequent, count(j, l, r));
                if (last[j] <= l) continue;
                int prv = last[j] - 1, prvChar = s[prv] - 'a';
                if (getHash(prvChar, 1, l, r) == getHash(j, 0, l, r)) {
                    nxtChar[j] = prvChar;
                    dbg(j, prvChar, l, r);
                    // dbg(getHash(prvChar, 1, l, r));
                    // dbg(getHash(j, 0, l, r));
                }
            }

            function<int(int)> calc = [&] (int x) {
                if (dp[x] != -1) return dp[x];
                return dp[x] = (nxtChar[x] == -1 ? 0 : calc(nxtChar[x])) + 1;
            };
            for (int j = 0; j < 26; j++) {
                if (frequent == count(j, l, r)) maximize(ans[idx], calc(j));
                // maximize(ans[idx], calc(j));
            }
        }
    }

    // output
    for (int i = 0; i < Q; i++) cout << ans[i] << "\n";
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
5 4
ababa
1 1
1 5
1 4
2 5
*/