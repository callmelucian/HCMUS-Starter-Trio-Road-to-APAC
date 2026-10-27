#include <bits/stdc++.h>
using namespace std;

#define all(v) begin(v), end(v)
#define compact(v) v.erase(unique(all(v)), end(v))
#define sz(v) (int)v.size()
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
template<class T> bool maximize(T& a, const T& b){ return a < b ? a = b, 1 : 0; }

#ifdef LOCAL
    #include "debug.hpp"
#else 
    #define dbg(...) ((void)0)
#endif //LOCAL

const int MAX = 2e5 + 5;
const int MAXV = 1e6 + 5;

int N, Q, A[MAX];
vector<int> divs[MAXV];
vector<pii> queries[MAX], events[MAX], intervals[MAX];

struct SqrtDecomp{
    const int blockSize = 320;

    vector<int> maxBlock, maxPoint;
    SqrtDecomp(int n) : maxBlock((n - 1) / blockSize + 1, 0), maxPoint(n) {}

    void update(int i, int v){
        maximize(maxPoint[i], v);
        maximize(maxBlock[i  / blockSize], v);
    }

    int querySuff(int i){
        int ans = 0;
        for(int b = (i / blockSize) + 1; b < sz(maxBlock); ++b){
            maximize(ans, maxBlock[b]);
        }

        int last = min(sz(maxPoint), ((i / blockSize) + 1) * blockSize);
        for(int j = i; j < last; ++j) maximize(ans, maxPoint[j]);
        return ans;
    }
};

void sieve(){
    for(int i = 1; i <= 1000000; ++i){
        for(int j = i; j <= 1000000; j += i){
            divs[j].push_back(i);
        }
    }
}

void testcase(){
    cin >> N >> Q;
    for(int i = 0; i < N; ++i){
        cin >> A[i];
    }
    sieve();
    for(int i = 0; i < Q; ++i){
        int l, r;
        cin >> l >> r;
        --l, --r;
        queries[r].emplace_back(l, i);
    }
    cerr << "done 1\n";
    vector<int> last(MAXV, -1);
    for(int j = 0; j < N; ++j){
        dbg(j, divs[A[j]]);
        for(auto d : divs[A[j]]){
            if(last[d] != -1){
                int i = last[d];
                int atLeast = i + 2 * (j - i);
                if(atLeast < N) events[atLeast].emplace_back(i, d);
            }
            last[d] = j;
        }
    }
    fill(all(last), -1);
    for(int i = N - 1; i >= 0; --i){
        for(auto d : divs[A[i]]){
            last[d] = i;    
        }
        for(auto [l, v] : events[i]){
            int r = last[v];
            if(r != -1){
                intervals[r].emplace_back(l, v);
                dbg(l, r, v);
            }
        }
    }

    vector<int> ans(Q);
    SqrtDecomp ds(N);
    for(int r = 0; r < N; ++r){
        for(auto [l, v] : intervals[r]){
            ds.update(l, v);
        }
        for(auto [l, id] : queries[r]){
            ans[id] = ds.querySuff(l);
        }
    }
    for(int i = 0; i < Q; ++i){
        cout << ans[i] << '\n';
    }
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