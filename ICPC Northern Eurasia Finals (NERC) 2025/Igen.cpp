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

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int randint(int l, int r){
    return uniform_int_distribution<int>(l, r)(rng);
}

void testcase(){
    ofstream output("I.in");
    int t = 10;
    output << t << '\n';
    while(t--){
        int maxx = 10, maxy = 10;
        vector<pii> pts;
        for(int i = 0; i <= maxx; ++i){
            for(int j = 0; j <= maxy; ++j){
                pts.emplace_back(i, j);
            }
        }
        shuffle(all(pts), rng);
        int cnt = 0;
        for(int _ = 0; _ < 2; ++_){
           int n = randint(2, 20);       
            output << n << '\n';
            for(int i = 0; i < n; ++i){
                pii pt = pts[cnt++];
                output << pt.first << ' ' << pt.second << '\n';
            }
        }
        output << '\n';
    }
}

int main(){
    while(true){
        testcase();
        int code = system("./I < I.in");
        if(code != 0){
            cout << "Failed\n";
            return 0;
        }
    }
    return 0;
}

/*

10
7
3 30
87 13
96 31
19 19
90 62
6 99
22 54
5
62 53
21 30
45 88
56 96
91 1

2
19 60
16 38
9
38 2
4 26
47 83
74 89
16 47
89 64
8 40
20 18
20 96

3
16 33
33 67
92 21
19
43 47
92 18
16 45
56 82
35 2
38 59
55 33
60 91
77 63
56 26
62 18
31 28
26 74
38 13
40 3
53 76
84 87
59 9
85 91

3
83 8
79 76
3 94
11
77 39
30 44
36 60
27 99
98 32
14 19
44 46
26 16
5 49
40 84
24 88

20
27 71
22 76
96 15
30 97
28 49
25 21
86 49
79 16
38 67
25 61
72 81
30 90
1 7
85 54
31 59
97 63
45 90
100 15
2 41
6 26
13
31 7
76 23
17 56
37 79
72 24
82 87
57 88
97 81
93 41
19 70
95 53
88 98
10 70

20
70 2
49 75
27 55
14 6
55 53
91 41
13 22
37 48
43 32
44 33
88 8
62 84
19 26
32 30
53 24
75 94
99 11
45 9
42 36
0 84
16
67 98
86 46
65 46
40 19
92 52
87 72
81 42
95 11
67 45
44 24
11 5
30 18
47 48
20 17
35 57
81 12

13
26 86
71 83
71 25
22 35
68 97
73 23
44 66
48 21
49 94
25 7
90 91
71 93
49 54
10
24 96
83 84
15 90
63 1
73 17
67 76
1 78
47 13
86 2
17 46

2
40 31
92 24
18
21 84
58 29
12 18
80 18
23 47
95 51
39 42
52 39
81 65
24 59
87 37
35 54
65 32
86 12
8 93
57 90
42 32
51 15

7
93 87
96 7
25 33
42 78
7 23
2 31
83 28
3
77 39
30 10
86 28

13
75 61
71 63
62 71
26 13
82 58
2 93
17 49
33 12
28 33
90 29
31 83
44 99
74 30
19
35 89
60 23
48 54
32 42
95 39
73 5
87 28
53 54
1 76
70 56
24 84
64 29
41 82
78 57
10 25
54 10
80 27
77 47
8 55



*/