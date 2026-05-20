#include <bits/stdc++.h>
#ifdef LOCAL
    #include "../debug.hpp"
#else 
    #define dbg(...) (36)
#endif // LOCAL

using namespace std;

#define all(v) begin(v), end(v)
#define rall(v) rbegin(v), rend(v)
#define compact(v) v.erase(unique(all(v)), end(v))
#define pb push_back
#define eb emplace_back

using ll = long long;
using db = double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
template<class T> bool minimize(T& a, const T& b){  return (a > b ? a = b, 1 : 0); }
template<class T> bool maximize(T& a, const T& b){  return (a < b ? a = b, 1 : 0); }

const int NODE = 1e6;
int sink = 1, nodeCounter = 1, usedChain;
vector<pii> adj[NODE];
vector<int> chain;

void preProcess (int k) {
    chain.push_back(sink);
    for (int i = 0; i < k; i++)
        chain.push_back(++nodeCounter);
    
    for (int i = 1; i < chain.size(); i++) {
        int u = chain[i], v = chain[i - 1];
        adj[u].emplace_back(v, 0);
        adj[u].emplace_back(v, 1);
    }
}

int buildFull (int k) {
    usedChain = max(usedChain, k);
    return chain[k];
}

bool getCur (int mask, int pos) {
    return mask >> pos & 1;
}

int buildPrefix (int p, int k) {
    if (k < 0) return sink;
    int source = ++nodeCounter;
    if (getCur(p, k)) {
        int zeroNode = buildFull(k);
        int oneNode = buildPrefix(p, k - 1);
        adj[source].emplace_back(zeroNode, 0);
        adj[source].emplace_back(oneNode, 1);
    }
    else {
        int node = buildPrefix(p, k - 1);
        adj[source].emplace_back(node, 0);
    }
    return source;
}

int buildSuffix (int p, int k) {
    if (k < 0) return sink;
    // cout << "building suffix " << p << " " << k << endl;
    int source = ++nodeCounter;
    if (!getCur(p, k)) {
        int zeroNode = buildSuffix(p, k - 1);
        int oneNode = buildFull(k);
        adj[source].emplace_back(zeroNode, 0);
        adj[source].emplace_back(oneNode, 1);
    }
    else {
        int node = buildSuffix(p, k - 1);
        adj[source].emplace_back(node, 1);
    }
    return source;
}

int buildSingle (int value) {
    // build node
    int bit = 31 - __builtin_clz(value);
    vector<int> vec;
    for (int i = 0; i <= bit; i++) vec.push_back(++nodeCounter);
    vec.push_back(sink);

    // build edge
    for (int i = 0, b = bit; i + 1 < vec.size(); i++, b--) {
        int u = vec[i], v = vec[i + 1];
        adj[u].emplace_back(v, getCur(value, b));
    }

    return vec[0];
}

bitset<1'000'001> taken;

int countPath (const vector<vector<pii>> &adj, int n, int S, int T) {
    vector<int> vist(n + 1), dp(n + 1), topo;
    function<bool(int)> dfs = [&] (int u) {
        if (vist[u]) return vist[u] == 2;
        vist[u] = 1;
        for (auto [v, w] : adj[u])
            if (!dfs(v)) return false;
        vist[u] = 2, topo.push_back(u);
        return true;
    };
    function<void(int,int)> backtrack = [&] (int u, int mask) {
        // cout << "backtracking " << u << " " << mask << "\n";
        if (u == T) return taken[mask] = true, void();
        for (auto [v, w] : adj[u])
            backtrack(v, mask << 1 | w);
    };
    for (int i = 1; i <= n; i++)
        if (!vist[i]) assert(dfs(i));
    
    dp[T] = 1;
    for (int u : topo) {
        for (auto [v, w] : adj[u]) dp[u] += dp[v];
    }
    backtrack(S, 0);
    return dp[S];
}

void testcase (int L, int R) {
    int source = 0, curr = 0;

    if (L == R) source = buildSingle(L);
    else {
        int k = 31 - __builtin_clz(L ^ R), bit = 31 - __builtin_clz(L);
        preProcess(k);
        
        // process those first bits of L, R
        source = ++nodeCounter, curr = source;
        for (int i = bit; i > k; i--) {
            int node = ++nodeCounter;
            adj[curr].emplace_back(node, getCur(L, i));
            curr = node;
        }

        // divide and conquer
        int zeroNode = buildSuffix(L, k - 1);
        int oneNode = buildPrefix(R, k - 1);

        // if (k == bit) {
        //     for (auto [nextNode, w] : adj[zeroNode])
        //         adj[curr].emplace_back(nextNode, w);
        // }
        adj[curr].emplace_back(zeroNode, 0);
        adj[curr].emplace_back(oneNode, 1);
    }

    vector<pii> newSource;
    function<void(int)> mergeSource = [&] (int u) {
        for (auto [v, w] : adj[u]) {
            if (w) newSource.emplace_back(v, w);
            else mergeSource(v);
        }
    };
    mergeSource(source);
    adj[source] = newSource;

    vector<int> mappedID(nodeCounter + 1), deleted(nodeCounter + 1, true);
    function<void(int)> dfs = [&] (int u) {
        if (!deleted[u]) return;
        deleted[u] = false;
        for (auto [v, w] : adj[u]) dfs(v);
    };
    dfs(source);

    int counter = 0;
    for (int i = 1; i <= nodeCounter; i++)
        if (!deleted[i]) mappedID[i] = ++counter;
    
    vector<vector<pii>> newAdj(counter + 1);
    for (int i = 1; i <= nodeCounter; i++) {
        for (auto [j, w] : adj[i])
            if (mappedID[i] && mappedID[j])
                newAdj[mappedID[i]].emplace_back(mappedID[j], w);
    }

    cout << counter << "\n";
    for (int i = 1; i <= counter; i++) {
        cout << newAdj[i].size() << " ";
        for (auto [j, w] : newAdj[i]) cout << j << " " << w << " ";
        cout << "\n";

        // for (auto [j, w] : newAdj[i]) cout << i << " " << j << " " << w << "\n";
    }

    // int aa = countPath(newAdj, counter, mappedID[source], mappedID[sink]);
    // int bb = taken.count();

    // cout << aa << " " << bb << " " << R - L + 1 << endl;

    // if (aa != bb || aa != (R - L + 1)) {
    //     cout << "Wrong answer " << L << " " << R << endl;
    //     exit(0);
    // }
    
    // for (int i = 1; i <= nodeCounter; i++) adj[i].clear();
    // chain.clear();
    // source = nodeCounter = 1, usedChain = 0;
    // taken.reset();
}

mt19937 rng(21);

int rr (int l, int r) { return uniform_int_distribution<int>(l, r)(rng); }

int main(){
  ios_base::sync_with_stdio(0); cin.tie(0);

    int L, R; cin >> L >> R;
    testcase(L, R);
  return 0;
}