#include <bits/stdc++.h>
#ifdef LOCAL
    #include "../debug.hpp"
#else 
    #define dbg(...)
#endif // LOCAL

using namespace std;

#define all(v) begin(v), end(v)
#define rall(v) rbegin(v), rend(v)
#define compact(v) v.erase(unique(all(v)), end(v))
#define sz(v) (v).size()
#define pb push_back
#define eb emplace_back

using ll = long long;
using db = double;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using tpl = tuple<int,int,int>;

template<class T> bool minimize(T& a, const T& b){  return (a > b ? a = b, 1 : 0); }
template<class T> bool maximize(T& a, const T& b){  return (a < b ? a = b, 1 : 0); }

void testcase() {
    int N, M, BOUND;
    cin >> N >> M >> BOUND;
    vector<int> p(N * M + 1);
    vector<vector<int>> pos(N);
    for(int i = 1; i <= N * M; ++i){
        cin >> p[i];
        pos[(p[i] - 1) / M].pb(i);
    }

    auto f = [&](int cut){
        dbg(cut);
        for(int k = 0; k < N; ++k){
            dbg(k, pos[k]);
            int st = M;
            for(int j = 0; j < M; ++j){
                if(pos[k][j] > cut){
                    st = j;
                    break;
                }
            }
            if(M - st <= BOUND) return true;
        }
        return false;
    };

    int l = M, r = N * M, ans = -1;
    while(l <= r){
        int mid = l + r >> 1;
        if(f(mid)) ans = mid, r = mid - 1;
        else l = mid + 1;
    }
    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
  
    int TC = 1; cin >> TC;
    while (TC--) {
        testcase();
    }

    return 0;
}