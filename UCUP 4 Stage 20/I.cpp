#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
    #include "debug.hpp"
#else
    #define dbg(...) (void(0))
#endif // LOCAL

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

ll func(ll a, ll b){
    if(b == 0) return a;
    return func(b, a % b);
}

pair<ll, map<ll, int>> info(vector<int> A){
    ll G = 0;
    for(int i = 1; i < sz(A); ++i){
        G = func(G, A[i] - A[i - 1]);
    }
    G *= 2;
    if(G == 0){
        map<ll, int> cnt;
        cnt[A[0]] = sz(A);
        return make_pair(0, cnt);
    }
    map<ll, int> cnt;
    for(int i = 0; i < sz(A); ++i){
        ll x = (A[i] % G);
        if(x < 0) x += G;
        ++cnt[x];
    }
    return make_pair(G, cnt);
}

void testcase(){
    int N;
    cin >> N;
    vector<int> A(N), B(N);
    for(int i = 0; i < N; ++i){
        cin >> A[i] >> B[i];
    }
    sort(all(A));
    sort(all(B));
    cout << (info(A) == info(B) ? "YES" : "NO") << '\n';
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