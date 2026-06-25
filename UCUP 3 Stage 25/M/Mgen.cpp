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
int rint(int l, int r){
    return uniform_int_distribution<int>(l, r)(rng);
}

void testcase() {
    ofstream output("M.in");
    int t = rint(1, 10);
    output << t << '\n';
    while(t--){
        int n = rint(1, 8), k = rint(1, 1e3);
        int odd = rint(0, 1);
        output << n << ' ' << k << '\n';
        for(int i = 0; i < n; ++i){
            output << 2 * rint(1, 5) + odd << " \n"[i == n - 1];
        }
    }
}

int main() {
    while(true){
        testcase();
        system("M.exe < M.in > M.out");
        system("Mbrute.exe < M.in > M.ans");
        if(system("fc /w M.out M.ans") != 0){
            cout << "Failed\n";
            return 0;
        }
    }

    return 0;
}