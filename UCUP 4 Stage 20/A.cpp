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

void testcase(){
    ll ax, ay, bx, by, M, W;
    cin >> ax >> ay >> bx >> by >> M >> W;
    if(M >= 3){
        cout << -1 << '\n';
    } else if(M == 2){
        long double a = sqrtl(1.0l * (ax - bx) * (ax - bx) + (ay - by) * (ay - by));
        long double b = W;
        cout << fixed << a + b * 2.0l << '\n';
    } else{
        long double a = sqrtl(1.0l * (ax - bx) * (ax - bx) + (ay - by) * (ay - by));
        long double b = W / 2.0l;
        cout << fixed << setprecision(10) << sqrtl(a * a + b * b) + b << '\n';
    }
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