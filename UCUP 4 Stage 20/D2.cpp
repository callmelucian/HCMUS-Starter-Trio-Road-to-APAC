#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
    #include "debug.hpp"
#else
    #define dbg(...) (void(0))
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

const int mod = 998244353;
struct mint{
    int v;
    mint(int _v = 0) : v(_v) {}
    mint& operator += (const mint& o){
        v += o.v;
        if(v >= mod) v -= mod;
        return *this;
    }
    mint& operator -= (const mint& o){
        v -= o.v;
        if(v < 0) v += mod;
        return *this;
    }
    friend mint operator + (mint a, const mint& b){ return a += b; }
    friend mint operator - (mint a, const mint& b){ return a -= b; }
    friend istream& operator >> (istream& in, mint& o){ return in >> o.v; }
    friend ostream& operator << (ostream& out, const mint& o){ return out << o.v; }
};
const int maxN = 5005;
mint dp[maxN][2][2];
int spt[maxN][20];

int query (int l, int r) {
    if (l > r) return 0;
    int p = 31 - __builtin_clz(r - l + 1);
    return max(spt[l][p], spt[r - (1 << p) + 1][p]);
}

void testcase(){
    int N; cin >> N;
    for (int i = 1; i <= N; i++) cin >> spt[i][0];
    for (int s = 1; (1 << s) <= N; s++) {
        int p = s - 1;
        for (int i = 1; i + (1 << s) - 1 <= N; i++)
            spt[i][s] = max(spt[i][p], spt[i + (1 << p)][p]);
    }

    auto canCenter = [&] (int i) {
        return 1 < i && i < N && spt[i - 1][0] < spt[i][0] && spt[i][0] > spt[i + 1][0];
    };

    // run DP
    for (int i = 1; i <= N; i++) {
        for (int f = 0; f < 2; f++) {
            if (f && !canCenter(i)) continue;
            for (int l = 0; l < 2; l++) {
                if (((i & 1) ^ l) != f) continue;
                for (int j = i - 1 - f; j >= 1; j--) {
                    if (query(j + 1, i - 1) > max(spt[i][0], spt[j][0])) continue;
                    int len = (i - 1) - (j + 1) + 1, g = ((len & 1) ^ f);
                    dp[i][f][l] += dp[j][g][l ^ 1];
                }
                if (l && ((i - 1) & 1) == f && query(1, i - 1) < spt[i][0]) dp[i][f][l] += 1;
                // dbg(i, f, l, dp[i][f][l]);
            }
        }
    }
    
    mint ans;
    for (int i = 1; i <= N; i++) {
        for (int f = 0; f < 2; f++) {
            for (int l = 0; l < 2; l++) {
                // a[i] is the last element in the final sequence
                if (((N - (i + 1) + 1) & 1) == f && spt[i][0] > query(i + 1 + f, N)) ans += dp[i][f][l];
            }
        }
    }
    cout << ans << "\n";

    for (int i = 1; i <= N; i++)
        for (int f = 0; f < 2; f++) 
            for (int l = 0; l < 2; l++) dp[i][f][l] = 0;
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
5
2 2 1
3 2 1 3
5 3 1 4 5 2
10 1 2 3 4 5 6 7 8 9 10
15 5 7 6 12 2 13 10 1 11 4 3 9 14 15 8

1
5
3 1 4 5 2
*/