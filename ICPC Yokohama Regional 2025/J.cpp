#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
    #include "debug.hpp"
#else
    #define dbg(...) (void(0))
#endif

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
using db = double;

int N, M, row[1010];
char ch[1010][1010], ans[1010][1010], a[1010][1010];

const int dr[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
const int dc[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

bool ok (int i, int j) {
    return 1 <= i && i <= N && 1 <= j && j <= M;
}

bool trySolve (bool mirror) {
    // reset
    for (int i = 1; i <= N; i++) row[i] = 0;
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= M; j++) ans[i][j] = '.';

    // check if we're mirroring
    if (mirror) {
        for (int i = 1; i <= N; i++)
            for (int j = 1; j <= M; j++) a[j][i] = ch[i][j];
        swap(N, M);
        for (int i = 1; i <= N; i++)
            for (int j = 1; j <= M; j++) ch[i][j] = a[i][j];
    }

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            if (ch[i][j] == 'C') row[i] |= (1 << (j & 1));
            if (ch[i][j] == 'I' || ch[i][j] == 'P') row[i] |= (1 << ((j & 1) ^ 1));
        }
        dbg(i, row[i]);
    }

    for (int i = 1; i <= N; i++)
        if (row[i] == 3) return false;

    dbg("trying", mirror);
    // fill C
    for (int i = 1; i <= N; i++) {
        int start = ((row[i] & 1) ? 2 : 1);
        for (int j = start; j <= M; j += 2) ans[i][j] = 'C';
    }
    
    // fill I/P
    int si = 1, sj = 1, type = 'I';
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= M; j++)
            if (ans[i][j] != 'C') si = i, sj = j;
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= M; j++)
            if (ch[i][j] == 'I' || ch[i][j] == 'P') si = i, sj = j, type = ch[i][j];

    dbg(si, sj, type);

    vector<pii> qu = {{si, sj}};
    ans[si][sj] = type;

    for (int _ = 0; _ < qu.size(); _++) {
        int i, j; tie(i, j) = qu[_];
        dbg("vis", i, j, ans[i][j]);
        for (int k = 0; k < 8; k++) {
            int i2 = i + dr[k], j2 = j + dc[k];
            if (!ok(i2, j2) || ans[i2][j2] != '.') continue;
            ans[i2][j2] = (ans[i][j] == 'I' ? 'P' : 'I');
            qu.emplace_back(i2, j2);
        }
    }

    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= M; j++)
            if (ch[i][j] != '?' && ans[i][j] != ch[i][j]) return false;


    if (mirror) {
        for (int i = 1; i <= N; i++)
            for (int j = 1; j <= M; j++) a[j][i] = ans[i][j];
        swap(N, M);
        for (int i = 1; i <= N; i++)
            for (int j = 1; j <= M; j++) ans[i][j] = ch[i][j];
    }

    cout << "yes\n";
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) cout << ans[i][j];
        cout << "\n";
    }
    return true;
}

void testcase(){
    cin >> N >> M;
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= M; j++) cin >> ch[i][j];

    // preprocess
    // for (int i = 1; i + 1 <= N; i++)
    //     for (int j = 1; j + 1 <= N; j++)
    //         tryFill({ch[i][j], ch[i][j + 1], ch[i + 1][j], ch[i + 1][j + 1]});

    if (trySolve(false)) return;
    if (trySolve(true)) return;

    cout << "no\n";
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

/*
3
5 7
I?I?I?I
?P?P?P?
I?I?I?I
?P?P?P?
I?I?I?I
4 4
ICPC
CPCI
ICPC
CPCI
2 2
??
??
*/