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

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using tpl = tuple<int,int,int>;

template<class T> bool minimize(T& a, const T& b){  return (a > b ? a = b, 1 : 0); }
template<class T> bool maximize(T& a, const T& b){  return (a < b ? a = b, 1 : 0); }

void testcase() {
    int N;
    cin >> N;
    vector<int> A(N * 2);
    for(int i = 0; i < N; ++i){
        cin >> A[i];
        A[i + N] = A[i];
    }
    vector<int> nxt(N * 2);
    vector<int> st;
    for(int i = 2 * N - 1; i >= 0; --i){
        while(!st.empty() && A[i] >= A[st.back()]) st.pop_back();
        if(st.empty()) nxt[i] = 2 * N;
        else nxt[i] = st.back();
        st.push_back(i);
    }
    dbg(nxt);
    int mx = *max_element(all(A));
    vector<int> cand(N);
    iota(all(cand), 0);
    int added = 0;
    while(true){
        int mn = 1e9 + 10, len = -1;
        for(auto s : cand){
            int value = A[s + added];
            int siz = min(s + N, nxt[s + added]) - (s + added);
            dbg(value, siz);
            if(mn > value){
                mn = value;
                len = siz; 
            } else if(mn == value && len < siz){
                len = siz;
            }
        }
        dbg(cand);
        vector<int> newCand;
        for(auto s : cand){
            int value = A[s + added];
            int siz = min(s + N, nxt[s + added]) - (s + added);
            if(value == mn && len == siz){
                newCand.push_back(s);
            }
        }
        added += len; 
        dbg(newCand);
        if(sz(newCand) == 1 || added == N){
            int mx = -1;
            for(int i = newCand[0]; i < newCand[0] + N; ++i){ 
                maximize(mx, A[i]);
                cout << mx << ' ';
            }
            cout << '\n';
            return;
        }
        assert(!newCand.empty());
        swap(cand, newCand);
    }
    assert(false);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
  
    int TC = 1;
    cin >> TC;
    while (TC--) {
        testcase();
    }

    return 0;
}

/*

1
5
1 2 1 3 1
6
2 1 3 1 4 1

6
5
5 4 3 2 1
4
1 3 1 3
5
1 2 1 3 1
5
2 3 2 1 1
6
1 2 1 3 1 4
6
2 1 3 1 4 1

1
6
9 9 9 9 9 9

*/