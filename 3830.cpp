//
// Created by mrx on 2022/6/27.
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
    int q, n;
    cin >> q >> n;
    if (q == 1) {
        double ans = 0;
        for (int i = 2; i <= n; ++i)ans += 2.0 / i;
        cout << fixed << setprecision(6) << ans << endl;
    } else {

        vector<vector<double  >> dp(n + 1, vector<double>(n + 1, 0));
        for (int i = 1; i <= n; ++i)dp[i][0] = 1;
        for (int i = 2; i <= n; ++i) {
            for (int j = 1; j < i; ++j) {
                for (int k = 1; k < i; ++k) {
                    dp[i][j] += (dp[k][j - 1] + dp[i - k][j - 1] - dp[k][j - 1] * dp[i - k][j - 1]) / (i - 1);
                }
            }
        }
        double ans = 0;
        for (int i = 1; i <= n; ++i)ans += dp[n][i];
        cout << fixed << setprecision(6) << ans << endl;
    }
    return 0;
}