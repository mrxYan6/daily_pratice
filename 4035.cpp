//
// Created by mrx on 2022/6/25.
//

#include <bits/stdc++.h>

#define ll long long
#define endl '\n'
using namespace std;

const double eps = 1e-8;

struct matrix {
    vector<vector<double>> mat;
    int n, m;

    matrix(int eq, int va) {
        n = eq, m = va;
        mat.clear();
        mat.resize(n);
        for (auto &x: mat)x.resize(m + 1, 0);
    }

    void gauss() {
        for (int col = 0, row = 0; col < m && row < n; ++col) {
            int nxt = row;
            while (nxt < n - 1 && abs(mat[nxt][col]) < eps) {
                nxt++;
            }
            if (abs(mat[nxt][col]) > eps) {
                swap(mat[nxt], mat[row]);
                double divide = mat[row][col];
                for (int i = 0; i <= m; ++i) {
                    mat[row][i] /= divide;
                }
                for (int i = 0; i < n; ++i) {
                    if (i != row) {
                        if (abs(mat[i][col]) > eps) {
                            divide = mat[i][col];
                            for (int j = 0; j <= m; ++j) {
                                mat[i][j] -= mat[row][j] * divide;
                            }
                        }
                    }
                }
            }
            row++;
        }
    }

    void show() {
        for (auto &x: mat) {
            for (auto y: x)cerr << y << ' ';
            cerr << endl;
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
    int n;
    cin >> n;
    vector<vector<double>> dot(n + 1, vector<double>(n));
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> dot[i][j];
        }
    }

    matrix ans(n, n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            ans.mat[i][j] = 2 * (dot[i][j] - dot[n][j]);
            ans.mat[i][n] -= dot[n][j] * dot[n][j] - dot[i][j] * dot[i][j];
        }
    }
//    ans.show();
    ans.gauss();
//    cerr << endl;
//    ans.show();
    for (int i = 0; i < n; ++i) {
        cout << fixed << setprecision(3) << ans.mat[i][n] << ' ';
    }
    cout << endl;
    return 0;
}