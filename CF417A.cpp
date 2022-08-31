//
// Created by mrx on 2022/8/1.
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
    int c, d, n, m, k;
    std::cin >> c >> d >> n >> m >> k;
    if (k < n * m) {
        std::vector<int> dp(n * m - k + 1, 0x3f3f3f3f);
        dp[0] = 0;
        for (int i = 0; i <= n * m - k; ++i) {
            dp[std::min(n * m - k, i + n)] = std::min(dp[std::min(n * m - k, i + n)], dp[i] + c);
        }

        for (int i = 0; i <= n * m - k; ++i) {
            dp[std::min(n * m - k, i + 1)] = std::min(dp[std::min(n * m - k, i + 1)], dp[i] + d);
        }
        std::cout << dp[n * m - k] << '\n';
    } else std::cout << 0 << '\n';
    return 0;
}