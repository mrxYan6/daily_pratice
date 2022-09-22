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
    int money, m, n;
    std::cin >> money >> m >> n;
    std::vector<std::pair<int, int>> kind(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> kind[i].first >> kind[i].second;
    }

    for (int i = 0; i < m; ++i) {
        std::vector<int> dp(money + 1, -0X3F3F3F3F);
        dp[0] = 0;
        for (auto [a, b]: kind) {
            for (int j = 0; j <= money - a; ++j) {
                dp[j + a] = std::max(dp[j + a], dp[j] + b);
            }
        }

        money += *std::max_element(dp.begin(), dp.end());
//        std::cerr << money << ' ';
    }
    std::cout << money << '\n';

    return 0;
}