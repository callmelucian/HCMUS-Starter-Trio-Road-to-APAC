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

struct P{
    ll x, y;
    P() : x(0), y(0) {}
    P(ll _x, ll _y) : x(_x), y(_y) {}
    P operator + (P p) const {
        return P(x + p.x, y + p.y);
    }
    P operator - (P p) const { 
        return P(x - p.x, y - p.y);
    }
    ll cross(P a){ return x * a.y - a.x * y; }
    ll cross(P a, P b){ return (a - *this).cross(b - *this); }

    bool operator< (const P &o) const {
        if (x == o.x) return y < o.y;
        return x < o.x;
    }

    friend bool turnLeft (P a, P b, P c) { return a.cross(b, c) > 0; }
    friend bool turnRight (P a, P b, P c) { return a.cross(b, c) < 0; }

    friend istream& operator>> (istream &instream, P &point) {
        return instream >> point.x >> point.y, instream;
    }

    friend ostream& operator<< (ostream &outstream, const P &point) {
        return outstream << "(" << point.x << ", " << point.y << ")", outstream;
    }
};

int side(P a){
    if(a.y > 0) return 0;
    if(a.y == 0) return a.x >= 0 ? 0 : 1;
    return 1;
}

bool cmp(P a, P b){
    if(side(a) != side(b)) return side(a) < side(b);
    return a.cross(b) > 0;
}
    
void testcase() {
    int n; cin >> n;
    vector<P> points(n);
    vector<pair<P, int>> hull;
    vector<int> inHull(n);
    for (int i = 0; i < n; i++) cin >> points[i];
    sort(all(points));

    // build convex hull
    for (int i = 0; i < n; i++) {
        while (hull.size() >= 2 && turnLeft(hull[hull.size() - 2].first, hull.back().first, points[i]))
            inHull[hull.back().second]--, hull.pop_back();
        hull.emplace_back(points[i], i), inHull[i]++;
    }
    for (int i = n - 2; i >= 0; i--) {
        while (hull.size() >= 2 && turnLeft(hull[hull.size() - 2].first, hull.back().first, points[i]))
            inHull[hull.back().second]--, hull.pop_back();
        hull.emplace_back(points[i], i), inHull[i]++;
    }
    if (hull.size()) inHull[hull.back().second]--, hull.pop_back();

    dbg(hull);

    // choose pivots
    int ans = 0;
    for (int pivot = 0; pivot < n; pivot++) {
        if (inHull[pivot]) continue;
        vector<P> newPoints, newHull;
        for (auto p : hull) newHull.push_back(p.first - points[pivot]);
        for (int i = 0; i < n; i++)
            if (!inHull[i] && i != pivot) newPoints.push_back(points[i] - points[pivot]);
        sort(all(newPoints), cmp), sort(all(newHull), cmp);

        dbg("pivot", points[pivot]);
        dbg(newPoints);
        dbg(newHull);

        int start = 0, contrib = 0;
        while (start < newPoints.size() && cmp(newPoints[start], newHull[0])) start++;

        int itr = start;
        for (int i = 1; i < newHull.size(); i++) {
            if (itr == newPoints.size() || !cmp(newPoints[itr], newHull[i])) ans++, contrib++;
            else {
                while (itr < newPoints.size() && cmp(newPoints[itr], newHull[i])) itr++;
            }
        }
        if (itr == newPoints.size() && !start) ans++, contrib++;
    }

    cout << ans + 1 << "\n";
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
  
    int TC = 1;
    while (TC--) {
        testcase();
    }

    return 0;
}