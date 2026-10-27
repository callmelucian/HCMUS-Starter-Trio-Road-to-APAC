#include <bits/stdc++.h>
using namespace std;

#define all(v) begin(v), end(v)
#define compact(v) v.erase(unique(all(v)), end(v))
#define sz(v) (int)v.size()
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

#ifdef LOCAL
    #include "debug.hpp"
#else 
    #define dbg(...) ((void)0)
#endif //LOCAL

const int MAX = 1e5 + 5;
const int MAXQ = MAX * 10;

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
    mint& operator *= (const mint& o){
        v = 1LL * v * o.v % mod;
        return *this;
    }
    mint power(ll n) const {
        mint res(1), bs = *this;
        for(; n > 0; n /= 2, bs *= bs){
            if(n & 1) res *= bs;
        }
        return res;
    }

    mint inv() const {
        return power(mod - 2);
    }
    mint& operator /= (const mint& o){
        return *this *= o.inv();
    }
    friend mint operator + (mint a, const mint& b){ return a += b; }
    friend mint operator - (mint a, const mint& b){ return a -= b; }
    friend mint operator * (mint a, const mint& b){ return a *= b; }
    friend mint operator / (mint a, const mint& b){ return a /= b; }
    friend ostream& operator << (ostream& op, const mint& o){ return op << o.v; }
};

int N, Q;
array<mint, 320> dp[MAX];
mint ans[MAXQ];
string S;

int state1(int start, int len){ // 0 : open, 1 : close length 1 -> 40
    return start * 40 + (len - 1);
}

int state2(int start, int len, int t){ //t = 0 : constant, 1 : multiplied l, 2 : multiplied r, 3 : multiplied both
    int n = state1(start, len);
    return n + t * 80;
}

void dnc(int l, int r, vector<tuple<int, int, int, int, int>>& queries){
    if(l == r || queries.empty()) return;
    int mid = l + r >> 1;

    dp[mid].fill(0);
    for(int mask = 0; mask < 4; ++mask){
        mint w = 1;
        if(mask & 1) w *= mid;
        if(mask & 2) w *= mid;
        dp[mid][state2(S[mid], 1, mask)] = w;
    }

    for(int i = mid - 1; i >= l; --i){
        dp[i] = dp[i + 1];
        for(int mask = 0; mask < 4; ++mask){
            mint w = 1;
            if(mask & 1) w *= i;
            if(mask & 2) w *= i;
            dp[i][state2(S[i], 1, mask)] += w;
            if(mask & 1 ^ 1){
                for(int len = 2; len <= 20; ++len){
                //not multiplied l 
                    dp[i][state2(S[i], len, mask)] += dp[i + 1][state2((S[i] + len) & 1, len - 1, mask)];
                    dp[i][state2(S[i], len, mask | 1)] += dp[i + 1][state2((S[i] + len) & 1, len - 1, mask)] * i;
                }
            }
        }
    }

    // fill(dp[mid + 1], dp[mid + 1] + 320, 0);
    dp[mid + 1].fill(0);
    for(int mask = 0; mask < 4; ++mask){
        mint w = 1;
        if(mask & 1) w *= mid + 1;
        if(mask & 2) w *= mid + 1;
        dp[mid + 1][state2(S[mid + 1], 1, mask)] = w;
    }

    for(int i = mid + 2; i <= r; ++i){
        dp[i] = dp[i - 1];
        for(int mask = 0; mask < 4; ++mask){
            mint w = 1;
            if(mask & 1) w *= i;
            if(mask & 2) w *= i;
            dp[i][state2(S[i], 1, mask)] += w;
            if(mask >> 1 & 1 ^ 1){
                for(int len = 2; len <= 20; ++len){
                    //not multiplied r
                    dp[i][state2(S[i], len, mask)] += dp[i + 1][state2((S[i] + len) & 1, len - 1, mask)];
                    dp[i][state2(S[i], len, mask | 2)] += dp[i + 1][state2((S[i] + len) & 1, len - 1, mask)] * i;
                }
            }
        }
    }

    vector<tuple<int, int, int, int, int>> leftQueries, rightQueries;
    for(auto [op, L, R, k, id] : queries){
        if(L <= mid && mid + 1 <= R){
            if(op == 1){

                ans[id] += dp[L][state2(0, 2 * k, 0)];
                ans[id] += dp[R][state2(0, 2 * k, 0)];
                
                for(int s = 1; s < 2 * k; ++s){
                    ans[id] += dp[L][state2(0, s, 0)] * dp[R][state2(s & 1, 2 * k - s, 0)];
                }

            } else{

                array<mint, 4> sum;
                for(int mask = 0; mask < 4; ++mask){
                    sum[mask] += dp[L][state2(0, 2 * k, mask)];
                    sum[mask] += dp[R][state2(0, 2 * k, mask)];
                }

                for(int s = 1; s < 2 * k; ++s){
                    for(int m1 = 0; m1 < 4; ++m1){
                        for(int m2 = 0; m2 < 4; ++m2){
                            if((m1 & m2) == 0){
                                sum[m1 | m2] += dp[L][state2(0, s, m1)] * dp[R][state2(s & 1, 2 * k - s, m2)];
                            }
                        }
                    }
                }

                ans[id] -= sum[0] * mint(L) * mint(R);
                ans[id] -= sum[3];
                ans[id] += sum[1] * mint(R);
                ans[id] += sum[2] * mint(L);
            }

        } else if(R <= mid){
            leftQueries.emplace_back(op, L, R, k, id);
        } else {
            rightQueries.emplace_back(op, L, R, k, id);
        }
    }
    dnc(l, mid, leftQueries);
    dnc(mid + 1, r, rightQueries);
}   

void testcase(){
    cin >> N >> Q >> S;
    for(int i = 0; i < N; ++i){
        if(S[i] == '(') S[i] = 0;
        else S[i] = 1;
    }
    vector<tuple<int, int, int, int, int>> queries;
    for(int i = 0; i < Q; ++i){
        int op, l, r, k;
        cin >> op >> l >> r >> k;
        --l, --r;
        if(l == r){
            ans[i] = 0;
            continue;
        }
        queries.emplace_back(op, l, r, k, i);
    }

    dnc(0, N - 1, queries);
    for(int i = 0; i < Q; ++i) cout << ans[i] << '\n';
}
int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t = 1;
    // cin >> t;
    while(t--){
        testcase();
    }
    return 0;
}