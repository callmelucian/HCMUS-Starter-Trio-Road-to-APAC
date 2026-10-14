#include <bits/stdc++.h>
using namespace std;

#define all(v) begin(v), end(v)
#define compact(v) v.erase(unique(all(v)), end(v))
using ll = long long;
using pii = pair<int, int>;

template<class T> bool minimize(T& a, const T& b){ return b < a ? a = b, true : false; }
template<class T> bool maximize(T& a, const T& b){ return b > a ? a = b, true : false; }

#ifdef LOCAL
    #include "debug.hpp"
#else 
    #define dbg(...) ((void)0)
#endif //LOCAL

mt19937 rng(21);

int rr (int l, int r) {
    return uniform_int_distribution<int>(l, r)(rng);
}

void testcase(){
    int N = rr(1, 10);
    vector<int> A(N);
    iota(all(A), 1), shuffle(all(A), rng);

    ofstream inp("F.in");
    inp << N << "\n";
    for (int i = 0; i < N; i++) inp << A[i] << " ";
    inp << "\n";
    inp.close();

    system("./F < F.in > F.out");
    system("./Fb < F.in > F.ans");
    if(system("diff F.out F.ans") != 0){
        cout << "Failed\n";
        exit(0);
    }
    else cout << "Accepted" << endl;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int tests = 100;
    // cin >> tests;
    while(tests--){
        testcase();
    }
    return 0;
}