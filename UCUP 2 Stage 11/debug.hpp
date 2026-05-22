#pragma once
#include <bits/stdc++.h>
using namespace std;

template<class T> void pr(const T& x){ cerr << x; }
void pr(char c){ cerr << '\'' << c << '\''; }
void pr(string s){ cerr << '"' << s << '"'; }
void pr(bool b){ cerr << (b ? "True" : "False"); }
template<class T, class U> void pr(const pair<T, U>& p){ 
    cerr << "("; pr(p.ff); cerr << ", "; pr(p.ss); cerr << ")";
}

template<class T> void prite(T a, T b, string sep = ", "){
    cerr << "{";
    bool f = false;
    for(T c = a; c != b; ++c){
        if(f) cerr << sep;
        pr(*c);
        f = 1;
    }
    cerr << "}";
}

template<class T> void pr(const vector<T>& v){ prite(begin(v), end(v)); }
template<class T> void pr(const set<T>& v){ prite(begin(v), end(v)); }
template<class T> void pr(const set<T, greater<T>>& v){ prite(begin(v), end(v)); }
template<class T> void pr(const multiset<T>& v){ prite(begin(v), end(v)); }
template<class T> void pr(const multiset<T, greater<T>>& v){ prite(begin(v), end(v)); }
template<class T, class U> void pr(const map<T, U>& v){ prite(begin(v), end(v)); }
void PR(){ cerr << '\n'; }
template<class T> void PR(const T& a){ pr(a); cerr << '\n'; }
template<class T, class...U> void PR(const T& a, const U&... b){
    pr(a); cerr << " | "; PR(b...);
}

#ifdef LOCAL 
  #define dbg(...) (cerr << "[:" << __LINE__ << "] (" << #__VA_ARGS__ << ") = ", PR(__VA_ARGS__))
#else 
  #define dbg(...) 
#endif //LOCAL 