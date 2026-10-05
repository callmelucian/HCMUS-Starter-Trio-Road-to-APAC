#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
    #include "debug.hpp"
#else
    #define dbg(...) ((void)0)
#endif // LOCAL

#define all(v) begin(v), end(v)
#define compact(v) v.erase(unique(all(v)), end(v))
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using ull = unsigned long long;
using tpl = tuple<int,int,int>;

const int dr[4] = {-1, 0, 0, 1};
const int dc[4] = {0, -1, 1, 0};

int snake[3030][3030], dist[3030][3030];
char obs[3030][3030];
bool vist[3030][3030];

void testcase(){
    int N, M, K; cin >> N >> M >> K;
    int xHead = 0, yHead = 0;
    for (int i = K; i >= 1; i--) {
        int u, v; cin >> u >> v;
        snake[u][v] = i;
        if (i == K) xHead = u, yHead = v;
    }
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= M; j++) cin >> obs[i][j];

    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= M; j++) dist[i][j] = INT_MAX;

    dist[xHead][yHead] = 0;
    priority_queue<tpl> pq; pq.emplace(0, xHead, yHead);

    auto ok = [&] (int i, int j) {
        return 1 <= i && i <= N && 1 <= j && j <= M && obs[i][j] == '.';
    };
    dbg(0);

    while (pq.size()) {
        int ds, i, j; tie(ds, i, j) = pq.top(); pq.pop();
        if (vist[i][j]) continue;
        vist[i][j] = true;

        for (int k = 0; k < 4; k++) {
            int i2 = i + dr[k], j2 = j + dc[k];
            if (ok(i2, j2)) {
                int weight = max(snake[i2][j2], dist[i][j] + 1);
                if (weight < dist[i2][j2]) {
                    dist[i2][j2] = weight;
                    pq.emplace(-weight, i2, j2);
                }
            }
        }
    }

    ull ans = 0;
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= M; j++)
            if (dist[i][j] != INT_MAX)
                ans += (ull)dist[i][j] * (ull)dist[i][j];
    cout << ans << "\n";

    #ifdef LOCAL
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= M; j++) cout << dist[i][j] << " ";
            cout << "\n";
        }
    #endif
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

/*
4 5 5
3 5
3 4
3 3
3 2
4 2
.....
.....
.....
.....

2 2 4
1 1
1 2
2 2
2 1
..
..

5 5 3
1 2
1 1
2 1
.....
.###.
.#.#.
.###.
.....

4 3 5
4 2
4 3
3 3
2 3
1 3
...
...
...
...
*/