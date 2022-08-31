//
// Created by mrx on 2022/5/10.
//

#include <iostream>
#include <algorithm>
#include <vector>

#define ll long long
#define endl '\n'
using namespace std;

const int maxn = 27;
const int mod = 1e9 + 7;

struct matrix {
    ll m[maxn][maxn];

    matrix() {
        for (int i = 0; i < maxn; ++i)
            for (int j = 0; j < maxn; ++j)
                m[i][j] = 0;
    }

    void clear() {
        for (int i = 0; i < maxn; ++i)
            for (int j = 0; j < maxn; ++j)
                m[i][j] = 0;
    }

    void E() {
        for (int i = 0; i < maxn; ++i)
            for (int j = 0; j < maxn; ++j)
                m[i][j] = i == j;
    }

    void show() {
        for (int i = 0; i < maxn; ++i) {
            for (int j = 0; j < maxn; ++j) {
                cout << m[i][j] << ' ';
            }
            cout << endl;
        }
    }

    matrix operator*(const matrix &b) {
        matrix res;
        for (int i = 0; i < maxn; ++i) {
            for (int j = 0; j < maxn; ++j) {
                for (int k = 0; k < maxn; ++k) {
                    res.m[i][j] = (res.m[i][j] + m[i][k] * b.m[k][j] % mod) % mod;
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
        if (power & 1)res = base * res;
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
    ll n;
    cin >> n;
    vector<int> v(26, 1);
    matrix bas;
    for (int i = 0; i < 26; ++i)
        for (int j = 0; j < 26; ++j) {
            bas.m[i][j] = 1;
        }
    string s;
    cin >> s;
    for (int i = 1; i < s.length(); ++i) {
        bas.m[s[i - 1] - 'a'][s[i] - 'a'] = 0;
    }
    bas = qqp(bas, n - 1);
    ll ans = 0;
    for (int i = 0; i < 26; ++i) {
        for (int j = 0; j < 26; ++j)
            ans = (ans + bas.m[i][j] * v[j]) % mod;
    }
    if (n == 0)cout << 0 << endl;
    else
        cout << ans << endl;
    return 0;
}