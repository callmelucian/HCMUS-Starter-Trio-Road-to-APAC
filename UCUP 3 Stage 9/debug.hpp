#include <bits/stdc++.h>
using namespace std;
namespace debug{
    #define ifc if constexpr
    template<class T> void pr(T x){
        ifc (is_same_v<T, char>) cerr << '\'' << x << '\'';
        else ifc (is_same_v<T, string>) cerr << '"' << x << '"';
        else ifc (requires {begin(x); end(x); }){
            cerr << "{"; string s;
            for(auto&& y : x){
                cerr << s;
                pr(y);
                s = ", ";
            }
            cerr << "}";
        } else ifc (requires {tuple_size<T>::value; }){
            cerr << '('; string s;
            apply([&](auto&... y){ ((cerr << s, pr(y), s = ", "), ...); }, x);
            cerr << ')';
        } else ifc (requires {x.pop(); }){
            vector<typename T::value_type> v;
            for(; !x.empty(); x.pop()){
                ifc (requires {x.top();}) v.push_back(x.top());
                else v.push_back(x.front());
            }
            pr(v);
        } else cerr << x;
    }

    template<class... T> void out(T... x){
        string s;
        ((cerr << s, pr(x), s = " | "), ...);
        cerr << '\n';
    }
}

#define dbg(...) (cerr << "[:" << __LINE__ << "] (" << #__VA_ARGS__ << ") = ", debug::out(__VA_ARGS__))