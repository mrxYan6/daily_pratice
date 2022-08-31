//
// Created by mrx on 2022/6/3.
//
#include <bits/stdc++.h>

#define ll long long
#define endl '\n'
using namespace std;
const double eps = 1e-9;

struct matrix {
    vector<vector<double>> mat;
    int n, m;

    matrix(int _n, int _m) {
        mat.resize(_n);
        n = _n, m = _m;
        for (auto &x: mat)x.resize(_m);
    }

    void gauss() {
        int col = 0, row = 0;
        for (; col < n && row < m; ++col) {
            int nxt = row;
            for (; nxt < n - 1; ++nxt)
                if (abs(mat[nxt][col]) > eps)break;
            if (abs(mat[nxt][col]) > eps) {
                swap(mat[row], mat[nxt]);
                double tmp = mat[row][col];
                for (int i = 0; i < m; ++i) {
                    mat[row][i] /= tmp;
                }
                for (int r = 0; r < n; ++r) {
                    if (r == row)continue;
                    if (abs(mat[r][col]) > eps) {
                        double div = mat[r][col];
                        for (int i = 0; i < m; ++i) {
                            mat[r][i] -= mat[row][i] * div;
                        }
                    }
                }
                row++;
            }
        }
        if (row != n)cout << "No solution" << endl;
        else {
            for (int i = 0; i < n; ++i)cout << fixed << setprecision(2) << mat[i][n] << endl;
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
    matrix m(n, n + 1);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j <= n; ++j) {
            cin >> m.mat[i][j];
        }
    m.gauss();
    return 0;
}