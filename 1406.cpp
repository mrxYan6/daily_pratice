//
// Created by mrx on 2022/5/24.
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

    int n;
    cin >> n;
    vector<int> num(n * n);
    vector<bool> vis(n * n);
    vector<vector<int>> mp(n, vector<int>(n, 0));
    int sum = 0;
    for (int i = 0; i < n * n; ++i) {
        cin >> num[i];
        sum += num[i];
    }

    int need = sum / n;

    auto dfs = [&](int x, int y) -> void {
        if (x == n && y == 1) {
            for (auto &X: mp) {
                for (auto Y: X)cout << Y << ' ';
                cout << endl;
            }
            return;
        }
        if (y == n - 1) {
            int tmp = 0;
            for (int i = 0; i < n; ++i) {
                tmp += mp[x][i];
            }
        }
    };
    dfs(0, 0);
    return 0;
}