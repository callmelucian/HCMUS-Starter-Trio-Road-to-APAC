#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using tpl = tuple<int,int,int>;

#define all(v) begin(v), end(v)
#define sz(v) (int)v.size()
#define compact(v) v.erase(unique(all(v)), end(v))

template<class T> bool maximize (T &a, const T &b) { return b > a ? a = b, true : false; }
template<class T> bool minimize (T &a, const T &b) { return b < a ? a = b, true : false; }

#ifdef LOCAL
    #include "debug.hpp"
#else 
    #define dbg(...) ((void)0)
#endif //LOCAL

int popcount(int x){
    return __builtin_popcount(x);
}

void testcase(){
    int N, K;
    cin >> N >> K;
    string S[3];
    for(int i = 0; i < 3; ++i){
        cin >> S[i];
        S[i] = '#' + S[i];
    }

    vector<vector<int>> masks(N + 1);
    for(int i = 0; i <= N; ++i){
        for(int mask = 0; mask < (1 << 3); ++mask){
            bool ok = true;
            for(int j = 0; j < 3; ++j) if(mask >> j & 1){
                if(S[j][i] == '#'){
                    ok = false;
                    break;
                }    
            }
            if(ok) masks[i].emplace_back(mask);
        }
    }

    vector<int> pre1(1 << 3, -1);
    for(int mask = 0; mask < 8; ++mask){
        int last = -1;
        for(int i = 0; i < 3; ++i) if(mask >> i & 1){
            if(last != -1){
                if(pre1[mask] == -1) pre1[mask] = 1e9;
                minimize(pre1[mask], (i - last) * (i - last));
            }
            last = i;
        }
    }
    auto checkIn = [&](int mask, int d){
        if(pre1[mask] >= 0 && pre1[mask] < d) return false;
        return true;
    };


    vector<vector<int>> precalc(8, vector<int>(8, -1));
    for(int m1 = 0; m1 < 8; ++m1){
        for(int m2 = 0; m2 < 8; ++m2){
            for(int i = 0; i < 3; ++i) if(m1 >> i & 1){
                for(int j = 0; j < 3; ++j) if(m2 >> j & 1){
                    if(precalc[m1][m2] == -1) precalc[m1][m2] = 1e9;
                    minimize(precalc[m1][m2], abs(i - j) * abs(i - j));
                }
            }
        }
    }

    auto checkTwo = [&](int m1, int m2, int gap, int d){
        if(precalc[m1][m2] >= 0 && precalc[m1][m2] + gap * gap < d) return false;
        return true;
    };

    auto merge = [&](int maskPre, int maskCur){
        return maskCur + 8 * maskPre;
    };

    auto check = [&](int D){
        // dbg(D);
        vector<vector<int>> dp(N + 1, vector<int>(1 << 6, -1e9));
        for(int m : masks[1]){
            if(checkIn(m, D)) dp[1][merge(0, m)] = popcount(m);
        }    

        for(int i = 2; i <= N; ++i){
            //case i - 1
            // dbg(i);
            for(auto mask : masks[i]){
                if(!mask || !checkIn(mask, D)) continue;
                maximize(dp[i][merge(0, mask)], popcount(mask));

                for(int j = i - 1; j >= 1; --j){
                    if(j == i - 1){
                        for(auto maskPre : masks[j]){
                            if(!checkIn(maskPre, D)) continue;
                            for(auto maskPrePre : masks[j - 1]){
                                if(!checkIn(maskPrePre, D)) continue;

                                if(checkTwo(maskPre, mask, 1, D) && checkTwo(maskPrePre, mask, 2, D)){
                                    maximize(dp[i][merge(maskPre, mask)], dp[i - 1][merge(maskPrePre, maskPre)] + popcount(mask));
                                }
                            }
                        }
                    } else{
                        for(auto maskPre : masks[i - 1]){
                            if(!checkIn(maskPre, D)) continue;

                            for(auto maskPrePre : masks[j]){
                                // dbg(i, j, maskPrePre, checkIn(maskPrePre, D));
                                if(!checkIn(maskPrePre, D)) continue;
                                for(auto maskPrePrePre : masks[j - 1]){
                                    if(checkTwo(mask, maskPrePre, i - j, D) &&
                                       checkTwo(mask, maskPrePrePre, i - j + 1, D) &&
                                       checkTwo(maskPre, maskPrePre, i - j - 1, D) &&
                                       checkTwo(maskPre, maskPrePrePre, i - j, D))
                                        maximize(dp[i][merge(maskPre, mask)], dp[j][merge(maskPrePrePre, maskPrePre)] + popcount(mask));
                                }
                            }
                        }
                    }
                }
            }
        }

        int ans = 0;
        for(int i = 1; i <= N; ++i){
            for(auto m1 : masks[i - 1]){
                for(auto m2 : masks[i]){
                    maximize(ans, dp[i][merge(m1, m2)]);
                }
            }
        }
        return ans;
    };

    // int k = check(20);
    // cout << k << '\n';
    // return;

    int l = 1, r = 1e9, ans = -1;
    while(l <= r){
        int mid = l + r >> 1;
        if(check(mid) >= K) ans = mid, l = mid + 1;
        else r = mid - 1;
    }

    if(ans == -1) cout << -1 << '\n';
    else cout << fixed << setprecision(10) << sqrtl((double)ans) << '\n';
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