#include <bits/stdc++.h>
using namespace std;

#define all(v) begin(v), end(v)
#define compact(v) v.erase(unique(all(v)), end(v))
#define sz(v) (int)v.size()
using ll = long long;
using pii = pair<int, int>;

template<class T> bool minimize(T& a, const T& b){ return b < a ? a = b, true : false; }
template<class T> bool maximize(T& a, const T& b){ return b > a ? a = b, true : false; }

#ifdef LOCAL
    #include "debug.hpp"
#else 
    #define dbg(...) ((void)0)
#endif //LOCAL


int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    string run;
    cin >> run;
    if(run == "first"){
        int N;
        cin >> N;
        string S;
        cin >> S;

        if(N == 1){
            for(int i = 0; i < 5; ++i){
                cout << S[0];
            }
            return 0;
        }

        vector<int> s;
        int xorAll = 0, k = 0;
        while((1 << k) <= N) ++k;
        vector<int> u(k), v(k);
        for(int i = 0; i < N; ++i){
            int b = S[i] - '0';
            xorAll ^= b;
            for(int j = 0; j < k; ++j){
                if((i + 1) >> j & 1) u[j] ^= b;
                else v[j] ^= b;
            }
            s.push_back(b);
        }
        s.push_back(xorAll);
        s.insert(end(s), all(u));
        s.insert(end(s), all(v));
        for(int i = 0; i < (int)s.size(); ++i) cout << s[i];
        cout << '\n';
        return 0;
    } else{
        int N;
        string T;
        cin >> N >> T;

        if(N == 1){
            int cnt[2] = {0, 0};
            for(int  i = 0; i < sz(T); ++i){
                cnt[T[i] - '0'] += 1;
            }
            if(cnt[0] < cnt[1]){
                cout << cnt[0] << '\n';
                cout << 1 << '\n';
                return 0;
            } else{
                cout << cnt[1] << '\n';
                cout << 0 << '\n';
                return 0;
            }
        }
        int k = 0;
        while((1 << k) <= N) ++k;

        vector<int> u(k), v(k), xor0(k), xor1(k);
        int allT = T[N] - '0';
        for(int j = 0; j < k; ++j){
            u[j] = T[N + j + 1] - '0';
            v[j] = T[N + j +  1 + k] - '0';
        }
        for(int i = 0; i < N; ++i){
            for(int j = 0; j < k; ++j){
                if((i + 1) >> j & 1) xor1[j] ^= T[i] - '0';
                else xor0[j] ^= T[i] - '0';
            }
        }

        int xorAll = 0;
        for(int i = 0; i < N; ++i) xorAll ^= T[i] - '0';
        
        //Case k = 1.1

        auto check1 = [&](){
            if(xorAll == allT) return -1;
            int pos = 0;
            for(int i = 0; i < k; ++i){
                int p = (u[i] != xor1[i]);
                int q = (v[i] != xor0[i]);
                if(p ^ q){
                    if(p) pos ^= (1 << i);
                } else return -1;
            }
            return pos;
        };

        int r = check1();
        if(r != -1){
            string S = T.substr(0, N);
            S[r - 1] = (S[r - 1] == '0' ? '1' : '0');
            cout << 1 << '\n' << S << '\n';
            return 0;
        }
        
        auto check2 = [&](){
            if(allT != xorAll);
            else return false;
            for(int i = 0; i < k; ++i){
                if(allT != (xor0[i] ^ xor1[i]) && allT != (u[i] ^ v[i]));
                else return false;
            }
            return true;
        };
        dbg(xor0, xor1, u, v);

        if(check2()){
            cout << 1 << '\n';
            cout << T.substr(0, N) << '\n';
            return 0;
        }
        
        auto check3 = [&](){
            if(allT != xorAll) return false;
            int cnt = 0;
            for(int i = 0; i < k; ++i){
                cnt += (u[i] ^ v[i]) != allT;
            }
            return cnt == 1;
        };

        if(check3()){
            cout << 1 << '\n';
            cout << T.substr(0, N) << '\n';
            return 0;    
        }

        auto check4 = [&](){
            if(allT != xorAll) return false;
            for(int i = 0; i < k; ++i){
                dbg(xor0[i], v[i], xor1[i], u[i], xorAll, allT);
                if(xor0[i] != v[i]) return false;
                if(xor1[i] != u[i]) return false;
                if((xor0[i] ^ xor1[i]) != allT) return false;
                if((u[i] ^ v[i]) != allT) return false;
            }
            return true;
        };

        if(check4()){
            cout << 0 << '\n';
            cout << T.substr(0, N) << '\n';
            return 0;
        }
        cout << 2 << '\n';
    }
    return 0;
}