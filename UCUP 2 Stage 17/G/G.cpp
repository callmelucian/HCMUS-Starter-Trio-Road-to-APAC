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


struct DSU {
    vector<int> lab;
    vector<bool> color, toggleAll;
    vector<vector<int>> comp;
    bool isValid;

    DSU (int sz) : lab(sz + 1, -1), color(sz + 1), toggleAll(sz + 1), comp(sz + 1), isValid(true) {
        for (int i = 0; i <= sz; i++) comp[i].push_back(i);
    }

    int getRoot (int u) {
        if (lab[u] < 0) return u;
        return getRoot(lab[u]);
    }

    int getColor (int u) {
        return color[u] ^ toggleAll[getRoot(u)];
    }

    bool unite (int u, int v, bool isDifferent) {
        dbg("condition", u, v, isDifferent);
        int a = getRoot(u), b = getRoot(v);
        if (a == b) {
            if (isDifferent != (getColor(u) != getColor(v))) isValid = false;
            return isValid;
        }
        if (-lab[a] < -lab[b]) swap(a, b), swap(u, v);
        if (isDifferent != (getColor(u) != getColor(v)))
            toggleAll[a] = !toggleAll[a];
        if (toggleAll[b] != toggleAll[a]) {
            for (int x : comp[b]) {
                color[x] = !color[x];
                comp[a].push_back(x);
            }
        }
        lab[a] += lab[b], lab[b] = a;
        return isValid;
    }
};

const int mod = 1e9 + 7;

int power(int a, int b){
    int c = 1;
    for(; b > 0; b >>= 1, a = 1LL * a * a % mod){
        if(b & 1) c = 1LL * c * a % mod;
    }
    return c;
}

void testcase() {
    int N, M;
    cin >> N >> M;
    vector<string> A(N);
    for(int i = 0; i < N; ++i) cin >> A[i];

    int bad = (M & 1 ? (M / 2) : -1);
    int cntBad = 0;
    vector<vector<pair<int, int>>> adj(N);
    vector<int> last(M, -1), cnt(M), fst(M, -1), sec(M, -1);
    for(int i = 0; i < N; ++i){
        for(int j = 0; j < M; ++j) if(A[i][j] == '1'){
            if(j == bad){
                ++cntBad;
                if(cntBad >= 2){
                    cout << 0 << '\n';
                    return;
                }
            } else{
                ++cnt[j];
                if(cnt[j] >= 3){
                    cout << 0 << '\n';
                    return;
                }

                if(cnt[j] == 1){
                    fst[j] = i;
                } else{
                    sec[j] = i;
                }
            }
        }
        for(int j = 0; j < M; ++j) if(A[i][j] == '1'){
            last[j] = i;
        }
    }

    for(int i = 0; i < M; ++i){
        if(i == bad || fst[i] == -1) continue;

        if(sec[i] != -1){
            int u = fst[i], v = sec[i];
            adj[u].emplace_back(v, 1);
            adj[v].emplace_back(u, 1);
        }

        int j = M - i - 1;
        if(i < j){
            if(fst[j] != -1){
                int u = fst[i], v = fst[j];
                adj[u].emplace_back(v, 0);
                adj[v].emplace_back(u, 0);
                if(sec[i] != -1){
                    u = sec[i];
                    adj[u].emplace_back(v, 0);
                    adj[v].emplace_back(u, 0);    
                }
            }
            if(sec[j] != -1){
                int u = fst[i], v = sec[j];
                adj[u].emplace_back(v, 0);
                adj[v].emplace_back(u, 0);
                if(sec[i] != -1){
                    u = sec[i];
                    adj[u].emplace_back(v, 0);
                    adj[v].emplace_back(u, 0);    
                }
            }
        }
    }

    int cc = 0;
    queue<int> q;
    vector<int> c(N, -1);
    for(int i = 0; i < N; ++i) if(c[i] == -1){
        c[i] = 0;
        q.push(i);
        ++cc;
        while(!q.empty()){
            int u = q.front(); q.pop();
            for(auto [v, w] : adj[u]){
                if(c[v] == -1){
                    c[v] = c[u] ^ w;
                    q.push(v);
                } else{
                    if(c[u] ^ w != c[v]){
                        cout << 0 << '\n';
                        return;
                    }
                }
            }
        }
    }
    cout << power(2, cc) << '\n';
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