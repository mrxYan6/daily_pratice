//
// Created by mrx on 2022/7/31.
//
#include <bits/stdc++.h>

using ll = long long;

int main() {
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
#ifdef ONLINE_JUDGE
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#endif
    int n, m, k;
    std::cin >> n >> k >> m;
    std::vector<ll> cm(n), ck(n), w(n);

    for (int i = 0; i < n; ++i)std::cin >> w[i] >> ck[i] >> cm[i];

    std::vector<std::vector<ll>> dp(m + 1, std::vector<ll>(k + 1, -0x3f3f3f3f3f3f3f3f));
    dp[m][k] = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= m - cm[i]; ++j) {
            for (int kk = 0; kk <= k - ck[i]; ++kk) {
                dp[j][kk] = std::max(dp[j][kk], dp[j + cm[i]][kk + ck[i]] + w[i]);
            }
        }
    }

    ll ans = 0;
    for (int i = 0; i <= m; ++i)for (int j = 0; j <= k; ++j)ans = std::max(ans, dp[i][j]);
    std::cout << ans << '\n';
    return 0;
}