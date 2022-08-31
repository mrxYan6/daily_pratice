//
// Created by mrx on 2022/5/29.
//
#include <bits/stdc++.h>

#define ll long long
#define endl '\n'
using namespace std;

char mp[60][60];
int hmp[60][60];
int lmp[60][60];
int pre[60];
vector<int> EDG[60];
bool use[60];

int dfs(int x) {
    for (int i = 0; i < EDG[x].size(); ++i) {
        if (!use[EDG[x][i]]) {
            use[EDG[x][i]] = 1;
            if (pre[EDG[x][i]] == 0 || dfs(pre[EDG[x][i]])) {
                pre[EDG[x][i]] = x;
                return 1;
            }
        }
    }
    return 0;
}

int hungary(int n) {
    int sum = 0;
    for (int i = 1; i <= n; ++i) {
        memset(use, false, sizeof use);
        if (dfs(i))sum++;
    }
    return sum;
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
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; ++i)cin >> mp[i];
    int cnt1 = 0;
    for (int i = 0; i < n; ++i) {
        int f = 1;
        for (int j = 0; j < m; ++j) {
            if (mp[i][j] == '.')f = 1;
            else {
                cnt1 += f;
                f = 0;
                lmp[i][j] = cnt1;
            }
        }
    }
    int cnt = 0;
    for (int i = 0; i < m; ++i) {
        int f = 1;
        for (int j = 0; j < n; ++j) {
            if (mp[j][i] == '.')f = 1;
            else {
                cnt += f;
                f = 0;
                hmp[j][i] = cnt;
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (mp[i][j] == '*')EDG[lmp[i][j]].push_back(hmp[i][j]);
        }
    }
    cout << hungary(cnt1) << endl;
    return 0;
}


