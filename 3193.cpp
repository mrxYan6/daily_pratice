//
// Created by mrx on 2022/6/27.
//
#include <bits/stdc++.h>

#define ll long long
#define endl '\n'
using namespace std;
int mod;

vector<int> nxt(string &s) {
    int n = s.length();
    vector<int> nxt(n + 1, 0);
    for (int i = 2, j = 0; i <= n && j <= n; ++i) {
        while (j && s[j + 1] != s[i])j = nxt[j];
        if (s[j + 1] == s[i])j++;
        nxt[i] = j;
    }
    return nxt;
}

struct matrix {
    vector<vector<int>> mat;
    int n, m;

    matrix(int n, int m) : n(n), m(m), mat(n, vector<int>(m, 0)) {}

    void E() {
        m = n;
        mat.clear();
        mat.resize(n);
        for (auto &x: mat)x.resize(m, 0);
        for (int i = 0; i < n; ++i)mat[i][i] = 1;
    }

    friend matrix operator*(const matrix &lhs, const matrix &rhs) {
        if (lhs.m != rhs.n) {
            throw (runtime_error("matrix multiply not matching"));
        }
        matrix ans(lhs.n, rhs.m);
        for (int i = 0; i < lhs.n; ++i) {
            for (int j = 0; j < rhs.m; ++j) {
                for (int k = 0; k < lhs.m; ++k) {
                    ans.mat[i][j] = (ans.mat[i][j] + lhs.mat[i][k] * rhs.mat[k][j] % mod) % mod;
                }
            }
        }
        return ans;
    }

    friend matrix operator^(matrix a, long long b) {
        if (a.n != a.m) {
            throw (runtime_error("matrix pow not matching"));
        }
        matrix ans(a.n, a.n);
        ans.E();
        while (b) {
            if (b & 1) {
                ans = ans * a;
            }
            a = a * a;
            b >>= 1;
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
    int n, m;
    string s;
    cin >> n >> m >> mod;
    cin >> s;
    s = '*' + s;
    vector<int> kmp = nxt(s);
    matrix xs(m, m);
    for (int i = 0; i < m; ++i) {
        for (int j = '0'; j <= '9'; ++j) {
            int temp = i;
            while (s[temp + 1] != j && temp > 0) temp = kmp[temp];
            if (s[temp + 1] == j) temp++;
            if (temp < m) xs.mat[i][temp]++;
        }
    }
    matrix dp(1, m);
    dp.mat[0][0] = 1;
    long long ans = 0;
    matrix ansm = dp * (xs ^ n);
    for (int i = 0; i < m; ++i) {
        ans = (ansm.mat[0][i] + ans) % mod;
    }
    cout << ans << endl;
    return 0;
}