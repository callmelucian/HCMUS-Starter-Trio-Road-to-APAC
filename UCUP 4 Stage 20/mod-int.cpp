template<int MOD>
struct ModInt {
    static const int mod = MOD;
    int v;
    ModInt (int a = 0) : v(refine(a)) {}

    template<class T> T refine (T a) {
        if (abs(a) >= mod) a %= mod;
        if (a < 0) a += mod;
    }

    const ModInt& operator+= (const ModInt &o) {
        if ((v += o.v) >= mod) v -= mod;
        return *this;
    }

    const ModInt& operator-= (const ModInt &o) {
        if ((v -= o.v) < 0) v += mod;
        return *this;
    }

    const ModInt& operator*= (const ModInt &o) {
        v = 1LL * v * o.v % mod;
        return *this;
    }

    const ModInt& operator/= (const ModInt &o) {
        return operator*=(o.inv());
    }

    ModInt pwr (int k) const {
        ModInt ans(1), a(*this);
        for (; k; k >>= 1, a *= a)
            if (k & 1) ans *= a;
        return ans;
    }

    ModInt inv() const { return pwr(mod - 2); }

    friend ModInt operator+ (ModInt a, const ModInt &b) { return a += b; }
    friend ModInt operator- (ModInt a, const ModInt &b) { return a -= b; }
    friend ModInt operator* (ModInt a, const ModInt &b) { return a *= b; }
    friend ModInt operator/ (ModInt a, const ModInt &b) { return a /= b; }

    friend istream& operator>> (istream &i, ModInt &m) { return i >> m.v, m.v = refine(m.v), i; }
    friend ostream& operator<< (ostream &o, const ModInt &m) { return o << m.v; }
};
using mint = ModInt<998'244'353>;