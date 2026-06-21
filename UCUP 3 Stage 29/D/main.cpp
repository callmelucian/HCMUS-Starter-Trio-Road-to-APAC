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
    int n; cin >> n;
    string s; cin >> s;

    // make run-length decoding
    vector<pii> runLength;
    for (int i = 0, curr = 0; i < n; i++) {
        curr++;
        if (i == n - 1 || s[i] != s[i + 1]) {
            runLength.emplace_back(s[i] - '0', curr);
            curr = 0;
        }
    }

    string newString = "";
    int hold = 0;
    for (auto [type, len] : runLength) {
        if (type) hold += len;
        else {
            for (int j = 0; j < len; j++) {
                if (hold) newString += '1', newString += '0', hold--;
                else newString = "";
            }
        }
    }
    for (int j = 0; j < hold; j++) newString += '1';
    dbg(newString);

    cout << (newString.empty() || newString.size() >= 4 ? "Yes" : "No") << "\n";
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
  
    int TC = 1; cin >> TC;
    while (TC--) {
        testcase();
    }

    return 0;
}