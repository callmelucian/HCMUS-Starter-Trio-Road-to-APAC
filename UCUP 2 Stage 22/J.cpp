#include <bits/stdc++.h>
using namespace std;

#define all(v) begin(v), end(v)
#define compact(v) v.erase(unique(all(v)), end(v))
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

int n;

void solve(int i) {
    vector<int> vt;
    for(int j = 1; j <= n; ++j) if(j != i && j != i + 1) {
        vt.push_back(j);
        if(vt.size() == 2) break;
    }
    
    cout << "? " << i << ' ' << vt[0] << endl;
    bool state; cin >> state;
    if(state == 0) {
        int state1, state2;
        cout << "? " << i + 1 << ' ' << vt[0] << endl;
        cin >> state1;
        cout << "? " << i + 1 << ' ' << vt[1] << endl;
        cin >> state2;
        if(state1 && state2) {
            cout << "! 2" << endl;
        }
        else cout << "! 1" << endl;
    }
    else {
        cout << "? " << i << ' ' << vt[1] << endl;
        cin >> state;
        if(state == 0) cout << "! 1" << endl;
        else cout << "! 2" << endl;
    }
}

void testcase(){
    cin >> n;
    if(n & 1) {
        cout << "? " << n - 1 << ' ' << n << endl;
        bool state; cin >> state;
        if(state) {
            solve(n - 1);
            return;
        }

    }
    for(int i = 1; i < n; i += 2) {
        cout << "? " << i << ' ' << i + 1 << endl;
        bool state; cin >> state;
        if(state == 1) {
            solve(i);
            return;
        }
    }
    
    cout << "! 1" << endl;
}

int main(){
    // ios_base::sync_with_stdio(0); cin.tie(0);
    int tests = 1;
    cin >> tests;
    while(tests--){
        testcase();
    }
    return 0;
}

/*

2 1
2 3
2 4
2 5

1
5 1
5 2
5 3
5 4


*/