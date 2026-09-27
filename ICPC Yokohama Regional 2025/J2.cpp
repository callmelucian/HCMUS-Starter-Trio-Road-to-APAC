#include <bits/stdc++.h>
#ifdef LOCAL
    #include "debug.hpp"
#else 
    #define dbg(...)
#endif // LOCAL

using namespace std;

#define all(v) begin(v), end(v)
#define rall(v) rbegin(v), rend(v)
#define compact(v) v.erase(unique(all(v)), end(v))
#define sz(v) (int)v.size()
#define eb emplace_back
#define pb push_back
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using tpl = tuple<int,int,int>;

template<class T> bool minimize (T& a, const T& b) { return (a > b ? a = b, 1 : 0); }
template<class T> bool maximize (T& a, const T& b) { return (a < b ? a = b, 1 : 0); }

vector<vector<tuple<int, int, int>>> tps;

void gen(){ //I, C, C, P
    vector<int> p = {0, 1, 1, 2};
    vector<pii> d = {{0, 0}, {0, 1}, {1, 0}, {1, 1}};
    do{
        vector<tuple<int, int, int>> cur;
        for(int i = 0; i < 4; ++i){
            auto [dx, dy] = d[i];
            cur.eb(dx, dy, p[i]);
        }
        tps.pb(cur);
        next_permutation(all(d));
    } while(next_permutation(all(p)));
}

bool ok(int i, int j){
    return (i == -1 || (i == j));
}

int popcount(int mask){
    return __builtin_popcount(mask);
}

int getBit(int mask){
    return 31 - __builtin_clz(mask);
}

int checkCnt(int v, int n, int c){
    if(v == 1) return c * 2 == n;
    else return c == n;
}

void testcase() {
    int N, M;
    cin >> N >> M;
    gen();
    dbg(tps);
    vector<vector<int>> A(N, vector<int>(M));
    for(int i = 0; i < N; ++i){
        for(int j = 0; j < M; ++j){
            char c; cin >> c;
            A[i][j] = (c == 'I' ? 0 : (c == 'C' ? 1 : (c == 'P' ? 2 : -1)));
            dbg(A[i][j]);
        }
    }
    vector<vector<int>> numBlock(N, vector<int>(M));
    vector<vector<array<int, 3>>> ways(N, vector<array<int, 3>>(M, {0, 0, 0}));


    auto getMask = [&](int i, int j){
        int msk = 0;
        for(int k = 0; k < 3; ++k) if(check(k, ways[i][j][k], numBlock[i][j])){
            msk |= (1 << k);
        }
        return msk;
    };

    vector<vector<vector<int>>> memo(N, vector<vector<int>>(M, vector<int>(sz(tps))));
    for(int i = 0; i < N - 1; ++i){
        for(int j = 0; j < M - 1; ++j){
            ++numBlock[i][j];
            ++numBlock[i][j + 1];
            ++numBlock[i + 1][j];
            ++numBlock[i + 1][j + 1];
            
            for(int cur = 0; cur < sz(tps); ++cur){
                bool check = true;
                for(auto [dx, dy, c] : tps[cur]){
                    if(ok(A[i + dx][j + dy], c));
                    else{
                        check = false;
                        break;
                    }
                }
                if(!check) continue;
                dbg(i, j, cur);
                memo[i][j][cur] = 1;

                for(auto [dx, dy, c] : tps[cur]){
                    dbg(i + dx, j + dy, c);
                    ++ways[i + dx][j + dy][c];
                }
            }
        }
    }

    function<void(int, int)> updateBlock = [&](int i, int j){
        for(int k = 0; k < sz(tps); ++k) if(memo[i][j][k]){
            if(memo[i][j][k]){
                for(auto [dx, dy, c] : tps[k]){
                    --ways[i + dx][j + dy][c];
                }
                memo[i][j][k] = 0;
            }
            memo[i][j][k] = 1;
            for(auto [dx, dy, c] : tps[k]){
                if(ok(A[i + dx][j + dy], c));
                else{
                    memo[i][j][k] = 0;
                    break;
                }
            }
            if(memo[i][j][k]){
                for(auto [dx, dy, c] : tps[k]){
                    ++ways[i + dx][j + dy][c];
                }
            }
        }
    };

    auto canDirect = [&](int i, int j){
        for(int x = 0; x < 2; ++x){
            for(int y = 0; y < 2; ++y){
                if(A[i + x][j + y] == -1 && popcount(getMask(i + x, j + y)) == 1){
                    return true;
                }       
            }
        }
        return false;
    };

    vector<vector<int>> vis(N - 1, vector<int>(M - 1));

    function<void(int, int)> go = [&](int i, int j){
        dbg(i, j);
        vis[i][j] = 1;
        for(int x = 0; x < 2; ++x){
            for(int y = 0; y < 2; ++y){
                int mask = getMask(i + x, j + y);
                if(A[i + x][j + y] == -1 && popcount(mask == 1)){
                    A[i + x][j + y] = getBit(mask);
                }
            }
        }
        for(int p = -1; p <= 1; ++p){
            for(int q = -1; q <= 1; ++q){
                if(0 <= i + p && i + p + 1 < N && 0 <= j + q && j + q + 1 < M){
                    updateBlock(i + p, j + q);
                }
            }
        }

        for(int p = -1; p <= 1; ++p){
            for(int q = -1; q <= 1; ++q){
                if(0 <= i + p && i + p + 1 < N && 0 <= j + q && j + q + 1 < M){
                    if(!vis[i + p][j + q] && canDirect(i + p, j + q)){
                        go(i, j);
                    }
                }
            }
        }
    };

    for(int i = 0; i < N; ++i){
        for(int j = 0; j < M; ++j){
            dbg(i, j, getMask(i, j), numBlock[i][j]);
            for(int k = 0; k < 4; ++k){
                dbg(i, j, k, ways[i][j][k]);
            }
            if(popcount(getMask(i, j)) == 0){
                cout << "no\n";
                return;
            }
        }
    }
    for(int i = 0; i < N - 1; ++i){
        for(int j = 0; j < M - 1; ++j) {
            if(!vis[i][j] && canDirect(i, j) == 1){
                go(i, j);
            }
        }
    }

    for(int i = 0; i < N; ++i){
        for(int j = 0; j < M; ++j) if(A[i][j] == -1){
            int base = getMask(i, j);
            int v = getBit(base);
            A[i][j] = v;
            dbg(i, j, base, v);
            for(int p = -1; p <= 1; ++p){
                for(int q = -1; q <= 1; ++q){
                    if(0 <= i + p && i + p + 1 < N && 0 <= j + q && j + q + 1 < M){
                        go(i + p, j + q);
                    }
                }
            }
        }
    }
    cout << "yes\n";
    char ch[3] = {'I', 'C', 'P'};
    for(int i = 0; i < N; ++i){
        for(int j = 0; j < M; ++j){
            cout << ch[A[i][j]] << " \n"[j == M - 1];
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
  
    int TC = 1;
    cin >> TC;
    while (TC--) {
        testcase();
    }

    return 0;
}