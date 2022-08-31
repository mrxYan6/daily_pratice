//
// Created by mrx on 2022/6/27.
//
#include <bits/stdc++.h>

#define ll long long
#define endl '\n'
using namespace std;
const long long mod = 998244353;

template<typename T>
T quickPow(T base, T fact) {
    T ans = 1;
    while (fact) {
        if (fact & 1) ans = ans * base % mod;
        base = base * base % mod;
        fact >>= 1;
    }
    return ans;
}

template<typename T>
T normal(T a) {
    return a < 0 ? a + mod : a >= mod ? a - mod : a;
}

template<typename T>
struct ModInt {
    T base;

    ModInt() : base(0) {}

    ModInt(T a) : base(normal(a % mod)) {}

    ModInt(int a) : base(normal(a % mod)) {}

    ModInt(const ModInt &rhs) {
        base = rhs.base;
    }

    ModInt inv() const {
        return quickPow(base, mod - 2);
    }

    ModInt &operator=(const ModInt &rhs) {
        base = rhs.base;
        return *this;
    }

    ModInt operator-() const { return ModInt(normal(mod - base)); }

    ModInt &operator*=(const ModInt &rhs) {
        base = 1ll * base * rhs.base % mod;
        return *this;
    }

    ModInt &operator+=(const ModInt &rhs) {
        base = normal(base + rhs.base);
        return *this;
    }

    ModInt &operator-=(const ModInt &rhs) {
        base = normal(base - rhs.base);
        return *this;
    }

    ModInt &operator/=(const ModInt &rhs) { return *this *= rhs.inv(); }

    ModInt &operator++() { return *this += 1; }

    ModInt &operator--() { return *this -= 1; }

    ModInt operator++(int) {
        ModInt res = *this;
        ++*this;
        return res;
    }

    ModInt operator--(int) {
        ModInt res = *this;
        --*this;
        return res;
    }

    friend ModInt operator*(const ModInt &lhs, const ModInt &rhs) {
        ModInt res = lhs;
        res *= rhs;
        return res;
    }

    friend ModInt operator+(const ModInt &lhs, const ModInt &rhs) {
        ModInt res = lhs;
        res += rhs;
        return res;
    }

    friend ModInt operator-(const ModInt &lhs, const ModInt &rhs) {
        ModInt res = lhs;
        res -= rhs;
        return res;
    }

    friend ModInt operator/(const ModInt &lhs, const ModInt &rhs) {
        ModInt res = lhs;
        res /= rhs;
        return res;
    }

    template<class stream>
    friend stream &operator>>(stream &is, ModInt &rhs) {
        T x;
        is >> x;
        rhs = ModInt(x);
        return is;
    }

    operator T() {
        return base;
    }

    template<class stream>
    friend stream &operator<<(stream &os, const ModInt &rhs) {
        return os << rhs.base;
    }

    friend bool operator==(const ModInt &lhs, const ModInt &rhs) {
        return lhs.base == rhs.base;
    }

    friend bool operator!=(const ModInt &lhs, const ModInt &rhs) {
        return lhs.base != rhs.base;
    }
};

using Mint = ModInt<long long>;

int main() {
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
#ifdef ONLINE_JUDGE
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
#endif
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    int q;
    cin >> q;
    vector<vector<Mint>> prob(n + 1, vector<Mint>(211, 0));
    vector<Mint> g(211), inv(211), tmp(211);
    for (int i = 1; i <= 203; ++i)inv[i] = Mint(i).inv();
    for (int i = 1; i <= n; ++i)prob[i][a[i]] = 1;
    while (q--) {
        int opt;
        cin >> opt;
        if (opt == 0) {
            Mint id, u, v;
            cin >> id >> u >> v;
            Mint p = u * v.inv();
            Mint mp = Mint(1) - p;
            prob[id][0] = prob[id][0] + prob[id][1] * p;
            for (int i = 1; i <= a[id]; ++i) {
                prob[id][i] = prob[id][i + 1] * p + prob[id][i] * mp;
            }
        } else {
            int cnt, tot = 0;
            cin >> cnt;
            vector<int> atkid(cnt + 2);
            for (int i = 1; i <= cnt; ++i) {
                cin >> atkid[i];
            }
            g[0] = 1;
            for (int i = 1; i <= cnt; ++i) {
                Mint id = atkid[i], p = Mint(1) - prob[id][0];
                Mint invp = prob[id][0];
                if (invp == Mint(0)) {
                    tot++;
                    continue;
                }
                for (int j = cnt; j >= 1; --j) {
                    g[j] = g[j - 1] * p + g[j] * invp;
                }
                g[0] = g[0] * invp;
            }
            for (int i = 1; i <= cnt; ++i) {
                Mint id = atkid[i], p = Mint(1) - prob[id][0];
                Mint invp = prob[id][0], invp_inv = invp.inv();
                Mint ans = 0;
                if (invp == Mint(0)) {
                    for (int j = 0; j <= cnt; ++j) {
                        ans = ans + inv[j + tot] * g[j];
                    }
                    cout << ans << ' ';
                } else {
                    for (int j = 0; j <= cnt; ++j) {
                        tmp[j] = g[j];
                    }
                    tmp[0] = tmp[0] * invp_inv;
                    for (int j = 1; j <= cnt; ++j) {
                        tmp[j] = (tmp[j] - tmp[j - 1] * p) * invp_inv;
                    }
                    for (int j = 0; j <= cnt; ++j)ans = ans + inv[j + tot + 1] * tmp[j] * p;
                    cout << ans << ' ';
                }
            }
            cout << endl;
            for (int j = 0; j <= cnt; ++j)g[j] = 0;
        }
    }
    for (int i = 1; i <= n; ++i) {
        Mint ans = 0;
        for (int j = 0; j <= a[i]; ++j)ans += Mint(j) * prob[i][j];
        cout << ans << ' ';
    }
    cout << endl;
    return 0;
}