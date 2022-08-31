//
// Created by mrx on 2022/6/27.
//
#include <bits/stdc++.h>

#define ll long long
#define endl '\n'
using namespace std;
double eps = 1e-8;

struct matrix {
    vector<vector<double>> mat;
    int n, m;

    matrix(int n, int m) : n(n), m(m), mat(n, vector<double>(m + 1, 0.0)) {}

    void gauss() {
        for (int col = 0, row = 0; col <= m && row < n; ++col) {
            int nxt = row;
            for (; nxt < n - 1; nxt++) if (abs(mat[nxt][col]) > eps)break;
            if (abs(mat[nxt][col]) > eps) {
                swap(mat[row], mat[nxt]);
                double div = mat[row][col];
                for (int i = 0; i <= m; ++i) mat[row][i] /= div;
                for (int i = 0; i < n; ++i) {
                    if (i != row && abs(mat[row][col]) > eps) {
                        div = mat[i][col];
                        for (int j = 0; j <= m; ++j) {
                            mat[i][j] -= div * mat[row][j];
                        }
                    }
                }
            }
            row++;
        }
    }

    void show() {
        for (auto &x: mat) {
            for (auto y: x) { cout << y << ' '; }
            cout << endl;
        }
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
    cin >> n >> m;
    vector<int> E[n + 1];
    vector<pair<double, pair<int, int>>> e;
    vector<int> d(n + 1, 0);
    for (int i = 1; i <= m; ++i) {
        int x, y;
        cin >> x >> y;
        E[x].push_back(y), E[y].push_back(x);
        e.emplace_back(0, make_pair(x, y));
        d[x]++, d[y]++;
    }
    matrix M(n, n);
    M.mat[0][n] = 1;
    M.mat[n - 1][n - 1] = 1;
    for (int u = 1; u < n; ++u) {
        M.mat[u - 1][u - 1] = 1;
        for (auto v: E[u]) {
            if (v != n)
                M.mat[u - 1][v - 1] -= 1.0 / d[v];
        }
    }
//    M.show();
//    cout << endl;
    M.gauss();
//    M.show();
    for (auto &x: e) {
        x.first += M.mat[x.second.first - 1][n] / d[x.second.first] + M.mat[x.second.second - 1][n] / d[x.second.second];
    }
    std::sort(e.begin(), e.end());
    std::reverse(e.begin(), e.end());
    double ans = 0;
    for (int i = 1; i <= m; ++i) {
        ans += i * e[i - 1].first;
    }
    cout << fixed << setprecision(3) << ans << endl;
    return 0;
}