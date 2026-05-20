#include <bits/stdc++.h>
#ifdef LOCAL
    #include "../debug.hpp"
#else 
    #define dbg(...) (36)
#endif // LOCAL

using namespace std;

#define all(v) begin(v), end(v)
#define rall(v) rbegin(v), rend(v)
#define compact(v) v.erase(unique(all(v)), end(v))
#define pb push_back
#define eb emplace_back

using ll = long long;
using db = double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
template<class T> bool minimize(T& a, const T& b){  return (a > b ? a = b, 1 : 0); }
template<class T> bool maximize(T& a, const T& b){  return (a < b ? a = b, 1 : 0); }

vector<int> factorize(int n){
    vector<int> divs;
    for(int i = 1; i * i <= n; ++i){
        if(n % i == 0){
            divs.push_back(i);
            if(n / i != i) divs.push_back(n / i);
        }
    }
    sort(all(divs));
    return divs;
}

void testcase(){
    int n;
    cin >> n;
    vector<int> divs = factorize(n);
    int last = n + 1;
    reverse(all(divs));
    ll ans = 0;
    for(auto d : divs){
        ans += 1LL * (last - d) * (n / d);
        last = d;
    }
    cout << ans << '\n';
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