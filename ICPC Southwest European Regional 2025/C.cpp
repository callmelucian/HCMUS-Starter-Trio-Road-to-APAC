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

void testcase(){
    int N, M;
    cin >> N >> M;
    
    vector<int> nxt((N * M) / 2 + 1);
    vector<vector<int>> A(N, vector<int>(M));
    for(int i = 0; i < N; ++i){
        for(int j = 0; j < M; ++j){
            cin >> A[i][j];
            if(j > 0){
                nxt[A[i][j - 1]] = A[i][j];
            }
        }
    }

    if(M == 1){
        for(int i = 1; i <= N * M / 2; ++i){
            cout << i << ' ';
        }
        cout << '\n';
        return;
    }

    if((N % 2 == 0)){
        sort(all(A));
        
        for(int i = 0; i < N; i += 2){
            for(int j = 0; j < M; ++j){
                cout << A[i][j] << ' ';
            }
        }
        cout << '\n';
        return;
    }

    for(int i = 1; i <= N * M / 2; ++i){
        dbg(sz(nxt), i, nxt[i]);
    }

    vector<int> p;
    int u = A[0][0];
    p.pb(u);
    while(sz(p) < N * M / 2){
        u = nxt[u];
        p.pb(u);
    }
    for(auto u : p) cout << u << ' ';
    cout << '\n';
    
    vector<vector<int>> B = A;
    sort(all(B));
    
    vector<vector<int>> C(N);
    int t = 0;
    for(int i = 0; i < N; ++i){
        for(int j = 0; j < M; ++j){
            C[i].pb(p[t++]);
            t %= sz(p);
        }
    }
    sort(all(C));
    if(B != C){
        cout << "failed\n";
        exit(0);
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int tests = 1;
    cin >> tests;
    while(tests--){
        // cerr << "solving!\n";
        testcase();
    }
    return 0;  
}