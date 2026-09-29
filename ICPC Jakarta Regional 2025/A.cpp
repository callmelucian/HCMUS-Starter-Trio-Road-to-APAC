/*
- Neu gcd > 1 -> 1 operation
- General -> <= 3 operation
*/

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

void testcase(){
    int N; cin >> N;
    int g = 0;
    vector<int> A(N + 1);
    for (int i = 1; i <= N; i++) cin >> A[i], g = __gcd(g, A[i]);

    if (*max_element(all(A)) == 0) cout << 0 << "\n";
    else if (g > 1) {
        cout << 1 << "\n";
        cout << 1 << " " << g << "\n";
    }
    else {
        cout << 2 << "\n";
        cout << 2 << " " << 10 << "\n";
        cout << 1 << " " << 2 << "\n";
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
5
4 1 2 6 3

5
9 9 9 9 9

3
3 6 9
*/