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

bool type (char c) {
    if (c == '(' || c == ')') return 0;
    return 1;
}

void testcase() {
    string s; cin >> s;
    vector<pair<int, bool>> openStack;
    vector<vector<int>> children(s.size() + 1);

    for (int i = 0; i < s.size(); i++) {
        bool curr = type(s[i]);
        if (openStack.size() && openStack.back().second == curr) openStack.pop_back();
        else {
            if (openStack.size()) children[openStack.back().first].push_back(i);
            else children[s.size()].push_back(i);
            openStack.emplace_back(i, curr);
        }
    }

    for (int i = 0; i <= s.size(); i++) {
        vector<int> cnt(2);
        for (int u : children[i]) cnt[type(s[u])]++;
        if (max(cnt[0], cnt[1]) >= 2) return cout << "No\n", void();
    }
    cout << "Yes\n";
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