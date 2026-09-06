#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
    #include "debug.hpp"
#else
    #define dbg(...) (void(0))
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

vector<pii> solve(int N, int M){
    int atLeast = 4 + (N - 4);
    if(M < atLeast || N < 4){
        return {};
    }
    set<pii> edges;
    edges.insert({1, 2});
    edges.insert({2, 3});
    edges.insert({3, 4});
    edges.insert({1, 4});
    for(int i = 5; i <= N; ++i){
        edges.insert({1, i});
    }
    M -= sz(edges);

    for(int i = 1; i <= N; ++i){
        int j = i + 1;
        while(M > 0 && j <= N){
            if(edges.count({i, j})){
                ++j;
            } else{
                edges.insert({i, j});
                ++j;
                --M;
            }
        }
    }
    return vector<pii>(all(edges));
}

vector<pii> solve2(int N, int M, int K){
    if(N < 5) return {};
    if(K < 4) return {};
    set<pii> edges;
    auto add = [&](int u, int v){
        if(u > v) swap(u, v);
        edges.insert({u, v});
    };
    auto remove = [&](int u, int v){
        if(u > v) swap(u, v);
        edges.erase({u, v});
    };
    add(1, 2);
    add(1, 3);
    add(2, 3);
    add(1, 4);
    add(1, 5);
    add(4, 5);
    //1 -> {6, 7, ..., ...}
    int needMore = K - 4, last = 6 + needMore;
    for(int i = 6; i <= 6 + needMore - 1; ++i){
        add(4, i);
    }
    for(int i = last; i <= N; ++i){
        add(1, i);
    }
    dbg(edges);
    if(sz(edges) > M){
        return {};
    }
    M -= sz(edges);
    //4 -> {x, y}
    //1 -> {x, y}
    for(int i = 6; M > 0 && i + 1 <= last - 1; i += 2){
        remove(4, i);
        remove(4, i + 1);
        add(1, i);
        add(1, i + 1);
        add(i, i + 1);
        --M;
    }
    dbg(edges);
    if(M != 0) return {};
    return vector<pii>(all(edges));
}

void testcase(){
    int N, M, K;
    cin >> N >> M >> K;
    if(K == 0){
        if(M == N - 1){
            for(int i = 2; i <= N; ++i){
                cout << i << ' ' << i - 1 << '\n';
            }
        } else if(M == N && M >= 3){
            cout << 1 << ' ' << 2 << '\n';
            cout << 2 << ' ' << 3 << '\n';
            cout << 3 << ' ' << 1 << '\n';
            for(int i = 4; i <= N; ++i){
                cout << i - 1 << ' ' << i << '\n';
            }
        } else{
            cout << -1 << '\n';
            return;
        }
    } else if(K == N){
        vector<pii> edges = solve(N, M);
        if(edges.empty()){
            cout << -1 << '\n';
        } else{
            for(auto [u, v] : edges){
                cout << u << ' ' << v << '\n';
            }
        }
    } else{
        vector<pii> edges = solve2(N, M, K);
        if(edges.empty()){
            cout << -1 << '\n';
        } else{
            for(auto [u, v] : edges){
                cout << u << ' ' << v << '\n';
            }
        }
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int tests = 1;
    cin >> tests;
    while(tests--){
        testcase();
        cerr << '\n';
    }
    return 0;
}