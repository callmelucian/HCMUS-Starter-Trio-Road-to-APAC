#include <bits/stdc++.h>
using namespace std;

namespace debug{

#define dv declval
#define dt decltype
#define help(x) dt(x(dv<T>()))
#define tcT template<class T 
tcT, class = void> struct IsRange : false_type {};
tcT> struct IsRange<T, void_t<help(begin), help(end)>> : true_type {};
tcT> void print(T x);
void print(string s){ cerr << '"' << s << '"'; }
tcT, class U> void print(pair<T, U> pt){
    cerr << '('; print(pt.first); cerr << ", "; print(pt.second); cerr << ')';
}

tcT> void print(T x){
    if constexpr (IsRange<T>::value){
        cerr << '{';
        string sep = "";
        for(auto y : x) cerr << sep, print(y), sep = ", ";
        cerr << '}';
    } else cerr << x;
}

template<class... T> void out(T... x){
    string sep; 
    ((cerr << sep, print(x), sep = " | "), ...);
    cerr << '\n';
}
}

#define dbg(...) (cerr << "[:" << __LINE__ << "] (" << #__VA_ARGS__ << ") = ", debug::out(__VA_ARGS__))