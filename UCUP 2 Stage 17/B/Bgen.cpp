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

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using tpl = tuple<int,int,int>;

template<class T> bool minimize(T& a, const T& b){  return (a > b ? a = b, 1 : 0); }
template<class T> bool maximize(T& a, const T& b){  return (a < b ? a = b, 1 : 0); }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int rint(int l, int r){ return uniform_int_distribution<int>(l, r)(rng); }
int wrint(int l, int r, int w){
    if(w > 0){
        int mx = rint(l, r);
        for(int i = 0; i < w; ++i) maximize(mx, rint(l, r)); 
        return mx;
    } else{
        int mn = rint(l, r);
        for(int i = 0; i < -w; ++i) minimize(mn, rint(l, r));
        return mn;
    }

}

vector<pii> genTree(int n){
    int seed = rint(-(n / 2), +(n / 2));
    vector<int> p(n);
    iota(all(p), 0);
    shuffle(all(p), rng);
    vector<pii> e;
    for(int i = 1; i < n; ++i){
        int u = p[i], v = p[wrint(0, i - 1, seed)];
        if(rint(0, 1)) swap(u, v);
        e.emplace_back(u, v);
    }
    shuffle(all(e), rng);
    return e;
}

void testcase() {
    ofstream output("B.in");
    int n = rint(2, 100), k = rint(1, n);
    output << 1 << '\n';
    output << n << ' ' << k << '\n';
    for(auto [u, v] : genTree(n)) output << u + 1 << ' ' << v + 1 << '\n';
}

int main() {
    while(true){
        testcase();
        int code = system("B.exe < B.in");
        if(code != 0){
            cout << "failed\n";
            break;
        } else{
            cerr << "ok\n";
        }
    }

    return 0;
}