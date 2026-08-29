#include <bits/stdc++.h>
using namespace std;

#define all(v) begin(v), end(v)
#define rall(v) rbegin(v), rend(v)
#define sz(v) (int)v.size()
#define pb push_back
#define eb emplace_back
#define compact(v) v.erase(unique(all(v)), end(v))
template<class T> bool minimize(T& a, const T& b){ return a > b ? a = b, 1 : 0; }
template<class T> bool maximize(T& a, const T& b){ return a < b ? a = b, 1 : 0; }
using ll = long long;
using db = double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#ifdef LOCAL 
    #include "debug.hpp"
#else 
    #define dbg(...) ((36))
#endif //LOCAL

#define ASSERT(...) ((36))

int ceilLog(int N){
    int k = 0;
    while((1 << k) < N) ++k;
    return k;
}

vector<string> encode(vector<string> A){
    int N = sz(A);
    vector<vector<int>> adj(N + 1, vector<int>(N + 1));
    for(int i = 0; i < N; ++i){
        for(int j = 0; j < N; ++j){
            adj[i + 1][j + 1] = (A[i][j] == '1');
        }
    }

    int L = ceilLog(N);
    int M = N + L + 3;
    vector<vector<int>> ans(M + 1, vector<int>(M + 1));
    for(int i = 1; i <= N; ++i){
        for(int j = 1; j <= N; ++j){
            ans[i][j] = adj[i][j];
        }
    }
    
    auto addEdge = [&](int i, int j){
        ans[i][j] = 1;
        ans[j][i] = 1;
    };
    for(int i = 1; i <= L - 1; ++i){
        addEdge(N + i, N + i + 1);
    }

    for(int i = 1; i <= N + L; ++i) {
        addEdge(i, N + L + 1);
    }
    addEdge(N + L + 1, N + L + 3);
    for(int i = N + 1; i <= N + L; ++i){
        addEdge(i, N + L + 2);
    }
    addEdge(N + L + 3, N + L + 2);
    for(int i = 1; i <= N + 1; ++i) addEdge(i, N + L + 3);

    for(int i = 1; i <= N; ++i){
        for(int j = 0; j < L; ++j){
            if(i >> j & 1){
                addEdge(i, N + j + 1);
            }
        }
    }
    vector<string> result(M);
    for(int i = 0; i < M; ++i){
        for(int j = 0; j < M; ++j){
            result[i].pb('0' + ans[i + 1][j + 1]);
        }
    }
    return result;
}

vector<string> decode(vector<string> A){
    int M = sz(A);
    vector<int> deg(M + 1);
    vector<vector<int>> adj(M + 1, vector<int>(M + 1));
    for(int i = 0; i < M; ++i){
        for(int j = 0; j < M; ++j){
            adj[i + 1][j + 1] = (A[i][j] == '1');
            if(i < j){
            deg[i + 1] += adj[i + 1][j + 1];
            deg[j + 1] += adj[i + 1][j + 1];
            }
        }
    }
    dbg(deg);
    
    int N = -1, L = -1;
    for(int i = 3; i <= M; ++i){
        if(i + ceilLog(i) + 3 == M){
            N = i;
            L = ceilLog(i);
            break;
        }
    }
    dbg(N, L);
    ASSERT(N != -1);
    int S1 = max_element(all(deg)) - begin(deg);
    int S2 = -1, S3 = -1;
    for(int i = 1; i <= M; ++i) if(i != S1 && adj[S1][i] == 0){
        S2 = i;
    }
    vector<int> need(M + 1, 0);
    for(int i = 1; i <= M; ++i) if(i != S1 && i != S2 && !adj[S2][i]){
        need[i] = true;
        dbg(i);
    }
    vector<int> mustHave;
    for(int i = 1; i <= M; ++i) if(need[i] && i != S1 && i != S2){
        mustHave.pb(i);
    }
    dbg(mustHave);
    dbg(adj[S1]);
    for(int i = 1; i <= M; ++i) if(adj[S2][i]){
        int ok = true;
        for(int j : mustHave){
            if(!adj[i][j]){
                ok = false;
            }
        }
        if(ok){
            S3 = i;
            break;
        }
    }
    dbg(S1, S2, S3);
    vector<int> inChain, checker(M + 1);
    
    for(int i = 1; i <= M; ++i) if(i != S1 && i != S2 && i != S3 && adj[S2][i] && i != S3){
        inChain.pb(i);
        checker[i] = 1;
    }  
    dbg(inChain);
    int beginChain = -1;

    for(int i = 1; i <= M; ++i) if(i != S1 && i != S2 && i != S3 && adj[S2][i] && adj[S3][i]){
        beginChain = i;
    }
    ASSERT(sz(inChain) == L);
    ASSERT(beginChain != -1);
    int u = beginChain;
    vector<int> bitHolder(M + 1, -1);
    for(int i = 0; i < L; ++i){
        bitHolder[u] = i;
        dbg(i, u);
        for(int j = 1; j <= M; ++j) if(adj[u][j] && checker[j] && bitHolder[j] == -1){
            u = j;
            break;
        }
    }

    vector<int> original(M + 1, -1);
    for(int i = 1; i <= M; ++i) {
        if(i == S1 || i == S2 || i == S3 || bitHolder[i] != -1) continue;
        original[i] = 0;
        for(int j : inChain){
            if(adj[i][j]){
                original[i] |= 1 << bitHolder[j];
            }
        }
        dbg(i, original[i]);
    }

    vector<string> ans(N, string(N, '0'));
    for(int i = 1; i <= M; ++i){
        for(int j = 1; j <= M; ++j){
            if(adj[i][j] && original[i] != -1 && original[j] != -1){
                dbg(original[i], original[j]);
                ans[original[i] - 1][original[j] - 1] = '1';
            }
        }
    }
    return ans;
}

void testcase(){
    int N1, N2;
    cin >> N1 >> N2;
    vector<string> A(N1);
    for(int i = 0; i < N1; ++i){
        cin >> A[i];
    }

    if(N1 < N2){
        vector<string> ans = encode(A);
        for(int i = 0; i < N2; ++i){
            cout << ans[i] << '\n';
        }
        for(int i = 0; i < N2; ++i){
            for(int j = i + 1; j < N2; ++j){
                if(ans[i][j] == '1'){
                    dbg(i + 1, j + 1);
                }
            }
        }
    } else{
        vector<string> ans = decode(A);
        for(int i = 0; i < N2; ++i){
            cout << ans[i] << '\n';
        }
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
10
386413329 88494216 245947398 316438989 192751270 204627269 65749456 3938400 150458676 345180997
*/