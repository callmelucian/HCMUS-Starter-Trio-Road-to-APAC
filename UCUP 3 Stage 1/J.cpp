#include <bits/stdc++.h>
using namespace std;

#define all(v) begin(v), end(v)
#define rall(v) rbegin(v), rend(v)
#define sz(v) (int)v.size()
#define pb push_back
#define eb emplace_back
#define compact(v) v.erase(unique(all(v)), end(v))
template<class T> bool minimize(T& a, const T& b){ return a > b ? a = b, 1 : 0; }
template<class T> bool maximize(T& a, const T& b){ return a < b ? a = b, 1 : 0; }
using ll = long long;
using db = double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#ifdef LOCAL 
    #include "debug.hpp"
#else 
    #define dbg(...) ((36))
#endif //LOCAL

mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
    return uniform_int_distribution<int>(l, r)(rng);
}

bool check(vector<int> &L, vector<int> &R, int &sumL, int &sumR) {
    unordered_set<int> st;
    int gap = sumR - 1'000'000'000;
    for(int &x: L) st.insert(x);
    for(int &x: R) if(st.count(x - gap)) {
        for(int &y: L) if(y == x - gap) {
            y = x; break;
        }
        x = x - gap;
        sumL = sumR = 1'000'000'000;
        return true;
    }
    return false;
}

vector<int> genSeq (int n, int sum) { // n << sum
    set<int> s = {sum};
    while (s.size() < n) s.insert(rnd(1, sum - 1));

    vector<int> v;
    int last = 0;
    for (int u : s) v.push_back(u - last), last = u;
    shuffle(all(v), rng);
    return v;
}

bool solve (vector<int> &L, vector<int> &R) {
    int sumL = 0, sumR = 0;
    for(int &x: L) sumL += x;
    for(int &x: R) sumR += x;
    if (sumL > sumR) swap(sumL, sumR), swap(L, R);

    while (true) {
        dbg(sumL, sumR);

        bool swapped = false;
        for (int ii = 0; ii < L.size(); ii++) {
            for (int jj = 0; jj < R.size(); jj++) {
                if (R[jj] <= L[ii] || (R[jj] - L[ii]) * 2 > sumR - sumL) continue;
                sumL -= L[ii], sumR -= R[jj];
                swap(L[ii], R[jj]);
                sumL += L[ii], sumR += R[jj];
                swapped = true;
            }
        }
        if (!swapped) return false;

        // if(check(L, R, sumL, sumR)) break;
        shuffle(L.begin(), L.end(), rng);
        shuffle(R.begin(), R.end(), rng);
        // cerr << "fck" << endl;
        // while(1) {
        //     swap(L[0], L[rnd(0, m)]);
        //     swap(R[0], R[rnd(0, m)]);
        //     int new_sumL = sumL - L[0] + R[0];
        //     int new_sumR = sumR - R[0] + L[0];
        //     cerr << abs(sumL - sumR) << ' ' << abs(new_sumL - new_sumR) << endl; 
        //     if(abs(sumL - 1'000'000'000) <= abs(new_sumL - new_sumR)) continue;
        //     swap(L[0], R[0]);
        //     sumL = new_sumL;
        //     sumR = new_sumR;
        //     break;
        // }
        if (sumL == sumR) return true;
    }
    return false;
}

void testcase(){
    int n = 100;
    // cin >> n;
    // vector<int> a(n);
    // for(int i = 0; i < n; ++i) cin >> a[i];
    
    vector<int> a = genSeq(n / 2, 1'000'000'000);
    vector<int> tmp = genSeq(n / 2, 1'000'000'000);
    a.insert(a.end(), all(tmp));
    shuffle(all(a), rng);
    // for(int i = 1; i <= n / 2; ++i) a[i] = a[i + n / 2] = X[i - 1];

    while (true) {
        vector<int> L, R;
        shuffle(all(a), rng);
        for(int i = 0; i < n / 2; ++i) L.push_back(a[i]);
        for(int i = n / 2; i < n; ++i) R.push_back(a[i]);

        if (solve(L, R)) {
            cout << L.size() << " ";
            for(int x: L) {
                for(int i = 0; i < n; ++i) if(a[i] == x) {
                    cout << i << ' ';
                    a[i] = -1;
                }
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
/*
10
386413329 88494216 245947398 316438989 192751270 204627269 65749456 3938400 150458676 345180997
*/