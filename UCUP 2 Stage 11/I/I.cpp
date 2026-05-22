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
#define size(v) (v).size()
#define pb push_back
#define eb emplace_back

using ll = long long;
using db = double;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using tpl = tuple<int,int,int>;

template<class T> bool minimize(T& a, const T& b){  return (a > b ? a = b, 1 : 0); }
template<class T> bool maximize(T& a, const T& b){  return (a < b ? a = b, 1 : 0); }

void testcase() {
    int n, m;
    cin >> n >> m;
    bool ok = true;
    map<int, int> v;
    for(int i = 0; i < m; ++i){
        int a, b;
        cin >> a >> b;
        if(v.count(a) && v[a] != b){
            ok = false;
        } else{
            v[a] = b;
        }
    }
    if(!ok){
        cout << "No\n";
        return;
    }
    int last = 0, value = 0;
    for(auto [i, val] : v){
        int gap = i - last;
        dbg(i, val, last, gap);
        if(value + gap == val){
        } else{
            dbg(gap, val + 1);
            if(gap >= val + 1){
                dbg("ok");
            } else{
                // cerr << "no\n";
                ok = false;
                break;
            }
        }
        value = val;
        last = i;
    }
    if(!ok){
        cout << "No\n";
    } else{
        cout << "Yes\n";
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int tests = 1;
    cin >> tests;
    while(tests--){
        testcase();
    }
    return 0;
}