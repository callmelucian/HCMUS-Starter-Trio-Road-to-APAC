#include <bits/stdc++.h>
using namespace std;

namespace debug {
    #define dv declval
    #define dt decltype
    #define help(x) dt(x(dv<T>()))
    #define tcT template<class T
    tcT, class = void> struct IsRange : false_type {};
    tcT> struct IsRange<T, void_t<help(begin), help(end)>> : true_type {};
    tcT> void print (T x);

    void print (char x) { cerr << '\'' << x << '\''; }
    void print (string x) { cerr << '"' << x << '"'; }

    tcT, class U> void print (pair<T, U> p) { cerr << '('; print(p.first); cerr << ", "; print(p.second); cerr << ')'; }
    tcT> void print (T x) {
        if constexpr (IsRange<T>::value) {
            cerr << '{'; string sep;
            for (const auto &y : x) cerr << sep, print(y), sep = ", ";
            cerr << "}";
        }
        else cerr << x;
    }

    template<class... T> void out(T... x) {
        string sep;
        ((cerr << sep, print(x), sep = " | "), ...);
        cerr << '\n';
    }
};

#define dbg(...) (cerr << "[:" << __LINE__ << "] (" << #__VA_ARGS__ << ") = ", debug::out(__VA_ARGS__))