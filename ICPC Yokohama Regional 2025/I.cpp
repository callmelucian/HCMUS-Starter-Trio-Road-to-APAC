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

const int MX = 200005;
const int LIM = 20;
int f[MX][3][3][2];
bool vist[MX][3][3][2];

int state(char c) {
    if(c == '.') return 0;
    if(c == 'a') return 1;
    if(c == 'b') return 2;
    abort();
    return -1;
}

void testcase(){
    int n;
    string s;
    cin >> n >> s;
    s = "." + s + ".";
    
    int flag = 0;
    for(int i = 1; i <= n; ++i) {
        if(s[i] != '.') flag = 1;
    }
    if(flag == 0) {
        if(n == 1) cout << "alice\n";
        else cout << "bob\n";
        return;
    }
    
    int a = 0, b = 0, aa = 0, bb = 0;
    flag = 0;
    for(int i = 1; i <= n; ++i) if(s[i] == '.') {
        int j = i;
        while(i < n && s[i + 1] == '.') ++i;
        if(s[j - 1] == '.') {
            if(s[i + 1] == 'a') {
                ++b;
                if(i > 1) flag++;
            }
            if(s[i + 1] == 'b') {
                ++a;
                if(i > 1) flag--;
            }
        }
        if(s[i + 1] == '.') {   
            if(s[j - 1] == 'a') {
                ++b;
                if(j < n) flag++;
            }
            if(s[j - 1] == 'b') {
                ++a;
                if(j < n) flag--;
            }
        }
        if(s[j - 1] == s[i + 1]) {
            if(s[j - 1] == 'a') ++bb;
            if(s[i + 1] == 'b') ++aa;
        }
    }

    if(a + aa > b + bb) cout << "alice\n";
    else if(a + aa == b + bb && flag > 0) cout << "alice\n";
    else cout << "bob\n";
}

int dwuy(int k, int u, int v, bool t) {
    if(k == 0) return 0;
    if(vist[k][u][v][t]) return f[k][u][v][t];
    vist[k][u][v][t] = 1;
    bitset<64> mex = 0;
    for(int i = 1; i <= min(k, LIM); ++i) {
        int grundy = dwuy(i - 1, u, 2 - t, !t) ^ dwuy(k - i, 2 - t, v, !t);
        bool flag_1 = i != 1 || u != 2 - t;
        bool flag_2 = k != i || v != 2 - t;
        if(flag_1 && flag_2) mex[grundy] = 1;
        
        grundy = dwuy(i - 1, 2 - t, v, !t) ^ dwuy(k - i, u, 2 - t, !t);
        flag_1 = i != 1 || v != 2 - t;
        flag_2 = k != i || u != 2 - t;
        if(flag_1 && flag_2) mex[grundy] = 1;
    }
    while(mex[f[k][u][v][t]]) ++f[k][u][v][t];
    return f[k][u][v][t];
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int tests = 1;
    
    // for(int k = 0; k < MX; ++k) {
    //     for(int u = 0; u < 3; ++u) {
    //         for(int v = 0; v < 3; ++v) {
    //             f[k][u][v][0] = dwuy(k, u, v, 0);
    //             f[k][u][v][1] = dwuy(k, u, v, 1);
    //         }
    //     }
    // }
    
    cin >> tests;
    while(tests--){
        testcase();
    }

    return 0;
}

/*

3
2
..
3
.a.
4
ab..

*/