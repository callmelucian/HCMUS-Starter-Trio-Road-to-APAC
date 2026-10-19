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

namespace Grader{
    const int MAX = 1e4 + 5;
    int N, M, asked = 0;
    pii edges[MAX];
    vector<vector<int>> states;
    
    void build(){
        // ifstream input("C.in");
        cin >> N >> M;
        asked = 0;
        for(int i = 0; i < M; ++i){
            int u, v;
            cin >> u >> v;
            edges[i + 1] = {u, v};
        }
        for(int i = 1; i <= M; ++i) dbg(i, edges[i]);
        states.push_back(vector<int>(M + 1, 1));
    }

    int calc(vector<int> state){
        int cc = N;
        dbg(N);
        DSU dsu(N + 1);
        for(int i = 1; i <= M; ++i){
            if(state[i] == 1){
                dbg(edges[i].first, edges[i].second);
                cc -= dsu.join(edges[i].first, edges[i].second);
            }
        }
        return cc == 1;
    }

    int F(int old, int e){
        ++asked;
        if(asked > 8 * M){
            cerr << "asked too much !\n";
            exit(2);
        }
        vector<int> nxt = states[old];
        if(nxt[e] == 0){
            cerr << "wrong question !\n";
            exit(1);
        }
        nxt[e] = 0;
        states.push_back(nxt);
        return calc(nxt);
    }
}


int F(int p, int e){
    cout << "? " << p << ' ' << e + 1 << endl;
    int res;
    #ifdef LOCAL 
        res = Grader::F(p, e + 1);
        cerr << "-> " << res << '\n';
    #else 
        cin >> res;
    #endif //LOCAL
    return res;
}

void testcase(){
    #ifdef LOCAL    
        Grader::build();
        int M = Grader::M;
    #else   
        int M;
        cin >> M;
    #endif //LOCAL
    
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
        assert(cnt <= 8 * M);
        int b = F(currentGraph, i);
        if(b){
            //new Cycles 
            currentGraph = u;
            prefixCycles.emplace_back(cnt, i);
        } else{
            ++cnt;
            if(F(0, i) == 0){
                ans[i] = -1;
                continue;
            }
            // dbg(prefixCycles, bigCyclesGraph);
            //visited this cycle
            if(bigCyclesGraph){
                int _ = ++cnt;
                assert(cnt <= 8 * M);
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
                assert(cnt <= 8 * M);
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
                assert(cnt < 8 * M);
                F(bigCyclesGraph, i);
                bigCyclesGraph = ++cnt;
                prefixCycles.erase(prefixCycles.begin() + pos);
            } 
        }
    }
    dbg(prefixCycles);

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

    #ifndef LOCAL
        int result;
        cin >> result;
    #endif //LOCAL
    // assert(result == 1);
    cerr << "total questions = " << cnt << '\n';
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