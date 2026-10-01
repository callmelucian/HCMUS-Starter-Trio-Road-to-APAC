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

namespace Interactor{
const int MAX = 105;
int N, A[MAX], p[MAX];
double sumCost;

int f(int x){
    return (x == 0 ? -1 : 31 - __builtin_clz(x));
}

void preprocess(){
    sumCost = 0.0;
    ifstream in("I.in");
    in >> N;
    for(int i = 1; i <= N; ++i){
        in >> A[i];
        p[i] = p[i - 1] ^ A[i];
    }

    int bad = 0;
    vector<int> cnt(100), g(N + 1);
    for(int u = 1; u <= N; ++u) if(u == 1){
        for(int v = u; v <= N; ++v){
            int x = f(p[v] ^ p[u - 1]);
            if(x == -1) ++bad;
            else ++cnt[x]; 
            g[v] = x;
            cout << g[v] << ' ';
        }
    }
    int tot = N * (N + 1) / 2;
    int know = 0;
    vector<vector<int>> done(N + 1, vector<int>(N + 1));
    for(int i = 1; i <= N; ++i) done[1][i] = 1;
    for(int i = 1; i <= N; ++i){
        for(int j = i + 1; j <= N; ++j){
            if(g[i] < g[j]){
                done[i + 1][j] = 1;
                //f[i + 1][j] = 
            }
        }
    }

    for(int s = 2; s <= N; ++s){
        for(int t = s; t <= N; ++t){
            g[t] = f(p[t] ^ p[s - 1]);
            done[s][t] = 1;
        }

        for(int u = s; u <= N; ++u){
            for(int v = u + 1; v <= N; ++v){
                if(g[u] < g[v]){
                    done[u + 1][v] = 1;
                }   
            }
        }

        int win = 0;
        for(int i = 1; i <= N; ++i){
            for(int j = i; j <= N; ++j){
                win += done[i][j];
            }
        }
        dbg(s, win);
    }
    dbg(tot, know);
    double q = 0;
    for(int i = 1; i <= N; ++i){
        q += log(i) / log(2.718);
    }
    dbg(q);
    dbg(bad);
    for(int i = 0; i < 100; ++i) if(cnt[i]){
        dbg(i, cnt[i]);
    }
}

int ask(int u, int v){
    sumCost += 1.0 / (v - u + 1);
    if(sumCost >= 35.0){
        cerr << "exceeded ask sum !\n";
        exit(1);
    }
    cout << "? " << u << ' ' << v << endl;
    int x = f(p[v] ^ p[u - 1]);
    return x;
}

}

void testcase(){
    Interactor::preprocess();
    int N = 100;

    // vector<vector<int>> f(N + 1, vector<int>(N + 1, -2));
    // for(int i = 1; i <= N; ++i){
    //     for(int j = i + 49; j <= N; ++j){
    //         f[i][j] = Interactor::ask(i, j);
    //         dbg(i, j, f[i][j]);
    //     }
    // }

}

void brute(){
    int N = 100;
    double sum = 0;

    for(int len = 1; len <= N; ++len){
        sum = 0.0;
        for(int i = 1; i <= N; ++i){
            for(int j = i + len; j <= N; ++j){
                sum += 1.0 / (j - i + 1);
            }
        }
        if(sum <= 35){
            cerr << setprecision(10);
            dbg(len, sum);
        }
    }
    exit(0);
}

int main(){
    // brute();
    int tests = 1;
    // cin >> tests;
    while(tests--){
        testcase();
    }
    return 0;  
}