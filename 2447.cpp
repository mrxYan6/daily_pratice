//
// Created by mrx on 2022/6/23.
//
#include <bits/stdc++.h>

#define ll long long
#define endl '\n'
using namespace std;

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
    vector<bitset<3002>> mat(m);
    for (int i = 0; i < m; ++i) {
        string s;
        int ans;
        cin >> s >> ans;
        vector<int> tmp;
        mat[i][n] = ans;
        for (int j = 0; j < n; ++j) {
            mat[i][j] = s[j] - '0';
        }
    }
    int col, row;
    int need = 0;
    for (col = 0, row = 0; col < n && row < m; ++col) {
        int nxt = row;
        while (nxt < m - 1 && mat[nxt][col] == 0)nxt++;
        need = max(need, nxt);
        if (mat[nxt][col]) {
            swap(mat[nxt], mat[row]);
            for (int equ = 0; equ < m; ++equ) {
                if (equ != col) {
                    if (mat[equ][col]) {
                        mat[equ] ^= mat[row];
                    }
                }
            }
        }
        row++;
    }
    for (int i = 0; i < n; ++i)
        if (mat[i][i] == 0) {
            cout << "Cannot Determine" << endl;
            return 0;
        }
    cout << need + 1 << endl;
    for (int i = 0; i < n; ++i) {
        if (mat[i][n])
            cout << "?y7M#" << endl;
        else cout << "Earth" << endl;
    }

    return 0;
}