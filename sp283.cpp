//
// Created by mrx on 2022/7/9.
//
#include <bits/stdc++.h>

#define ll long long
#define endl '\n'
using namespace std;
const int N = 4000;
long long dp[N][N][2];

void sol() {
    int n, b;
    cin >> n >> b;
    vector<long long> a(n + 1);
    for (int i = 1; i <= n; ++i)cin >> a[i];
//    memset(dp, -0x3f, sizeof(dp));
    dp[1][1][1] = dp[1][0][0] = 0;
    for (int i = 2; i <= n; ++i) {
        for (int j = 0; j <= b; ++j) {
            if (j != 1)dp[i][j][1] = max(dp[i - 1][j - 1][1] + a[i], dp[i - 1][j - 1][0]);
            dp[i][j][0] = max(dp[i - 1][j][1], dp[i - 1][j][0]);
        }
    }
    long long ans = max(dp[n][b][0], dp[n][b][1]);
    dp[1][1][1] = a[1], dp[1][0][0] = 0;
    for (int i = 2; i <= n; ++i) {
        for (int j = 0; j <= b; ++j) {
            if (j != 1)dp[i][j][1] = max(dp[i - 1][j - 1][1] + a[i], dp[i - 1][j - 1][0]);
            dp[i][j][0] = max(dp[i - 1][j][1], dp[i - 1][j][0]);
        }
    }
    ans = max(ans, dp[n][b][1]);
    cout << ans << endl;
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
    int t;
    cin >> t;
    while (t--)sol();
    return 0;
}