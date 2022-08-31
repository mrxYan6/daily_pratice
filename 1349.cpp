//
// Created by mrx on 2022/6/3.
//
#include <bits/stdc++.h>

#define ll long long
#define endl '\n'
using namespace std;

int mod;

struct matrix {
    vector<vector<ll>> mat;
    ll n, m;

    matrix(ll a, ll b) {
        n = a, m = b;
        mat.clear();
        mat.resize(n);
        for (auto &x: mat)x.resize(m, 0);
    }

    void clear() {
        for (ll i = 0; i < n; ++i) {
            for (ll j = 0; j < m; ++j)mat[i][j] = 0;
        }
    }

    void E() {
        clear();
        for (ll i = 0; i < min(n, m); ++i) {
            mat[i][i] = 1;
        }
    }

    void show() {
        for (auto x: mat) {
            for (auto y: x)cout << y << ' ';
            cout << endl;
        }
    }

    matrix operator*(const matrix &rhs) {
        matrix ans(n, rhs.m);
        if (m != rhs.n) {
            cerr << "Matrix not matching!";

        }
        for (ll i = 0; i < n; ++i) {
            for (ll j = 0; j < m; ++j) {
                for (ll k = 0; k < rhs.m; ++k) {
                    ans.mat[i][k] = (ans.mat[i][k] + mat[i][j] * rhs.mat[j][k] % mod) % mod;
                }
            }
        }
        return ans;
    }

    friend matrix operator^(matrix bas, long long x) {
        matrix ans(bas.n, bas.n);
        ans.E();
        while (x) {
            if (x & 1) {
                ans = ans * bas;
            }
            bas = bas * bas;
            x >>= 1;
        }
        return ans;
    }
};

int main() {
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
#ifdef ONLINE_JUDGE
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
#endif
    ll p, q, a1, a2;
    ll n;
    cin >> p >> q >> a1 >> a2 >> n >> mod;
    matrix init(2, 2);
    init.mat[0][0] = p, init.mat[0][1] = q, init.mat[1][0] = 1, init.mat[1][1] = 0;
    matrix ans = init ^ (n - 2);
    cout << (ans.mat[0][1] * a1+ans.mat[0][0] * a2) % mod << endl;
    return 0;
}