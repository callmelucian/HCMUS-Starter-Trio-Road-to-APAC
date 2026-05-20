#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pl = pair<ll,ll>;
using pii = pair<int,int>;
using tpl = tuple<int,int,int>;

#define all(a) a.begin(), a.end()
#define filter(a) a.erase(unique(all(a)), a.end())

const int mn = 1e5 + 5;

struct Crop {
    ll re, L, R;
    Crop() : re(0), L(0), R(0) {}

    ll reward (ll x) const { return re * x; }
    bool operator> (const Crop &oth) const { return re > oth.re; }

    friend istream& operator>> (istream &inp, Crop &c) {
        return inp >> c.re >> c.L >> c.R, inp;
    }
} crop[mn];

ll used[mn], available[mn], takeAll[mn];

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n; ll m; cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> crop[i];
    sort(crop + 1, crop + 1 + n, greater<Crop>());

    ll sum = 0;
    for (int i = 1; i <= n; i++) {
        sum += crop[i].reward(crop[i].L);
        m -= crop[i].L;
    }
    
    ll tmp = m, takeMore = sum;
    for (int i = 1; i <= n; i++) {
        ll take = min(crop[i].R - crop[i].L, tmp);
        tmp -= take, available[i] = crop[i].R - (crop[i].L + take), takeAll[i] = crop[i].reward(available[i]);
        available[i] += available[i - 1], takeAll[i] += takeAll[i - 1];
        takeMore += crop[i].reward(take);
    }

    // case 1: take all
    ll ans = sum + crop[1].reward(m);

    // for (int i = 1; i <= n; i++) cout << available[i] << " ";
    // cout << "\n";
    // for (int i = 1; i <= n; i++) cout << takeAll[i] << " ";
    // cout << "\n";

    // case 2: empty someone
    for (int i = 1; i <= n; i++) {
        int k = lower_bound(available + 1, available + i, crop[i].L) - available - 1;
        // cout << "take all " << k << " " << available[k] << " " << available[k + 1] << " " << crop[i].L << "\n";
        ll curr = takeMore + takeAll[k] - crop[i].reward(crop[i].L) + crop[k + 1].reward(crop[i].L - available[k]);
        // cout << sum << " " << curr << " " << crop[i].re * crop[i].L << " " << crop[k + 1].re * (crop[i].L - available[k]) << "\n";
        ans = max(ans, curr);
    }
    cout << ans << "\n";    
    

    return 0;
}

/*
5 17
2 3 4
6 1 5
8 2 4
4 3 3
7 5 5
*/