#include <bits/stdc++.h>
using namespace std;

#define all(v) begin(v), end(v)
#define sz(v) (int)v.size()
#define compact(v) v.erase(unique(all(v)), end(v))
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

#ifdef LOCAL
    #include "debug.hpp"
#else 
    #define dbg(...) ((void)0)
#endif //LOCAL

pair<int, string> test(int N, int M, vector<pair<int, string>>& hints, int ban){
    string result(M, '.');
    for(int i = 0; i < N; ++i) if(i != ban){
        int st = hints[i].first;
        for(int j = 0; j < sz(hints[i].second); ++j){
            if(result[st + j] == '.' || result[st + j] == hints[i].second[j]){
                result[st + j] = hints[i].second[j];
            } else{
                return {0, ""};
            }
        }
        dbg(result);
    }
    for(int i = 0; i < M; ++i) if(result[i] == '.') return {0, ""};
    return {1, result};
}

void testcase(){
    int N, M;
    cin >> N >> M;
    vector<pair<int, string>> hints(N);
    for(int i = 0; i < N; ++i){
        int st; string q;
        cin >> st >> q;
        hints[i] = {st - 1, q};
    }

    set<string> ways;

    for(int i = 0; i <= N; ++i){
        auto [r, s] = test(N, M, hints, i);
        if(r == 1){
            ways.insert(s);
        }

        if(sz(ways) == 2){
            cout << -2 << '\n';
            return;
        }
    }
    if(sz(ways) == 0) cout << -1 << '\n';
    else cout << *ways.begin() << '\n';
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
3 9
6 EX
8 AM
1 FINAL

3 2
1 AB
2 B
1 A
*/