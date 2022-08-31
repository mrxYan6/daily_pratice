//
// Created by mrx on 2022/5/10.
//

#include <iostream>

using ll = __int128;
#define endl '\n'
using namespace std;
const ll mod = 9223372036854775783;
const int maxn = 5;
using namespace std;

struct matrix {
    ll a[maxn][maxn]{};

    matrix() {
        for (auto &i: a)
            for (__int128 &j: i)
                j = 0;
    }

    void clear() {
        for (auto &i: a)
            for (__int128 &j: i)
                j = 0;
    }

    void E() {
        for (int i = 0; i < maxn; ++i)
            for (int j = 0; j < maxn; ++j)
                a[i][j] = i == j;
    }

    matrix operator*(const matrix &b) {
        matrix res;
        for (int i = 0; i < maxn; ++i) {
            for (int j = 0; j < maxn; ++j) {
                for (int k = 0; k < maxn; ++k) {
                    res.a[i][j] = (res.a[i][j] + (a[i][k] % mod) * (b.a[k][j] % mod)) % mod;
                    if (res.a[i][j] < 0)res.a[i][j] += mod;
                    if (res.a[i][j] >= mod)res.a[i][j] -= mod;
                }
            }
        }
        return res;
    }
};

matrix qqp(matrix base, ll power) {
    matrix res;
    res.E();
    while (power) {
        if (power & 1)res = res * base;
        base = base * base;
        power >>= 1;
    }
    return res;
}

bool fla;

template<typename T>
inline void read(T &x) {
    x = 0;
    char ch = 1;
    fla = 0;
    int fh;
    while (ch != '-' && (ch > '9' || ch < '0')) ch = getchar();
    if (ch == '-') {
        ch = getchar();
        fh = -1;
    } else fh = 1;
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + ch - '0';
        if (x >= (mod - 1)) {
            x %= (mod - 1);
            fla = 1;
        }
        ch = getchar();
    }
    x *= fh;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    ll n;
    read(n);
    n--;
    if (n < 0) n = mod - 1;
    if (fla)
        n += mod - 1;
    matrix s, u;
    s.a[1][1] = 2;
    s.a[1][2] = 1;
    s.a[1][3] = 0;
    s.a[1][4] = 0;
    s.a[2][1] = 2;
    s.a[2][2] = 2;
    s.a[2][3] = 0;
    s.a[2][4] = 0;
    s.a[3][1] = 3;
    s.a[3][2] = 1;
    s.a[3][3] = 2;
    s.a[3][4] = 0;
    s.a[4][1] = -2;
    s.a[4][2] = -1;
    s.a[4][3] = 0;
    s.a[4][4] = 1;
    u.a[1][1] = 1;
    u.a[1][2] = 0;
    u.a[1][3] = 2;
    u.a[1][4] = 1;
    matrix ans = u * qqp(s, n);
    cout << (long long) ans.a[1][1] << '\n';
    return 0;
}