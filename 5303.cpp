//
// Created by mrx on 2022/5/10.
//
#include <iostream>
#include <vector>

#define ll long long
#define endl '\n'
using namespace std;
const ll mod = 1e9 + 7;

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
        for (auto &x: mat) {
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
    ll t;
    cin >> t;
    matrix init(5, 1);
    init.mat[0][0] = 2, init.mat[1][0] = 0, init.mat[2][0] = init.mat[3][0] = 2, init.mat[4][0] = 1;
    matrix base(5, 5);
    base.mat[0][0] = base.mat[0][1] = 1, base.mat[0][2] = 2;
    base.mat[1][0] = 1;
    base.mat[2][2] = base.mat[2][3] = 1;
    base.mat[3][3] = base.mat[3][4] = 1;
    base.mat[4][3] = 1;
    while (t--) {
        ll x;
        cin >> x;
        if (x < 3)cout << 0 << endl;
        else {
            matrix ans = base ^ (x - 3);
//            ans.show();
            ans = ans * init;
//            ans.show();
            cout << ans.mat[0][0] << endl;
        }
    }
    return 0;
}