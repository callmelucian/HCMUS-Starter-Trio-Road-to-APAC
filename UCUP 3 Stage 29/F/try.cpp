#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<ll,ll> pl;
typedef pair<int,int> pii;
typedef tuple<int,int,int> tpl;

#define all(a) a.begin(), a.end()
#define filter(a) a.erase(unique(all(a)), a.end())

const int mn = 3e4 + 4;
int num[mn], low[mn], timeDfs, ans;
vector<int> adj[mn];
stack<int> st;

void dfs (int u, int p) {
    num[u] = low[u] = ++timeDfs;
    st.push(u);

    for (int v : adj[u]) {
        if (v == p) continue;
        if (!num[v]) {
            dfs(v, u);
            low[u] = min(low[u], low[v]);

            if (low[v] >= num[u]) { // note that this doesn't mean u is an articulation
                cout << "new component: ";
                int curSz = 1, cur = 0;
                do cur = st.top(), st.pop(), curSz++, cout << cur << " ";
                while (cur != v);
                cout << "\n";
                ans = max(ans, curSz);
            }
        }
        else low[u] = min(low[u], num[v]);
    }

    if (u == p && adj[u].empty() <= 1) ans = max(ans, 1); // tricky edge case
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, m; cin >> n >> m;
    while (m--) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    for (int i = 1; i <= n; i++)
        if (!num[i]) dfs(i, i);
    cout << ans;

    return 0;
}