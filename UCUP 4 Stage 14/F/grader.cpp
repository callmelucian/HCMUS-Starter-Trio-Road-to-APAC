#include <bits/stdc++.h>
#ifdef LOCAL
    #include "../debug.hpp"
#else 
    #define dbg(...)
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

template<class T> bool minimize(T& a, const T& b){  return (a > b ? a = b, 1 : 0); }
template<class T> bool maximize(T& a, const T& b){  return (a < b ? a = b, 1 : 0); }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int rint(int l, int r){
    return uniform_int_distribution<int>(l, r)(rng);
}

void shuffleFunc(){
    ifstream input("out.txt");
    vector<pii> edges;
    int u, v, n = 0;
    while(input >> u >> v){
        edges.emplace_back(u, v);
        maximize(n, u);
        maximize(n, v);
    }
    vector<int> label(n + 1);
    iota(all(label), 0);
    shuffle(begin(label) + 1, end(label), rng);
    int m = sz(edges);
    ofstream output("sec.txt");
    output << 2 << '\n';
    output << n << ' ' << m << '\n';
    for(auto [u, v] : edges){
        u = label[u], v = label[v];
        output << u << ' ' << v << '\n';
    }
}
int main() {
    system("F.exe < in.txt > out.txt");
    shuffleFunc();
    int code = system("F.exe < sec.txt");
    if(code != 0){
        cout << "failed\n";
    }
    return 0;
}