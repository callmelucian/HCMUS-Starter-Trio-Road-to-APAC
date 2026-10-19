#include <bits/stdc++.h>
using namespace std;

#define all(v) begin(v), end(v)
#define sz(v) (int)v.size()
#define compact(v) v.erase(unique(all(v)), end(v))
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
template<class T> bool minimize(T& a, const T& b){ return a > b ? a = b, 1 : 0; }
template<class T> bool maximize(T& a, const T& b){ return a < b ? a = b, 1 : 0; }

#ifdef LOCAL
    #include "debug.hpp"
#else 
    #define dbg(...) ((void)0)
#endif //LOCAL

template<class T> int sgn(T x){ return (x > 0) - (x < 0); }
template<class T> 
struct Point{
    typedef Point P;
    T x, y;
    Point() : x(0), y(0) {}
    Point(T x, T y) : x(x), y(y) {}
    bool operator < (const P& o) const { return tie(x, y) < tie(o.x, o.y); }
    bool operator == (const P& o) const { return tie(x, y) == tie(o.x, o.y); }
    P operator + (P p) const { return P(x + p.x, y + p.y); }
    P operator - (P p) const { return P(x - p.x, y - p.y); }
    P operator * (T d) const { return P(x * d, y * d); }
    P operator / (T d) const { return P(x / d, y / d); }
    T dot(P p) const { return (x * p.x) + (y * p.y); }
    T cross(P p) const { return x * p.y - y * p.x; }
    T cross(P a, P b) const { return (a - *this).cross(b - *this); }
    P perp() const { return P(-y, x); }
    friend ostream& operator << (ostream& op, const P& p){
        return op << '(' << p.x << ", " << p.y << ')';
    } 
};  

template<class P> 
vector<P> convexHull(vector<P> pts){
    sort(all(pts));
    compact(pts);
    int n = sz(pts);
    if(n <= 1) return pts;
    vector<P> hull(2 * n);
    int k = 0;
    for(P p : pts){
        while(k >= 2 && hull[k - 2].cross(hull[k - 1], p) <= 0) --k;
        hull[k++] = p;
    }
    for(int i = n - 2, lower = k + 1; i >= 0; --i){
        P p = pts[i];
        while(k >= lower && hull[k - 2].cross(hull[k - 1], p) <= 0) --k;
        hull[k++] = p;
    }
    hull.resize(k - 1);
    return hull;
}

template<class P>
int sideOfLine(P s, P e, P p){ return sgn(s.cross(e, p)); }

template<class P> bool pointOnSegment(P s, P e, P p){
    return p.cross(s, e) == 0 && (s - p).dot(e - p) <= 0;
}

template<class P> 
bool pointInHull(const vector<P>& l, P p, bool strict){
    int a = 1, b = sz(l) - 1, r = !strict;
    if(sz(l) < 3) return r && pointOnSegment(l[0], l.back(), p);
    if(sideOfLine(l[0], l[a], l[b]) > 0) swap(a, b);
    if(sideOfLine(l[0], l[a], p) >= r || sideOfLine(l[0], l[b], p) <= -r) return false;
    while(abs(a - b) > 1){
        int c = (a + b) / 2;
        (sideOfLine(l[0], l[c], p) > 0 ? b : a) = c;
    }
    return sgn(l[a].cross(l[b], p)) < r;
}

#define cmp(i, j) sgn(dir.perp().cross(poly[(i) % n] - poly[(j) % n]))
#define extr(i) cmp(i + 1, i) >= 0 && cmp(i, i - 1 + n) < 0
template<class P> int extrVertex(vector<P>& poly, P dir){
    int n = sz(poly), lo = 0, hi = n;
    if(extr(0)) return 0;
    while(lo + 1 < hi){
        int m = (lo + hi) / 2;
        if(extr(m)) return m;
        int ls = cmp(lo + 1, lo), ms = cmp(m + 1, m);
        (ls < ms || (ls == ms && ls == cmp(lo, m)) ? hi : lo) = m; 
    }
    return lo;
}

#define cmpL(i) sgn(a.cross(poly[i], b))
template<class P>
int lineHullSide(P a, P b, vector<P>& poly){
    int endA = extrVertex(poly, (a - b).perp());
    int endB = extrVertex(poly, (b - a).perp());
    if(cmpL(endA) < 0) return -1;
    else if(cmpL(endB) > 0) return 1;
    return 0;
}

template<class P>
bool segmentIntersect(P a, P b, P c, P d){
    // dbg(a, b, c, d);
    int oa = c.cross(d, a), ob = c.cross(d, b);
    int oc = a.cross(b, c), od = a.cross(b, d);
    // dbg(oa, ob, oc, od);
    if(sgn(oa) * sgn(ob) < 0 && sgn(oc) * sgn(od) < 0) return true;
    if(pointOnSegment(a, b, c)) return true;
    if(pointOnSegment(a, b, d)) return true;
    if(pointOnSegment(c, d, a)) return true;
    if(pointOnSegment(c, d, b)) return true;
    return false;
}

template<class P>
tuple<P, P, P, P> findIntersection(P a, P b, vector<P>& poly){
    // dbg(a, b, poly);
    for(int i = 0; i < sz(poly); ++i){
        int j = (i + 1) % sz(poly);
        if(segmentIntersect(a, b, poly[i], poly[j])) return {poly[i], poly[j], a, b};
    }
    assert(false);
}

