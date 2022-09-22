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
    int n, m;
    std::cin >> n >> m;
    std::vector<int> cost(n + 1);
    cost[0] = m;
    for (int i = 1; i <= n; ++i) {
        std::cin >> cost[i];
        cost[i] += cost[i - 1];
    }
    for (int i = 1; i <= n; ++i)cost[i] += m;

    std::vector<int> dp(n + 1, 0x3f3f3f3f);
    dp[0] = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = i; j <= n; ++j) {
            dp[j] = std::min(dp[j], dp[j - i] + cost[i]);
        }
    }
    std::cout << dp[n] - m << '\n';
    return 0;
}