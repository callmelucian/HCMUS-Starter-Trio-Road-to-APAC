#include <bits/stdc++.h>
#ifdef LOCAL
    #include "debug.hpp"
    const bool local = false;
#else 
    #define dbg(...)
    const bool local = false;
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

template<class T> bool minimize (T& a, const T& b) { return (a > b ? a = b, 1 : 0); }
template<class T> bool maximize (T& a, const T& b) { return (a < b ? a = b, 1 : 0); }

mt19937 rng(21);

int rr (int l, int r) {
    return uniform_int_distribution<int>(l, r)(rng);
}

const int M = 1440;

struct Grader {
    vector<int> ans, lastAsk, counter;
    vector<bitset<1440>> sleep, ready;

    Grader (int n) : ans(n, -1), lastAsk(n, -1), counter(n), sleep(n), ready(n) {
        for (auto &bitset : sleep) {
            int idx = rr(0, M - 1);
            if (local) cin >> idx;
            for (int i = idx, j = 0; j < M / 2; j++, i = (i + 1) % M) bitset[i] = true;
            dbg(convert(idx), bitset);
        }
    }

    string itos (int x) {
        string s = "";
        s += char('0' + x / 10);
        s += char('0' + x % 10);
        return s;
    }

    string convert (int x) {
        return itos(x / 60) + ":" + itos(x % 60);
    }

    bool ask (int x, int id) {
        if (ready[id][x]) return sleep[id][x];
        int y = (x + M / 2) % M;

        ready[id][x] = ready[id][y] = true, lastAsk[id] = x, counter[id]++;
        cout << "at " << convert(x) << " check " << id + 1 << endl;
        // dbg("obtained", convert(x), convert(y));
        if (!local) {
            string s; cin >> s;
            sleep[id][x] = (s == "asleep");
            sleep[id][y] = (s == "awake");
        }
        return sleep[id][x];
    }

    void answer (int x, int id) {
        if (counter[id] > 50) {
            cout << "Asked too much! " << counter[id] << endl;
            exit(0);
        }
        ans[id] = x;
    }

    void answer() {
        cout << "answer" << endl;
        for (int u : ans) cout << convert(u) << endl;
    }
};


void testcase() {
    int N; cin >> N;
    Grader grader(N);

    int B = 49;
    vector<int> cp;
    for (int i = 0; i < M / 2; i += B, B--) cp.push_back(i);

    // first half
    vector<pii> range(N, {cp.back(), M / 2});
    for (int i = 0; i < cp.size(); i++) {
        for (int j = 0; j < N; j++) {
            if (range[j].second != M / 2) continue;
            grader.ask(cp[i], j);
            if (i && grader.ask(cp[i - 1], j) != grader.ask(cp[i], j)) range[j] = {cp[i - 1] + M / 2, cp[i] + M / 2};
        }
    }
    dbg(range);

    // second half
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            if (!(range[j].first < i && i <= range[j].second)) continue;
            if (grader.ask(i - 1, j) != grader.ask(i, j)) {
                if (grader.ask(i, j)) grader.answer(i, j);
                else grader.answer((i + M / 2) % M, j);
            }
        }
    }

    grader.answer();
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