template<class P>
tuple<P, P, P, P> solveInside(vector<P> small, vector<P> big){
    int m = sz(big);
    auto findNext = [&](int x, int n){
        if(x == n - 1) return 0;
        else return x + 1;
    };
    auto checkSide = [&](int i, int j){
        return lineHullSide(big[i], big[j], small) == -1;
    };

    for(int i = 0; i < sz(big); ++i){
        for(int j = findNext(i, m); j != i; j = findNext(j, m)){
            cerr << lineHullSide(big[i], big[j], small) << ' ';
        }
        cerr << '\n';
    }

    int j = 1;
    for(int i = 0; i < sz(big); ++i){
        while(true){
            int nj = findNext(j, m);
            if(j == i || checkSide(i, nj)) j = nj;
            else break;
        }
        // int u = lineHullSide(big[i], big[j], small);
        int v = lineHullSide(big[i], big[findNext(j, m)], small);
        // dbg(i, j, u, v);
        if(v == 0){
            auto res = findIntersection(big[i], big[findNext(j, m)], small);
            dbg(res);
            return res;
        }
    }
    return {P(), P(), P(), P()};
}

using P = Point<ll>;
void testcase(){
    int N, M;
    cin >> N;
    vector<P> A(N);
    map<pii, int> ptA, ptB;
    for(int i = 0; i < N; ++i){
        cin >> A[i].x >> A[i].y;
        ptA[make_pair(A[i].x, A[i].y)] = i + 1;
    }
    dbg(A);
    cin >> M;
    vector<P> B(M);
    for(int i = 0; i < M; ++i){
        cin >> B[i].x >> B[i].y;
        ptB[make_pair(B[i].x, B[i].y)] = i + 1;
    }

    bool hasAnswer = false;
    {
        for(int i = 0; i < N; ++i){
            for(int j = i + 1; j < N; ++j){
                for(int x = 0; x < M; ++x){
                    for(int y = x + 1; y < M; ++y){
                        if(segmentIntersect(A[i], A[j], B[x], B[y])){
                            hasAnswer = true;
                        }
                    }
                }
            }
        }
    }

    dbg(B);
    A = convexHull(A);
    B = convexHull(B);

    auto printAnswer = [&](P a, P b, P c, P d){
        if(a == b && b == c && c == d){
            if(hasAnswer){
                cerr << "Failed !!!\n";
                exit(1);
            }
            cout << -1 << '\n';
            return;
        }
        if(!hasAnswer){
            cerr << "failedfd\n";
            exit(2);
        }
        cout << ptA[make_pair(a.x, a.y)] << ' ';
        cout << ptA[make_pair(b.x, b.y)] << ' ';
        cout << ptB[make_pair(c.x, c.y)] << ' ';
        cout << ptB[make_pair(d.x, d.y)] << '\n';
    };  

    dbg(A, B);
    N = sz(A); M = sz(B);
    
    if(sz(A) == 2){
        for(int i = 0; i < M; ++i){
            P u = B[i], v = B[(i + 1) % M];
            if(segmentIntersect(u, v, A[0], A[1])){
                printAnswer(A[0], A[1], u, v);
                return;
            }
        }
    }
    if(sz(B) == 2){
        for(int i = 0; i < N; ++i){
            P u = A[i], v = A[(i + 1) % N];
            if(segmentIntersect(u, v, B[0], B[1])){
                printAnswer(u, v, B[0], B[1]);
                return;
            }
        }
    }
    // cerr << "Done build Hull !\n";
    vector<int> checkA(N), checkB(M);
    int cntA = 0, cntB = 0;
    for(int i = 0; i < N; ++i){
        checkA[i] = pointInHull(B, A[i], false);
        cntA += checkA[i];
    }
    for(int i = 0; i < M; ++i){
        checkB[i] = pointInHull(A, B[i], false);
        cntB += checkB[i];
    }
    // cerr << "Done PointInHull !\n";

    if(!cntA && !cntB){
        cout << -1 << '\n';
    } else if(cntA == N){
        //A is in B
        auto [a, b, c, d] = solveInside(A, B);
        printAnswer(a, b, c, d);
    } else if(cntB == M){
        //B is in A
        auto [c, d, a, b] = solveInside(B, A);
        printAnswer(a, b, c, d);
    } else{
        //intersection
        if(cntA > 0){
            P u, v;
            for(int i = 0; i < N; ++i){
                if(checkA[i]) u = A[i];
                else v = A[i];
            }

            for(int i = 0; i < M; ++i){
                P p = B[i], q = B[(i + 1) % M];
                if(segmentIntersect(u, v, p, q)){
                    printAnswer(u, v, p, q);
                    return;
                }
            }
        } else if(cntB > 0){
            P u, v;
            for(int i = 0; i < M; ++i){
                if(checkB[i]) u = B[i];
                else v = B[i];
            }
            for(int i = 0; i < N; ++i){
                P p = A[i], q = A[(i + 1) % N];
                if(segmentIntersect(u, v, p, q)){
                    printAnswer(p, q, u, v);
                    return;
                }
            }
        }
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t = 1;
    cin >> t;
    while(t--){
        testcase();
    }
    return 0;
}

/*

1
3
0 0
3 0
0 3
2
1 2
2 1

10
7 -2
9 -1
10 0
10 4
8 7
4 7
2 5
1 3
2 1
4 -1
8
5 0
4 2
4 3
5 4
7 5
8 3
8 1
7 0

4
0 0
4 0
3 3
1 3
5
-1 1
5 1
2 -1
2 4
6 3

4
0 0
1 0
0 1
1 1
4
5 5
6 5
5 6
6 6

3
0 0
4 0
0 2
3
4 -2
4 2
6 1

*/