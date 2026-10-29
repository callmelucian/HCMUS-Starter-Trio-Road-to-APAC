#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using tpl = tuple<int,int,int>;

#define all(v) begin(v), end(v)
#define sz(v) (int)v.size()
#define compact(v) v.erase(unique(all(v)), end(v))

template<class T> bool maximize (T &a, const T &b) { return b > a ? a = b, true : false; }
template<class T> bool minimize (T &a, const T &b) { return b < a ? a = b, true : false; }

#ifdef LOCAL
    #include "debug.hpp"
#else 
    #define dbg(...) ((void)0)
#endif //LOCAL

const int MAX = 1e5 + 5;
const int mod = 1e9 + 9;
struct mint{
    int v;
    mint(int _v = 0) : v(_v) {refine();}

    void refine() {
        if (abs(v) >= mod) v %= mod;
        if (v < 0) v += mod;
    }

    mint& operator += (const mint& o){
        v += o.v;
        if(v >= mod) v -= mod;
        return *this;
    }
    mint& operator -= (const mint& o){
        v -= o.v;
        if(v < 0) v += mod;
        return *this;
    }
    mint& operator *= (const mint& o){
        v = 1LL * v * o.v % mod;
        return *this;
    }
    mint power(ll n) const {
        mint res(1), bs = *this;
        for(; n > 0; n /= 2, bs *= bs){
            if(n & 1) res *= bs;
        }
        return res;
    }
    mint inv() const {
        return power(mod - 2);
    }
    mint& operator /= (const mint& o){
        return *this *= o.inv();
    }
    friend mint operator + (mint a, const mint& b){ return a += b; }
    friend mint operator - (mint a, const mint& b){ return a -= b; }
    friend mint operator * (mint a, const mint& b){ return a *= b; }
    friend mint operator / (mint a, const mint& b){ return a /= b; }
    friend bool operator == (const mint& a, const mint& b){ return a.v == b.v; }
    friend ostream& operator << (ostream& op, const mint& o){ return op << o.v; }
};

const int base = 37;
const int blockSize = 330;

struct Node{
    int at[3], l, r; 
};  

int N, Q;
string S[3];
mint pwBase[MAX], h[3][MAX];
vector<Node> blocks;

mint query(int t, int l, int r){
    return h[t][r] - h[t][l - 1] * pwBase[r - l + 1];
}

void rebuild(){
    string T[3];
    T[0] = "?";
    T[1] = "?";
    T[2] = "?";
    for(int i = 0; i < sz(blocks); ++i){
        for(int j = 0; j < 3; ++j){
            for(int k = blocks[i].l; k <= blocks[i].r; ++k){
                T[j] += S[blocks[i].at[j]][k];
            }
        }
    }
    swap(S[0], T[0]);
    swap(S[1], T[1]);
    swap(S[2], T[2]);
}

void build(){
    if(!blocks.empty()){
        rebuild();
        blocks.clear();
    }
    for(int k = 0; k < 3; ++k){
        for(int i = 1; i <= N; ++i){
            h[k][i] = h[k][i - 1] * base + (S[k][i] - 'a' + 1);        
        }
    }

    for(int l = 1; l <= N; l += blockSize){
        int r = min(N, l + blockSize - 1);
        blocks.push_back(Node{{0, 1, 2}, l, r});
    }
}

int cut(int pos){
    if(pos == 0) return -1;
    int L = 0, R = 0;
    for(int i = 0; i < sz(blocks); ++i){
        L = R + 1;
        R = L + blocks[i].r - blocks[i].l;
        if(R < pos) continue;
        if(R == pos) return i;
        int start = blocks[i].l;
        int residual = pos - L;
        blocks.insert(blocks.begin() + i, blocks[i]);
        blocks[i].r = start + residual;
        blocks[i + 1].l = start + residual + 1;
        return i;
    }
    assert(false);
    return -1;
}

int findLCP(int u, int v, int lo, int hi){
    int l = 1, r = hi - lo + 1, lcp = 0;
    while(l <= r){
        int mid = l + r >> 1;
        if(query(u, lo, lo + mid - 1) == query(v, lo, lo + mid - 1)) lcp = mid, l = mid + 1;
        else r = mid - 1;
    }
    return lcp;
}

int compare(int l, int r, int x, int y){
    for(int i = l; i <= r; ++i){
        int u = blocks[i].at[x];
        int v = blocks[i].at[y];
        if(query(u, blocks[i].l, blocks[i].r) == query(v, blocks[i].l, blocks[i].r)){

        } else{
            int lcp = findLCP(u, v, blocks[i].l, blocks[i].r);
            if(S[u][blocks[i].l + lcp] > S[v][blocks[i].l + lcp]){
                return 1;
            } else{
                return 0;
            }
        }
    }
    return 0;
}

void swapRange(int l, int r, int x, int y){
    for(int i = l; i <= r; ++i){
        swap(blocks[i].at[x], blocks[i].at[y]);
    }
}

void testcase(){
    cin >> N >> Q;
    cin >> S[0] >> S[1] >> S[2];

    pwBase[0] = 1;
    for(int i = 1; i <= N; ++i){
        pwBase[i] = pwBase[i - 1] * base;
    }

    S[0] = '?' + S[0];
    S[1] = '?' + S[1];
    S[2] = '?' + S[2];
    build();
    while(Q--){
        int l, r;
        cin >> l >> r;

        int p = cut(l - 1) + 1, q = cut(r);
        if(compare(p, q, 0, 1)){
            //A > B
            swapRange(p, q, 0, 1);
        } 

        if(compare(p, q, 0, 2)){
            //A > B
            swapRange(p, q, 0, 2);
        }

        if(compare(p, q, 1, 2)){
            //B > C
            swapRange(p, q, 1, 2);
        }

        if(sz(blocks) >= 3 * blockSize){
            build();
        }
    }

    build();
    for(int i = 0; i < 3; ++i){
        string res = S[i].substr(1, N);
        cout << res << '\n';
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t = 1;
    // cin >> t;
    while(t--){
        testcase();
    }
    return 0;
}