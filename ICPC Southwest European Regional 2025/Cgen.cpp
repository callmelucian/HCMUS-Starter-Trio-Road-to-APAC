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

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int randint(int l, int r){
    return uniform_int_distribution<int>(l, r)(rng);
}

void testcase(){    
    ofstream output("C.in");
    int t = 5;
    output << t << '\n';
    while(t--){
        int n = randint(1, 10), m = randint(1, 10);
        while((n * m) & 1){
            n = randint(1, 10);
            m = randint(1, 10);
        }

        output << n << ' ' << m << '\n';
        vector<int> p(n * m / 2);
        iota(all(p), 1);
        shuffle(all(p), rng);
        p.insert(end(p), all(p));
        vector<vector<int>> A(n);
        for(int i = 0; i < n; ++i){
            for(int j = 0; j < m; ++j){
                A[i].pb(p[i * m + j]);
            }
        }
        shuffle(all(A), rng);
        for(int i = 0; i < n; ++i){
            for(int j = 0; j < m; ++j){
                output << A[i][j] << " \n"[j == m - 1];
            }
        }
        output << '\n';
    }
}

int main(){
    while(true){
        testcase();
        int code = system("./C < C.in > C.out");
        if(code != 0){
            cout << "Failed\n";
            return 0;
        }
    }
    return 0;  
}