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

struct Score {
    int ac, pen;
    Score() : ac(0), pen(0) {}
    Score (int a, int b) : ac(a), pen(b) {}

    Score operator+ (const Score &o) const { return Score(ac + o.ac, pen + o.pen); }
    Score operator- (const Score &o) const { return Score(ac - o.ac, pen - o.pen); }

    void operator+= (const Score &other) { *this = *this + other; }
    void operator-= (const Score &other) { *this = *this - other; }

    bool operator< (const Score &o) const { return (ac == o.ac ? pen < o.pen : ac > o.ac); }
    bool operator== (const Score &o) const { return ac == o.ac && pen == o.pen; }

    friend ostream& operator<< (ostream &o, const Score &s) { return o << s.ac << " " << s.pen; }
};

struct Submission {
    ll team;
    char problem;
    int tm;
    string verd;

    Submission() : problem(0), tm(0) {}
    Submission (ll c, char p, int t, string s) : team(c), problem(p), tm(t), verd(s) {}
};

vector<string> names, inp;

int hashing (string s) {
    return lower_bound(all(names), s) - names.begin();
}

void testcase(){
    names.clear(), inp.clear();

    int M; cin >> M;
    vector<Submission> vec(M);
    for (auto &it : vec) {
        string team; cin >> team >> it.problem >> it.tm >> it.verd;
        inp.push_back(team), names.push_back(team);
    }
    sort(all(names)), compact(names);
    for (int i = 0; i < M; i++) vec[i].team = hashing(inp[i]);

    map<ll, Score> scoreboard;
    map<ll, set<char>> solvedGlobal;
    map<ll, map<char,int>> submission;
    map<ll, map<char, Score>> penalty;

    for (const auto &it : vec) {
        if (it.verd == "rejected") submission[it.team][it.problem]++;
        if (it.verd == "rejected" || solvedGlobal[it.team].count(it.problem)) continue;
        penalty[it.team][it.problem] = Score(1, it.tm + 20 * submission[it.team][it.problem]);
        scoreboard[it.team] += penalty[it.team][it.problem];
        solvedGlobal[it.team].insert(it.problem);
    }
    for (const auto &it : vec)
        if (!scoreboard.count(it.team)) scoreboard[it.team] = Score(0, 0);

    map<Score, set<ll>> freq, allow;
    for (auto [team, score] : scoreboard) freq[score].insert(team);

    int goodCnt = 0;
    for (auto [team, solveSet] : solvedGlobal)
        goodCnt += (bool)solveSet.size();
    
    auto getBound = [&] (int n) {
        return min(35, n / 10 + (n % 10 ? 1 : 0));
    };
    set<ll> goodTeams;
    auto setAllow = [&] (ll changedTeam, int n, Score newScore) {
        if (changedTeam != -1) freq[newScore].insert(changedTeam);
        auto it = freq.begin();
        for (int lt = 0; lt < getBound(n) && it != freq.end(); it++) {
            allow[it->first].insert((it->first == newScore ? -1 : changedTeam));
            if (it->first == newScore) goodTeams.insert(changedTeam);
            lt += it->second.size() - (it->first == newScore ? 0 : it->second.count(changedTeam));
        }
        if (changedTeam != -1) freq[newScore].erase(changedTeam);
    };
    auto searchName = [&] (ll team) {
        return names[team];
    };

    for (auto [team, score] : scoreboard) dbg(searchName(team), score);

    // no submisisons changed
    setAllow(-1, goodCnt, Score(-1, -1));

    // 1 submission changed
    map<ll, set<char>> solved;
    submission.clear();
    for (const auto &it : vec) {
        if (solved[it.team].count(it.problem)) continue;
        int n = goodCnt;
        Score delta = Score(0, 0) - penalty[it.team][it.problem];

        if (it.verd == "rejected") {
            delta += Score(1, it.tm + 20 * submission[it.team][it.problem]);
            submission[it.team][it.problem]++;
            n += (solvedGlobal[it.team].empty());
        }

        else {
            int cntAC = 0, counter = -1;
            for (const auto &oth : vec) {
                if (oth.team == it.team && oth.problem == it.problem)
                    cntAC += (it.verd == "accepted"), counter++;
                if (cntAC == 2) {
                    delta += Score(1, it.tm + 20 * counter);
                    break;
                }
            }
            solved[it.team].insert(it.problem);
            if (cntAC < 2 && solvedGlobal[it.team].size() == 1) n--;
        }

        dbg(delta, searchName(it.team), scoreboard[it.team] + delta, n, getBound(n));
        if (delta.ac || delta.pen) {
            scoreboard[it.team] += delta;
            setAllow(it.team, n, scoreboard[it.team]);
            scoreboard[it.team] -= delta;
        }

        // scoreboard[it.team] += penalty[it.team][it.problem];
    }

    dbg(allow);

    // finalize result
    for (auto &[score, exceptSet] : allow) {
        if (exceptSet.empty() || exceptSet.size() >= 2)
            for (ll team : freq[score]) goodTeams.insert(team);
        else {
            ll exception = *exceptSet.begin();
            for (ll team : freq[score])
                if (team != exception) goodTeams.insert(team);
        }
    }

    vector<string> ans;
    for (auto u : names)
        if (goodTeams.count(hashing(u))) ans.push_back(u);
    
    // output
    cout << ans.size() << "\n";
    for (auto u : ans) cout << u << " ";
    cout << "\n";
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);

    int tests = 1;
    cin >> tests;

    while(tests--){
        testcase();
    }
    return 0;
}
