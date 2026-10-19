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

mt19937 rng(12312);
map<pii, int> asked;

struct DSU{
    vector<int> f;
    DSU(int n) : f(n, -1) {}
    int root(int u){
        return f[u] < 0 ? u : (f[u] = root(f[u]));
    }
    bool join(int u, int v){
        u = root(u);
        v = root(v);
        if(u == v) return false;
        if(f[u] > f[v]) swap(u, v);
        f[u] += f[v];
        f[v] = u;
        return true;
    }
    int getSize(int u){
        return -f[root(u)];
    }
};

int F(int p, int e){
    cout << "? " << p << ' ' << e + 1 << endl;
    int res;
    cin >> res;
    return res;
}

void testcase(){
    int M;
    cin >> M;
    int bigCyclesGraph = 0;
    int currentGraph = 0;
    int cnt = 0;
    vector<int> ids(M);
    vector<pair<int, int>> prefixCycles;
    iota(all(ids), 0);
    shuffle(all(ids), rng);
    DSU dsu(M);
    vector<int> ans(M, -2);
    for(auto i : ids){
        int u = ++cnt;
        int b = F(currentGraph, i);
        if(b){
            //new Cycles 
            currentGraph = u;
            prefixCycles.emplace_back(cnt, i);
        } else{
            // dbg(prefixCycles, bigCyclesGraph);
            //visited this cycle
            if(bigCyclesGraph){
                int _ = ++cnt;
                int b = F(bigCyclesGraph, i);
                if(!b){
                    //in a big cycle
                    ans[i] = 0;
                    continue;
                } else{
                    //doesn't belong to a big cycle
                }
            }
            //doesn't belong to the big cycles, belong to an activated cycle
            int l = 0, r = sz(prefixCycles) - 1, pos = -1;
            while(l <= r){
                int mid = l + r >> 1;
                int k = ++cnt;
                int b = F(prefixCycles[mid].first, i);
                if(!b){
                    //visited the belonging cycle
                    pos = mid;
                    r = mid - 1;
                } else{
                    l = mid + 1;
                }
            }
            if(pos == -1){
                //this is a bridge
                ans[i] = -1;
                continue;
            }
            assert(pos != -1);
            dsu.join(prefixCycles[pos].second, i);
            // dbg("addEdge", prefixCycles[pos].second, i);
            if(dsu.getSize(i) > 14){
                //deactive the cycle, remove from prefixCycles and turn on in the bigCycle
                F(bigCyclesGraph, prefixCycles[pos].second);
                bigCyclesGraph = ++cnt;
                prefixCycles.erase(prefixCycles.begin() + pos);
            } 
        }
    }

    cout << "! ";
    for(int i = 0; i < M; ++i){
        if(ans[i] == -2){
            if(dsu.getSize(i) > 14){
                cout << 0 << ' ';
            } else {
                cout << dsu.getSize(i) << ' ';
            }
        } else{
            cout << ans[i] << ' ';
        }
    }
    cout << '\n';
    int result;
    cin >> result;

}

int main(){
    int t = 1;
    cin >> t;
    while(t--){
        testcase();
        asked.clear();
    }
    return 0;
}