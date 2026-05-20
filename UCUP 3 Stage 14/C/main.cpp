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

char turnLeft (char c) {
    switch (c) {
        case 'N': return 'W';
        case 'W': return 'S';
        case 'S': return 'E';
        case 'E': return 'N';
    }
    return 'O';
}

void testcase(){
    int n; cin >> n;
    vector<pair<char,int>> inp(n), instruct;
    for (auto &[c, d] : inp) cin >> c >> d;

    char init = inp[0].first, curr = inp[0].first;
    for (auto [c, d] : inp) {
        if (curr != c) {
            instruct.emplace_back(turnLeft(curr) == c ? 'L' : 'R', 0);
            curr = c;
        }
        instruct.emplace_back('Z', d);
    }

    cout << instruct.size() << " " << init << "\n";
    for (auto [c, d] : instruct) {
        cout << c << " ";
        if (d) cout << d;
        cout << "\n";
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