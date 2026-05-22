#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pl = pair<ll,ll>;
using pii = pair<int,int>;
using tpl = tuple<int,int,int>;

#define all(a) a.begin(), a.end()
#define filter(a) a.erase(unique(all(a)), a.end())

mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

int rr (int l, int r, int t = 0) {
    int cur = uniform_int_distribution<int>(l, r)(rng);
    for (int i = 0; i < t; i++)
        cur = max(cur, uniform_int_distribution<int>(l, r)(rng));
    for (int i = 0; i > t; i--)
        cur = min(cur, uniform_int_distribution<int>(l, r)(rng));
    return cur;
}

ll rrl (ll l, ll r, int t = 0) {
    ll cur = uniform_int_distribution<ll>(l, r)(rng);
    for (int i = 0; i < t; i++)
        cur = max(cur, uniform_int_distribution<ll>(l, r)(rng));
    for (int i = 0; i > t; i--)
        cur = min(cur, uniform_int_distribution<ll>(l, r)(rng));
    return cur;
}

void stress() {
    int TC = rr(1, 100), M = 10;
    ofstream inp("input.txt");
    inp << TC << "\n";
    for (int i = 0; i < TC; i++)
        inp << rr(2, M) << " " << rr(0, M) << "\n";
    inp.close();
    
    system("C2 < input.txt > output.txt");
    system("brute < input.txt > answer.txt");
    if (system("fc output.txt answer.txt")) {
        cout << "WA\n";
        exit(0);
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    system("g++ C2.cpp -o C2");
    system("g++ brute.cpp -o brute");

    int TC = 100;
    while (TC--) stress();

    return 0;
}
