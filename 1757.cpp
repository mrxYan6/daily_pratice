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
    std::cin >> m >> n;

    std::vector<std::pair<int, int>> kind[n + 1];
    std::vector<int> dp(m + 1, -0x3f3f3f3f);
    dp[m] = 0;

    for (int i = 0; i < n; ++i) {
        int w, v, k;
        std::cin >> w >> v >> k;
        kind[k].emplace_back(w, v);
    }

    for (int i = 1; i <= n; ++i) {
        std::vector<int> ndp(m + 1, -0x3f3f3f3f);
        for (auto [w, v]: kind[i]) {
            for (int k = 0; k <= m - w; ++k) {
                ndp[k] = std::max(ndp[k], dp[k + w] + v);
            }
        }
        for (int j = 0; j <= m; ++j)dp[j] = std::max(dp[j], ndp[j]);
    }
    std::cout << *std::max_element(dp.begin(), dp.end()) << '\n';

    return 0;
}