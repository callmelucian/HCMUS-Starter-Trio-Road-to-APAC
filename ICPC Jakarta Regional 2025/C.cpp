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
using pll = pair<ll, ll>;

#ifdef LOCAL 
    #include "debug.hpp"
#else
    #define dbg(...) (void(0))
#endif //LOCAL

void testcase(){

}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int tests = 1;
    // cin >> tests;
    while(tests--){
        testcase();
    }
    return 0;
}#include <bits/stdc++.h>
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
using pll = pair<ll, ll>;

#ifdef LOCAL 
    #include "debug.hpp"
#else
    #define dbg(...) (void(0))
#endif //LOCAL

void testcase(){
    int N, M;
    cin >> N >> M;
    
    vector<int> A(N + 1);
    int bound = (M + 1) / 2;
    for(int i = 1; i <= N; ++i){
        cin >> A[i];
    }
    if(*max_element(all(A)) > bound){
        cout << -1 << '\n';
        return;
    }
    
    vector<vetor<int>> B(N + 1, vector<int>(M + 1));

    if(M & 1){
        int last = -2;
        for(int i = 1; i < N; ++i){
            if(A[i] == bound){
                if(last + 1 == i){
                    cout << -1 << '\n';
                    return;
                }
                last = i;
            } 
        }

        if(last == -1){
            last = 1;
        }

        int st = 0;
        for(int i = last; i <= N; ++i){
            for(int j = 1 + st, cnt = 0; cnt < A[i] && j <= M; j += 2){
                A[i][j] = 1;
            }
            st ^= 1;
        }
        st = 1;
        for(int i = last - 1; i >= 1; --i){
            for(int j = 1 + st, cnt = 0; cnt < A[i] && j <= M; j += 2){
                A[i][j] = 1;
            }
            st ^= 1;
        }
    } else{
        int st = 0;
        for(int i = 1; i <= N; ++i){
            for(int j = 1 + st, cnt = 0; cnt < A[i]; j += 2){
                A
            }
        }
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