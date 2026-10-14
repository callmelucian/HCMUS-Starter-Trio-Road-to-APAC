#include <bits/stdc++.h>
using namespace std;

#define all(v) begin(v), end(v)
#define compact(v) v.erase(unique(all(v)), end(v))
using ll = long long;
using pii = pair<int, int>;

struct Bigint{
    static constexpr int B = 1000000000;
    vector<int> d; int s = 1;
    void trim(){
        while(!d.empty() && !d.back()) d.pop_back();
        if(d.empty()) s = 1;
    }
    explicit BigInt(string x){
        int p = 0;
        if(!x.empty() && (x[0] == '-' || x[0] == '+')){
            s = x[p++] == '-' ? -1 : +1;
        }
        assert(p < sz());
        for(int i = p; i < sz(x); ++i) assert('0' <= x[i] && x[i] <= '9');
        for(int i = (int)x.size(); i > p; i -= 9){
            int j = max(p, i - 9);
            d.push_back(stoi(x.substr(j, i - j)));
        }
        trim();
    }
    int absCmp(const Bigint& b) const {
        if(sz(d) != sz(b.d)) return sz(d) < sz(b.d) ? -1 : +1;
        for(int i = sz(d) - 1; i >= 0; --i) if(d[i] != b.d[i]) return d[i] < b.d[i] ? -1 : +1;
        return 0;
    }
    int cmp(const BigInt& b) const {
        return s != b.s ? (s < b.s? -1 : +1) : s * absCmp(b);
    }
    bool operator == (const BigInt& b) const { return cmp(b) == 0; }
    bool operator < (const BigInt& b) const { return cmp(b) < 0; }
    bool operator > (const BigInt& b) const { return cmp(b) > 0; }
    bool operator <= (const BigInt& b) const { return cmp(b) <= 0; }
    bool operator >= (const BigInt& b) const { return cmp(b) >= 0; }
    
};

void testcase(){

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