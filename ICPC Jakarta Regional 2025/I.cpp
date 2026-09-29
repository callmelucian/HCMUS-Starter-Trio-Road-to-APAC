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

const int MX = 200005;
int n;
string a[3];
int Left[MX], Right[MX], maxLeft[MX], maxRight[MX];

int findLeft(int pos, vector<int> &vt) {
    int res = -1;
    for(int lo = 0, hi = (int)vt.size() - 1; lo <= hi;) {
        int mid = (lo + hi) >> 1;
        int u = vt[mid];
        if(u > pos) hi = mid - 1;
        else if(maxLeft[u - 2] >= pos - u + 1) res = u, hi = mid - 1;
        else lo = mid + 1;
    }
    if(res == -1) return -1e6;
    return (pos - res + 1) * 3 * 2 - pos + res;
}

int findRight(int pos, vector<int> &vt) {
    int res = -1;
    for(int lo = 0, hi = (int)vt.size() - 1; lo <= hi;) {
        int mid = (lo + hi) >> 1;
        int u = vt[mid];
        if(u < pos) lo = mid + 1;
        else if(maxRight[u + 2] >= u - pos + 1) res = u, lo = mid + 1;
        else hi = mid - 1;
    }
    if(res == -1) return -1e6;
    return (res - pos + 1) * 3 * 2 - res + pos;
}

void testcase(){
    cin >> n;
    cin >> a[0] >> a[1] >> a[2];
    
    ++n;
    a[0].push_back('#');
    a[1].push_back('#');
    a[2].push_back('#');

    for(int i = 0, cnt = 0; i < n; ++i) {
        if(a[0][i] == '.' && a[1][i] == '.' && a[2][i] == '.') ++cnt;
        else cnt = 0;
        maxLeft[i] = max(maxLeft[i - 1], cnt);
    }

    for(int i = n - 1, cnt = 0; i >= 0; --i) {
        if(a[0][i] == '.' && a[1][i] == '.' && a[2][i] == '.') ++cnt;
        else cnt = 0;
        maxRight[i] = max(maxRight[i + 1], cnt);
    }

    vector<vector<int>> S;
    vector<int> cur;
    for(int i = 0; i < n; ++i) {
        if(a[0][i] == '#' || a[2][i] == '#') {
            if(cur.size()) S.push_back(cur);
            cur.clear();
            continue;
        }
        if(a[1][i] == '.') cur.push_back(i);
    }

    int ans = -1;
    for(vector<int> &e: S) {
        for(int i = e[0]; i <= e.back(); ++i) {
            // tknp Left
            Left[i] = findLeft(i, e);
            
            // tknp Right
            Right[i] = findRight(i, e);
            dbg(i, e, Left[i], Right[i]);

        }
        int mx = -2e6;
        for(int i = e[0] + 1; i <= e.back(); ++i) {
            mx = max(mx, Left[i - 1] - 2 *(i - 1));
            ans = max(ans, Right[i] + mx + 2 * i - 2);
        }
    }
    if(ans < 14) ans = -1;
    cout << ans;
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