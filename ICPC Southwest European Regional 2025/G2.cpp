#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
    #include "debug.hpp"
    const bool isLocal = true;
#else
    #define dbg(...) ((void)0)
    const bool isLocal = false;
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

const int BLOCK = 64;
const int STEP = 3;

void testcase(){
    int N; cin >> N;
    vector<int> pos(N); iota(all(pos), 1);

    vector<pii> ans;
    for (int iter = 0; iter < STEP; iter++) {
        for (int i = 0; i + 1 < BLOCK; i++) {
            vector<pii> batch;
            for (int j = i; j + 1 < pos.size(); j += BLOCK) batch.emplace_back(pos[j], pos[j + 1] - pos[j]);
            reverse(all(batch));
            ans.insert(ans.end(), all(batch));
        }

        vector<int> newPos;
        for (int j = BLOCK - 1; j < pos.size(); j += BLOCK) newPos.push_back(pos[j]);
        if (newPos.empty() || newPos.back() != N) newPos.push_back(N);
        swap(pos, newPos);
    }

    if (!isLocal) {
        cout << ans.size() << "\n";
        for (auto [a, b] : ans)
            cout << a << " " << b << "\n";
    }

    if (isLocal) {
        int cost = 0;
        for (auto [a, b] : ans) cost += b;
        for (int i = 1; i < ans.size(); i++)
            cost += 1000 * (ans[i - 1].first < ans[i].first);

        cout << "Cost " << cost << endl;
        for (int st = 1, p = 1; p < N; st++, p++) {
            for (auto [a, b] : ans)
                if (p == a) p += b;
            if (p < N) {
                cout << "WA. Couldn't resolve " << st << " " << p << endl;
                exit(0);
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