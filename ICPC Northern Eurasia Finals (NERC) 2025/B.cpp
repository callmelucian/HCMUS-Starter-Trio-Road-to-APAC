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

void testcase(){
    int N, M;
    cin >> N >> M;
    multiset<int> A, B;
    for(int i = 0; i < N; ++i){
        int x; cin >> x;
        A.insert(x);
    }
    for(int i = 0; i < M; ++i){
        int x; cin >> x;
        B.insert(x);
    }

    int turn = 0;
    while(!A.empty() && !B.empty()){
        if(turn == 0){
            int maxA = *prev(A.end());
            int maxB = *prev(B.end());
            B.erase(prev(B.end()));
            if(maxA < maxB){
                int res = maxB - maxA;
                B.insert(res);
            }
        } else{
            int maxA = *prev(A.end());
            int maxB = *prev(B.end());
            A.erase(prev(A.end()));
            if(maxA > maxB){
                int res = maxA - maxB;
                A.insert(res);
            }
        }
        turn ^= 1;
    }
    if(A.empty()) cout << "Bob\n";
    else cout << "Alice\n";
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t = 1;
    cin >> t;
    while(t--){
        testcase();
    }
    return 0;
}