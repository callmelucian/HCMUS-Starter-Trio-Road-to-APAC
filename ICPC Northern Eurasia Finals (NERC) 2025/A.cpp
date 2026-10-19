#include <bits/stdc++.h>
using namespace std;

#define all(v) begin(v), end(v)
#define sz(v) (int)v.size()
#define compact(v) v.erase(unique(all(v)), end(v))
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
template<class T> bool minimize(T& a, const T& b){ return a > b ? a = b, 1 : 0; }
template<class T> bool maximize(T& a, const T& b){ return a < b ? a = b, 1 : 0; }

#ifdef LOCAL
    #include "debug.hpp"
#else 
    #define dbg(...) ((void)0)
#endif //LOCAL

const vector<ll>& operator+= (vector<ll> &a, const vector<ll> &b) {
    for (int i = 0; i < (int)b.size(); i++) a[i] += b[i];
    return a;
}

const vector<ll>& operator-= (vector<ll> &a, const vector<ll> &b) {
    for (int i = 0; i < (int)b.size(); i++) a[i] -= b[i];
    return a;
}

const vector<ll>& operator*= (vector<ll> &a, const int &m) {
    for (ll &u : a) u *= m;
    return a;
}

vector<ll> operator+ (vector<ll> a, const vector<ll> &b) { return a += b; }
vector<ll> operator- (vector<ll> a, const vector<ll> &b) { return a -= b; }
vector<ll> operator* (vector<ll> a, const int &m) { return a *= m; }

void testcase(){
    int N, M; cin >> N >> M;
    vector<vector<ll>> freq(N, vector<ll>(26));
    vector<ll> allFreq(26);
    for (int i = 0; i < N; i++) {
        string s; cin >> s;
        for (char c : s) freq[i][c - 'A']++;
        allFreq += freq[i];
    }

    for (int ell = 0; ell < N; ell++) {
        vector<ll> having = allFreq * M - freq[ell] * (M + 1);
        if (*min_element(all(having)) < 0) {
            cout << -1 << " ";
            continue;
        }
        vector<ll> need = allFreq - freq[ell];
        ll ans = LLONG_MAX;
        for (int i = 0; i < 26; i++)
            if (need[i]) minimize(ans, having[i] / need[i]);
        cout << ans << " ";
    }
    cout << "\n";
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
3 10
NEERC
NERC
NEF

4 4
LENSE
TEN
SENSELESSNESSES
LENSE
*/