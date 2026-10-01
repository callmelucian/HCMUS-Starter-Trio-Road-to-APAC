#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
    #include "debug.hpp"
#else
    #define dbg(...) ((void)0)
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

void testcase(){
    int N;
    cin >> N;
    vector<int> A(N);
    for(int i = 0; i < N; ++i){
        cin >> A[i];
    }

    if(A[0] < A[1]){
        //same block
        int d = A[1] - A[0];
        int last = 1;
        for(int i = 1; i < N; ++i){
            if(A[i - 1] < A[i]){
                last = i; 
            } else break;
        }
        cout << max(d, A[last] / d) << '\n';
    } else{
        int k = A[1] - 1;
        cout << (A[0] / k) << '\n';
    }
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