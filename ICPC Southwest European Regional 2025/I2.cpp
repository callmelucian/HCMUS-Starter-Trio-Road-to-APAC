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
        cout << p[i] << " \n"[i == N];
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
    dbg(u, v, x);
    return x;
}

}

void testcase(){
    int N;
    cin >> N;
    vector<int> g(N + 1);
    vector<vector<int>> done(N + 1, vector<int>(N + 1));
    vector<vector<int>> ans(N + 1, vector<int>(N + 1));
    
    vector<pii> intervals;
    for(int i = 1; i <= N; ++i){
        for(int j = i; j <= N; ++j){
            intervals.eb(i, j);
        }
    }
    sort(all(intervals), [&](pii a, pii b){ return a.second - a.first > b.second - b.first; });

    bool wtf = false;
    for(auto [l, r] : intervals){
        dbg(r - l + 1, wtf);
        if(!done[l][r]){
            done[l][r] = 1;
            ans[l][r] = Interactor::ask(l, r);
        }

        for(int i = l - 1; i >= 1; --i){
            if(done[i][r] && ans[i][r] > ans[l][r]){
                done[i][l - 1] = 1;
                ans[i][l - 1] = ans[i][r];
                assert(false);
            }
        }

        for(int i = r + 1; i <= N; ++i){
            if(done[l][i] && ans[l][i] > ans[l][r]){
                done[r + 1][i] = 1;
                ans[r + 1][i] = ans[l][i];
                assert(false);
            }
        }
    }
    cout << "!\n";
    for(int i = 1; i <= N; ++i){
        for(int j = i; j <= N; ++j){
            cout << ans[i][j] << ' ';
        }
        cout << '\n';
    }
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