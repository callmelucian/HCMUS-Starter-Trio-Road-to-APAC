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
using db = double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#ifdef LOCAL 
    #include "debug.hpp"
#else 
    #define dbg(...) ((36))
#endif //LOCAL

int takeNum(string s){
    int num = 0;
    for(auto& c : s){
        if('0' <= c && c <= '9'){
            num = 10 * num + (c - '0');
        }
    }
    return num;
}

void testcase(){
    vector<string> str;
    string S;
    while(cin >> S){
        str.pb(S);
    }

    map<int, vector<int>> mp;
    for(int i = 0; i < sz(str); ++i){
        if(str[i].back() == ':'){
            str[i].pop_back();
            string vt = str[i];
            vector<string> cur;
            ++i;
            while(i < sz(str) && str[i].back() != ':'){
                cur.pb(str[i]);
                ++i;
            }
            --i;

            for(auto& tmp : cur){
                if(!('0' <= tmp.back() && tmp.back() <= '9')){
                    tmp.pop_back();
                }
                mp[takeNum(tmp)].pb(takeNum(vt));
            }
        }
    }

    for(auto [x, v] : mp){
        cout << "CS-" << x << ": ";
        string sep = "";
        sort(all(v));
        for(auto y : v){
            cout << sep << "CS-" << y;
            sep = ", ";
        }
        cout << '\n';
    }
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