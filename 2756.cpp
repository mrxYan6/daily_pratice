//
// Created by mrx on 2022/6/3.
//

#include <bits/stdc++.h>

#define ll long long
#define endl '\n'
using namespace std;
const int N = 120;
int pre[N];
vector<int> EDG[N];
bool use[N];

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
    memset(use, 0, sizeof use);
    memset(pre, 0, sizeof pre);
    memset(EDG, 0, sizeof(EDG));
    cin >> m >> n;

    int u, v;
    while (cin >> u >> v && u + v > 0) {
        EDG[u].push_back(v);
    }
    cout << hungary(m) << endl;
    for (int i = m + 1; i <= n; ++i)if (pre[i])cout << pre[i] << ' ' << i << endl;
    return 0;
}