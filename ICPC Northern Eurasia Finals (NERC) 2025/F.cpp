#include <bits/stdc++.h>
using namespace std;

#define all(v) begin(v), end(v)
#define rall(v) rbegin(v), rend(v)
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

map<vector<int>, int> state;

int findState(vector<int> piles){
    sort(rall(piles));
    while(!piles.empty() && piles.back() == 0) piles.pop_back();
    if(piles.empty()) return 0; //losing state
    reverse(all(piles));
    if(state.count(piles)) return state[piles];
    for(int i = 0; i < sz(piles); ++i){
        //second player choose this pile
        int stillWin = 0;
        for(int j = 1; j <= piles[i]; ++j){
            //first player choose to remove j stones
            vector<int> nxt = piles;
            nxt[i] -= j;
            if(findState(nxt) == 0){
                stillWin = 1;
                break;
            }
        }
        if(stillWin){
            //second player will not choose this pile
            continue;
        } else{
            return state[piles] = 0;
        }
    }
    return state[piles] = 1; //first player always win
}

bool checkAlice (const vector<int> &x) {
    int countOne = 0;
    for (int u : x) countOne += (u == 1);
    if (*max_element(all(x)) > 1) return countOne % 2 == 0;
    return countOne % 2 == 1;
    // return (countOne % 2 == 0 && *max_element(all(x)) > 1) || (!countOne);
}

void brute(){
    int val = 7;
    vector<vector<int>> arrays;
    for(int j = 1; j <= val; ++j){
        arrays.push_back({j});
    }
    for(int n = 2; n <= 8; ++n){
        vector<vector<int>> newArrays;
        for(int j = 1; j <= 7; ++j){
            for(auto x : arrays){
                x.push_back(j);
                sort(all(x));
                newArrays.push_back(x);
            }
        }
        sort(all(newArrays));
        compact(newArrays);
        swap(newArrays, arrays);
        for(auto x : arrays){
            int u = findState(x);
            // dbg(x, u);
            if (u != checkAlice(x)) {
                cout << "WA\n";
                dbg(x, u, checkAlice(x));
                exit(0);
            }
        }
        cout << "AC" << endl;
    }
}

void testcase(){
    int N; cin >> N;
    vector<int> A(N);
    for (int &u : A) cin >> u;

    cout << (checkAlice(A) ? "Alice" : "Bob") << "\n";
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    // brute();
    int t = 1;
    cin >> t;
    while(t--){
        testcase();
    }
    return 0;
}

/*
3
3
1 2 3
1
1
5
10 3 4 7 4
*/