//
// Created by mrx on 2022/6/26.
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
    int n, m, v, e;
    cin >> n >> m >> v >> e;
    vector<int> pri(n), swp(n);
    vector<double> prob(n);
    vector<vector<int>> cost(v, vector<int>(v, 0x3f3f3f3f));
    for (int i = 0; i < n; ++i) {
        cin >> pri[i];
        pri[i]--;
    }
    for (int i = 0; i < n; ++i) {
        cin >> swp[i];
        swp[i]--;
    }
    for (int i = 0; i < n; ++i) {
        cin >> prob[i];
    }
    for (int i = 0; i < e; ++i) {
        int x, y, w;
        cin >> x >> y >> w;
        x--, y--;
        cost[x][y] = cost[y][x] = min(cost[x][y], w);
    }
    for (int k = 0; k < v; ++k) {
        for (int i = 0; i < v; ++i) {
            for (int j = 0; j < v; ++j) {
                cost[i][j] = min(cost[i][j], cost[i][k] + cost[k][j]);
            }
        }
    }
    vector<vector<array<double, 2>>> dp(n, vector<array<double, 2>>(m + 2));//dp[i][j][0/1]表示到第i个换了j个点0表示已经换成功点，1表示没有换成功点
    for (int i = 0; i < v; i++)cost[i][i] = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= m; j++)dp[i][j][0] = dp[i][j][1] = 1e18;
    }
    dp[0][0][0] = dp[0][1][1] = 0;
    for (int i = 1; i < n; ++i) {
        dp[i][0][0] = dp[i - 1][0][0] + cost[pri[i - 1]][pri[i]];
        for (int j = 1; j <= min(i + 1, m); ++j) {
            dp[i][j][0] = min({dp[i][j][0], dp[i - 1][j][0] + cost[pri[i - 1]][pri[i]],
                               dp[i - 1][j][1] + prob[i - 1] * cost[swp[i - 1]][pri[i]] + (1 - prob[i - 1]) * cost[pri[i - 1]][pri[i]]});
            dp[i][j][1] = min({dp[i][j][1],
                               dp[i - 1][j - 1][0] + prob[i] * cost[pri[i - 1]][swp[i]] + (1 - prob[i]) * cost[pri[i - 1]][pri[i]],
                               dp[i - 1][j - 1][1]
                               + prob[i - 1] * prob[i] * cost[swp[i - 1]][swp[i]]
                               + prob[i - 1] * (1 - prob[i]) * cost[swp[i - 1]][pri[i]]
                               + (1 - prob[i - 1]) * prob[i] * cost[pri[i - 1]][swp[i]]
                               + (1 - prob[i - 1]) * (1 - prob[i]) * cost[pri[i - 1]][pri[i]]});
        }
    }
    double ans = 1e18;
    for (int i = 0; i <= m; ++i) {
        ans = min({ans, dp[n - 1][i][0], dp[n - 1][i][1]});
    }
    cout << fixed << setprecision(2) << ans << endl;
    return 0;
}