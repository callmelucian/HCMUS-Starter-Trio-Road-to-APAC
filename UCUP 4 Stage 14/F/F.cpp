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

const int MAX = 5e5 + 5;

int N, M, run, eu[MAX], ev[MAX];
vector<int> adj[MAX];
int dir[MAX];
vector<tuple<int, int, int>> edges;
bool inCycle[MAX];

int searchEdge(int u, int v){
    if(u > v) swap(u, v);
    int pos = lower_bound(all(edges), make_tuple(u, v, -1)) - begin(edges);
    pos = get<2>(edges[pos]);
    return pos;
}

void setDirect(int u, int v){
    dbg(u, v);
    int i = searchEdge(u, v);
    if(eu[i] == u) dir[i] = 0;
    else dir[i] = 1;
}

int vis[MAX], cnt;
void dfsMark(int u){
    if(vis[u]) return;
    vis[u] = ++cnt;
    for(auto v : adj[u]) if(!inCycle[v]){
        if(vis[v]){
            if(vis[v] < vis[u]) setDirect(v, u);
        } else{
            setDirect(u, v);
            dfsMark(v);
        }
    }
}

void firstRun(){
    cin >> N >> M;
    for(int i = 0; i < M; ++i){
        int u, v;
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
        eu[i] = u;
        ev[i] = v;
        edges.emplace_back(min(eu[i], ev[i]), max(eu[i], ev[i]), i);
    }
    sort(all(edges));
    int K;
    cin >> K;
    vector<int> P(K);
    for(int i = 0; i < K; ++i){
        cin >> P[i];
        inCycle[P[i]] = 1;
    }

    for(int i = 0; i < K; ++i){
        int j = (i + 1) % K;
        setDirect(P[i], P[j]);
    }

    for(auto i : P){
        for(auto j : adj[i]){
            if(inCycle[j]) continue;
            setDirect(i, j);
        }
    }

    for(auto i : P){
        for(auto j : adj[i]){
            if(inCycle[j]) continue;
            dfsMark(j);
        }
    }

    for(int i = 0; i < M; ++i){
        if(dir[i] == 0){
            cout << eu[i] << ' ' << ev[i] << '\n';
        } else{
            cout << ev[i] << ' ' << eu[i] << '\n';
        }
    }
}

vector<int> foundCycle;
stack<int> st;
bool dfsFindCycle(int u){
    vis[u] = 1;
    st.push(u);
    for(auto v : adj[u]){
        if(vis[v]){
            if(vis[v] == 1){
                foundCycle.clear();
                int last = -1;
                while(last != v){
                    last = st.top(); st.pop();
                    foundCycle.push_back(last);
                }
                reverse(all(foundCycle));
                return true;
            }
        } else{
            if(dfsFindCycle(v)) return true;
        }
    }
    st.pop();
    vis[u] = 2;
    return false;
}

void findArbitraryCycle(){
    for(int i = 1; i <= N; ++i){
        if(dfsFindCycle(i)){
            return;
        }
    }
}

int nxt[MAX];
vector<int> order;

void ans(int u, int v){
    nxt[u] = v;
}
void dfsTree(int u){
    vis[u] = ++cnt;
    order.push_back(u);
    dbg(u);
    // cerr << "visiting " << u << '\n';
    for(auto v : adj[u]) if(vis[v] != -1){
        if(vis[v]){
            if(vis[v] < vis[u]){
                //back edge
                // cerr << "visit back edge " << u << ' ' << v << '\n';

                if(inCycle[u]) continue; //goofy edge
                assert(inCycle[v]);

                int pos = sz(order) - 1;
                vector<int> attach;
                while(pos >= 0 && !inCycle[order[pos]]){
                    attach.push_back(order[pos]);
                    --pos;
                }
                // assert(pos >= 0);
                int c = order[pos];
                attach.push_back(c);
                reverse(all(attach));
                attach.push_back(v);
                dbg(attach);
                int last = -1;
                for(auto u : attach){
                    inCycle[u] = 1;
                    if(last != -1){
                        ans(last, u);
                    }
                    last = u;
                }
            }
        } else{
            // cerr << "move " << u << ' ' << v << '\n';
            dfsTree(v);
        }
    }
    order.pop_back();
    vis[u] = -1;
}

void secondRun(){
    cin >> N >> M;
    for(int i = 0; i < M; ++i){
        int u, v;
        cin >> u >> v;
        adj[u].emplace_back(v);
    }
    findArbitraryCycle();
    int root = foundCycle[0];
    dbg(foundCycle);
    for(int i = 0; i < sz(foundCycle); ++i){
        inCycle[foundCycle[i]] = 1;
        nxt[foundCycle[i]] = foundCycle[(i + 1) % sz(foundCycle)];
    }
    fill(vis + 1, vis + 1 + N, 0);
    cnt = 0;
    inCycle[root] = 1;
    dbg(root);
    dfsTree(root);

    vector<int> ansCycle;
    int u = root;
    // for(int i = 1; i <= N; ++i) cout << nxt[i] << " \n"[i == N];
    // dbg(u);
    // return;
    while(true){
        dbg(u);
        ansCycle.push_back(u);
        if(sz(ansCycle) > N){
            cerr << "asdfasfas\n";
            break;
        }
        if(nxt[u] == ansCycle[0]) break;
        u = nxt[u];
    }
    for(auto x : ansCycle) cout << x << ' ' ;
    cout << '\n';
}

void testcase() {
    cin >> run;
    if(run == 1){
        firstRun();
    } else{
        secondRun();
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
  
    int TC = 1;
    while (TC--) {
        testcase();
    }

    return 0;
}