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

const double pi = acos(-1);

template <class T> int sgn (T x) { return (x > 0) - (x < 0); }
template<class T>
struct Point {
    using P = Point;
    T x, y;
    explicit Point (T x = 0, T y = 0) : x(x), y(y) {}
    bool operator<(P p) const { return tie(x, y) < tie(p.x, p.y); }
    bool operator==(P p) const { return tie(x, y) == tie(p.x, p.y); }

    void operator+= (P p) { *this = *this + p; }
    void operator-= (P p) { *this = *this - p; }

    P operator+ (const P &p) const { return P(x + p.x, y + p.y); }
    P operator- (const P &p) const { return P(x - p.x, y - p.y); }
    P operator* (T d) const { return P(x * d, y * d);}
    P operator/ (T d) const { return P(x / d, y / d); }

    // T dot(P p) const { return x * p.x + y * p.y; }
    // T cross (P p) const { return x * p.y - y * p.x; }
    // T cross (P a, P b) const { return (a - *this).cross(b - *this); }
    T dist2() const { return x * x + y * y; }
    // double dist() const { return sqrt((double)dist2()); }

    double angle() const {
        double a = atan2(y, x);
        return a + (a < 0 ? 2 * pi : 0);
    }
    // P unit() const { return *this / dist(); }
    P perp() const { return P(-y, x); }
    // P normal() const { return perp().unit(); }
    
    friend istream& operator>> (istream &i, P &p) { return i >> p.x >> p.y; }
    friend ostream& operator<< (ostream &o, P p) { return o << '(' << p.x << ", " << p.y << ')'; }
};

template <class P>
vector<pair<P, P>> circleTangents (P c1, double r1, P c2, double r2) {
    P d = c2 - c1;
    double dr = r1 - r2, d2 = d.dist2(), h2 = d2 - dr * dr;
    if (abs(d2) < 1e-6 || h2 < 0) {
        cout << "bruh";
        exit(0);
    }
    vector<pair<P, P>> out;
    for (double sign : {-1, 1}) {
        P v = (d * dr + d.perp() * sqrt(h2) * sign) / d2;
        out.emplace_back(c1 + v * r1, c2 + v * r2);
    }
    // if (h2 == 0) out.pop_back();
    return out;
}

struct BIT {
    vector<int> tr;
    BIT (int sz) : tr(sz + 1) {}

    int p (int k) { return k & -k; }
    
    void update (int k, int val) {
        for (; k < tr.size(); k += p(k)) tr[k] += val;
    }

    int query (int k) {
        int ans = 0;
        for (; k; k -= p(k)) ans += tr[k];
        return ans;
    }

    int query (int l, int r) { return query(r) - query(l - 1); }
};

using P = Point<double>;

void testcase(){
    int N, M; cin >> N >> M;
    double radius; P center; cin >> center >> radius;

    vector<P> emitp(N), recp(M);
    for (P &p : emitp) cin >> p;
    for (P &p : recp) cin >> p;

    using pdd = pair<double, double>;
    function<pdd(P)> get = [&] (P p) {
        auto vec = circleTangents(p, 0, center, radius);
        P a = vec[1].second, b = vec[0].second;
        a -= center, b -= center;
        dbg(p, a, b);
        return make_pair(a.angle(), b.angle());
    };

    vector<pair<pdd, bool>> pts;
    for (int i = 0; i < N; i++) pts.emplace_back(get(emitp[i]), true);
    for (int i = 0; i < M; i++) pts.emplace_back(get(recp[i]), false);

    dbg(pts);

    vector<double> cmp = {-1000};
    for (auto [a, b] : pts)
        cmp.push_back(a.first), cmp.push_back(a.second);
    sort(all(cmp)), compact(cmp);

    auto id = [&] (double x) { return lower_bound(all(cmp), x) - cmp.begin(); };

    
    ll ans = 0;
    auto solve = [&] (bool f) {
        using Event = tuple<double, bool, double>;
        vector<Event> vec;
        for (auto [a, emit] : pts) {
            if (emit) vec.emplace_back(a.first, true, a.second);
            else vec.emplace_back(a.second, false, a.first);
        }
        sort(all(vec), greater<Event>());
        BIT tree(cmp.size() + 2);
        for (auto [prim, type, sec] : vec) {
            if (type) {
                // if (f && prim <= sec) continue;
                tree.update(id(sec), 1);
            }
            else {
                if (sec >= prim) continue;
                if (id(prim) + 1 < cmp.size()) ans += tree.query(id(prim) + 1, (int)cmp.size() - 1);
                if (1 < id(sec)) ans += tree.query(1, id(sec) - 1);
            }
        }
    };
    solve(false);
    for (auto &[a, b] : pts) b = !b;
    solve(true);

    cout << ans << "\n";
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
3 3
0 0 2
-4 3
4 3
0 -4
-4 -3
4 -3
0 4

1 2 
2 -1 3 
5 0 
5 2 -2 -1
*/