#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
    #include "debug.hpp"
#else
    #define dbg(...) ((void)0)
#endif // LOCAL

#define all(v) begin(v), end(v)
#define compact(v) v.erase(unique(all(v)), end(v))
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

void testcase(){
    int N; cin >> N;

    int m = N % 4;
    if (m == 1) {
        cout << 1 << " " << 2 << " ";
        int k = (2 * N - 2) / 2;
        for (int i = 0, a = -1; i < k; i += 2, a = -a) cout << a << " " << 2 * a << " ";
    }
    else if (m == 3) {
        cout << -2 << " ";
        int k = (2 * N - 2) / 2;
        for (int i = 0; i < k; i += 2) cout << 1 << " " << -2 << " ";
        cout << -2 << " ";
        for (int i = 0, a = 1; i < k; i += 2, a = -a) cout << a << " " << 2 * a << " ";
    }
    else {
        cout << 1 << ' ';
        int x = (N - 1) / 2;
        for(int i = 1; i <= x; ++i) {
            if(i % 2) cout << 2 << ' ' << -1 << ' ';
            else cout << -2 << ' ' << 1 << ' ';
        }
        cout << 1 << ' ' << 1 << ' ';
        for(int i = 1; i <= x; ++i) {
            if(i % 2) cout << 1 << ' ' << -2 << ' ';
            else cout << -1 << ' ' << 2 << ' ';
        }
        cout << 1 << ' ';
    }
    cout << "\n";
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int tests = 1;
    cin >> tests;
    while(tests--){
        testcase();
    }
    return 0;
}