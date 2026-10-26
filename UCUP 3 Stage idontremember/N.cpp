#include <bits/stdc++.h>
using namespace std;

#define all(v) begin(v), end(v)
#define compact(v) v.erase(unique(all(v)), end(v))
#define sz(v) (int)v.size()
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

#ifdef LOCAL
    #include "debug.hpp"
#else 
    #define dbg(...) ((void)0)
#endif //LOCAL

string s[5];
int st[5], ed[5];
vector<int> spaces[5], sep[5];

int toInt(string s){
    // dbg(s);
    int sgn = 1;
    int num = 0;
    for(auto d : s){
        if(d == '-'){
            sgn = -1;
        } else{
            num = num * 10 + (d - '0');
        }
    }
    return num * sgn;
}

string getSub(string s, int i, int j){
    return s.substr(i, j - i + 1);
}

ll solve(ll from, ll to, ll det){
    if(det > 0){
        ll l = 0, r = 1e8, k = -1;
        while(l <= r){
            ll m = l + r >> 1;
            if(from + m * det < to) k = m, l = m + 1;
            else r = m - 1;
        }
        dbg(k);
        if(k == -1) return 0;
        ++k;
        return from * k + k * (k - 1) / 2 * det; 
    } else{
        ll l = 0, r = 1e8, k = -1;
        while(l <= r){
            ll m = l + r >> 1;
            if(from + m * det > to) k = m, l = m + 1;
            else r = m - 1;
        }
        dbg(k);
        if(k == -1) return 0;
        ++k;
        return from * k + k * (k - 1) / 2 * det; 
    }
}

void testcase(){
    for(int i = 0; i < 5; ++i){
        getline(cin, s[i]);
        for(int j = 0; j < sz(s[i]); ++j){
            if(s[i][j] == ' '){
                spaces[i].emplace_back(j);
            }
            if(s[i][j] == ','){
                sep[i].emplace_back(j);
            }
            if(s[i][j] == '('){
                st[i] = j;
            }
            if(s[i][j] == ')'){
                ed[i] = j;
            }
        }
        if(sz(sep[i]) == 1) sep[i].push_back(ed[i]);
        dbg(i, s[i]);
    }
    cerr << "parse 0\n";

    string name[4];

    name[0] = s[1].substr(spaces[1][0] + 1, spaces[1][1] - spaces[1][0] - 1);
    dbg(name[0]);
    int a = toInt(getSub(s[1], st[1] + 1, sep[1][0] - 1));
    int b = toInt(getSub(s[1], sep[1][0] + 1, sep[1][1] - 1));
    int c = ed[1] == sep[1][1] ? 1 : toInt(getSub(s[1], sep[1][1] + 1, ed[1] - 1));
    name[1] = (getSub(s[2], st[2] + 1, sep[2][0] - 1));
    name[2] = (getSub(s[2], sep[2][0] + 1, sep[2][1] - 1));
    name[3] = ed[2] == sep[2][1] ? "1" : (getSub(s[2], sep[2][1] + 1, ed[2] - 1));
    dbg(a, b, c, name[1], name[2], name[3]);
    ll ans = 0;

    if(c > 0){
        dbg("case1");
        for(int i = a; i < b; i += c){
            int d = (name[1] == name[0] ? i : toInt(name[1]));
            int e = (name[2] == name[0] ? i : toInt(name[2]));
            int f = (name[3] == name[0] ? i : toInt(name[3]));
            dbg(i, d, e, f);
            ans += solve(d, e, f);
        }
    } else{
        for(int i = a; i > b; i += c){
            int d = (name[1] == name[0] ? i : toInt(name[1]));
            int e = (name[2] == name[0] ? i : toInt(name[2]));
            int f = (name[3] == name[0] ? i : toInt(name[3]));
            dbg(i, d, e, f);
            ans += solve(d, e, f);
        }
    }
    cout << ans << '\n';
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