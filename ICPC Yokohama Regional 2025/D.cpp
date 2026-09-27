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
using db = double;

string concat(ll a, ll b){
    string s = to_string(a) + to_string(b);
    return s;
}

bool isBigger(string a, string b){
    return sz(a) > sz(b) || (sz(a) == sz(b) && a > b); 
}

int countDigits(ll n){
    int cnt = 0;
    while(n > 0){
        ++cnt;
        n /= 10;
    }
    return cnt;
}

void testcase(){
    ll N;
    cin >> N;
    ll num = 1;
    string ans = "";
    for(int k = 0; num < N; ++k, num *= 10){
        int x = countDigits(N - num);
        ll l = num, r = 10 * num - 1, chosen = -1;
        while(l <= r){
            ll mid = (l + r) / 2;
            if(countDigits(N - mid) == x) chosen = mid, l = mid + 1;
            else r = mid - 1;
        }
        assert(chosen != -1);
        if(isBigger(concat(chosen, N - chosen), ans)) ans = concat(chosen, N - chosen);
    }
    cout << ans << '\n';
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