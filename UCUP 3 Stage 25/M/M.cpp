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
    int N, K;
    cin >> N >> K;
    vector<int> A(N);
    for(int i = 0; i < N; ++i){
        cin >> A[i];
    }
    int G = 0;
    for(int i = 0; i + 1 < N; ++i) if(A[i] != A[i + 1]){
        if(G == 0) G = abs(A[i] - A[i + 1]);
        else G = __gcd(G, abs(A[i] - A[i + 1]));
    }

    if(G == 0){
        cout << K << ' ' << 1LL * K * (K + 1) / 2 << '\n';
        return;
    }

    vector<int> divs;
    for(int i = 1; i * i <= G; ++i){
        if(G % i == 0){
            divs.pb(i);
            if(G / i != i) divs.pb(G / i);
        }
    }


    int minElement = *min_element(all(A));
    int cnt = 0;
    ll sum = 0;
    // dbg(divs);

    vector<int> l(N, -1), r(N, -1);
    vector<int> st;
    for(int i = 0; i < N; ++i){
        while(!st.empty() && A[st.back()] >= A[i]) st.pop_back();
        l[i] = (st.empty() ? -1 : st.back());
        st.push_back(i);
    }
    st.clear();
    for(int i = N - 1; i >= 0; --i){
        while(!st.empty() && A[st.back()] >= A[i]) st.pop_back();
        r[i] = (st.empty() ? -1 : st.back());
        st.push_back(i);
    }
    
    for(int x : divs){
        x -= minElement;
        if(1 <= x && x <= K){
            bool ok = true;
            // cerr << "Checking " << x << '\n';
            for(int i = 0; i < N; ++i){
                if(l[i] != -1 && (A[i] + x) % (A[l[i]] + x)){
                    ok = false;
                    break;
                }
                if(r[i] != -1 && (A[i] + x) % (A[r[i]] + x)){
                    ok = false;
                    break;
                }
            }
            if(ok){
                ++cnt;
                sum += x;
            }
        }
    }
    cout << cnt << ' ' << sum << '\n';
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