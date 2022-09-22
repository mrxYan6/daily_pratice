//
// Created by mrx on 2022/7/16.
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
    int n;
    std::cin >> n;
    std::vector<std::pair<int, int>> p(n + 1);
    for (int i = 1; i <= n; ++i)std::cin >> p[i].first >> p[i].second;
    std::vector<std::array<int, 2>> dp(n + 1);
    dp[1][0] = 2 * p[1].second - p[1].first - 1;
    dp[1][1] = p[1].second - 1;
    for (int i = 2; i <= n; ++i) {
        dp[i][0] = std::min(dp[i - 1][0] + abs(p[i - 1].first - p[i].second) + p[i].second - p[i].first + 1,
                            dp[i - 1][1] + abs(p[i - 1].second - p[i].second) + p[i].second - p[i].first + 1);
        dp[i][1] = std::min(dp[i - 1][0] + abs(p[i - 1].first - p[i].first) + p[i].second - p[i].first + 1,
                            dp[i - 1][1] + abs(p[i - 1].second - p[i].first) + p[i].second - p[i].first + 1);
    }
    std::cout << std::min(dp[n][0] + n - p[n].first, dp[n][1] + n - p[n].second) << "\n";
    return 0;
}