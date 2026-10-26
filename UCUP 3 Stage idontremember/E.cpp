#include <bits/stdc++.h>
using namespace std;

#define all(v) begin(v), end(v)
#define compact(v) v.erase(unique(all(v)), end(v))
#define sz(v) (int)v.size()
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

#ifdef LOCAL
    #include "debug.hpp"
#else 
    #define dbg(...) ((void)0)
#endif //LOCAL

const int MX = 5005;
int n, b[MX];
bitset<MX> a[MX];

void testcase(){
    cin >> n;
    for(int i = 0; i < n; ++i) for(int j = 0; j < n; ++j) {
        char x; cin >> x;
        if(x == '1') a[i][j] = 1;
    }
    for(int i = 0; i < n; ++i) {
        b[i] = n - a[i].count();
        if(b[i] == 1) {
            cout << "NOT FOUND\n";
            return;
        }   
    }
    vector<int> order(n);
    for(int i = 0; i < n; ++i) order[i] = i;
    sort(order.begin(), order.end(), [](const int &i, const int &j) -> bool {
        return b[i] > b[j];
    });
    int result = 0;
    for(int i: order) {
        bitset<MX> cur = a[i];
        for(int j = 0; j < n; ++j) if(a[i][j]) cur = cur | a[j];
        if(cur[i]) cur[i] = 0;
        if(cur.count() == n - 1) {
            cout << i + 1 << ' ';
            if(++result == 3) break;
        }
    }
}



int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t = 1;
    // cin >> t;
    while(t--){
        testcase();
    }
    return 0;
}

/*

6
011010
000101
010111
100001
010100
100010

3
011
001
000

3
010
001
100

*/