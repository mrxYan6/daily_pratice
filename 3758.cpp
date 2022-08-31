//
// Created by mrx on 2022/5/10.
//
#include <iostream>
#include <algorithm>

#define ll long long
#define endl '\n'
using namespace std;
const int maxn = 32;
const int mod = 2017;
int n;

struct matrix {
    ll m[maxn][maxn];

    matrix() {
        for (int i = 0; i <= n; ++i)
            for (int j = 0; j <= n; ++j)
                m[i][j] = 0;
    }

    void E() {
        for (int i = 0; i <= n; ++i)
            for (int j = 0; j <= n; ++j)
                m[i][j] = i == j;
    }

    void show() {
        for (int i = 0; i <= n; ++i) {
            for (int j = 0; j <= n; ++j)cout << m[i][j] << ' ';
            cout << endl;
        }
    }

    matrix operator*(const matrix &b) {
        matrix res;
        for (int i = 0; i <= n; ++i) {
            for (int j = 0; j <= n; ++j) {
                for (int k = 0; k <= n; ++k) {
                    res.m[i][j] = (res.m[i][j] + m[i][k] * b.m[k][j] % mod) % mod;
                }
            }
        }
        return res;
    }
};

matrix LINEVECTOR;

matrix qqp(matrix base, ll power) {
    matrix res;
    res.E();
    while (power) {
        if (power & 1) {
            res = res * base;
        }
        base = base * base;
        power >>= 1;
    }
    return res;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
#ifdef ONLINE_JUDGE
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
#endif
    int m;
    cin >> n >> m;
    matrix b;
    LINEVECTOR.m[1][1] = 1;
    for (int i = 0; i <= n; ++i) {
        b.m[i][0] = 1;
        b.m[i][i] = 1;
    }
    for (int i = 1; i <= m; ++i) {
        int x, y;
        cin >> x >> y;
        b.m[x][y] = 1;
        b.m[y][x] = 1;
    }
    ll t;
    cin >> t;
    matrix tmp = qqp(b, t);
    ll ans = 0;
    for (int i = 0; i <= n; ++i) {
        ans += tmp.m[1][i];
        ans %= mod;
    }
    cout << ans << endl;
    return 0;
}