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

const int mod = 1e9 + 7;
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
    mint& operator *= (const mint& o){
        v = 1LL * v * o.v % mod;
        return *this;
    }
    friend mint operator + (mint a, const mint& b){ return a += b; }
    friend mint operator - (mint a, const mint& b){ return a -= b; }
    friend mint operator * (mint a, const mint& b){ return a *= b; }
    friend bool operator == (const mint& a, const mint& b){ return a.v == b.v; }
    friend bool operator != (const mint& a, const mint& b){ return a.v != b.v; }
    friend ostream& operator << (ostream& op, const mint& o){ return op << o.v; }
};

const mint BASE = 37;
vector<mint> getHash(string& s, int block){
    vector<mint> res;
    for(int l = 0; l < sz(s); l += block){
        int r = min(sz(s), l + block);
        mint h = 0;
        for(int i = l; i < r; ++i){
            h = h * BASE + (s[i] - 'a' + 1);
        }
        res.pb(h);
    }
    return res;
}

void testcase() {
    int N, Q, M, K;
    cin >> N >> Q >> M >> K;
    vector<string> S(N);
    vector<vector<mint>> hashBlocks(N);
    int blockSize = sqrt(M);
    for(int i = 0; i < N; ++i){
        cin >> S[i];
        hashBlocks[i] = getHash(S[i], blockSize);
    }
    while(Q--){
        string T;
        cin >> T;
        vector<mint> curHash = getHash(T, blockSize);
        int ans = 0;
        for(int i = 0; i < N; ++i){
            dbg(curHash, hashBlocks[i]);
            int dist = 0;
            for(int j = 0; j < sz(hashBlocks[i]); ++j){
                if(hashBlocks[i][j] != curHash[j]){
                    int l = j * blockSize, r = min(M, l + blockSize);
                    for(int t = l; t < r; ++t){
                        // dbg(S[i][j], T[j]);
                        dist += S[i][t] != T[t];
                    }
                }
                if(dist > K) break;
            }
            ans += dist <= K;
            dbg(dist);
        }
        cout << ans << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    int tests = 1;
    // cin >> tests;
    while (tests--) {
        testcase();
    }

    return 0;
}