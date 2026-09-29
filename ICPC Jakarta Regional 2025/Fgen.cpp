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
using pii = pair<int, int>;
using pll = pair<ll, ll>;

#ifdef LOCAL 
    #include "debug.hpp"
#else
    #define dbg(...) (void(0))
#endif //LOCAL

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int randint(int l, int r){ return uniform_int_distribution<int>(l, r)(rng); }

void testcase(){
    ofstream output("F.in");
    int n = 300;
    int maxEdges = min(n * (n - 1) / 2, 200000);
    int m = randint(maxEdges - 1000, maxEdges);
    vector<pii> edges;
    for(int i = 1; i <= n; ++i){
        for(int j = i + 1; j <= n; ++j){
            edges.eb(i, j);
        }
    }
    shuffle(all(edges), rng);
    output << n << ' ' << m << '\n';
    for(int i = 0; i < m; ++i){
        auto [u, v] = edges[i];
        output << u << ' ' << v << '\n';
    }
}

int main(){
    while(true){
        testcase();
        int code = system("./F < F.in > F.out");
        if(code != 0){
            cout << "Failed\n";
            return 0;
        }
    }
    return 0;
}