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
    int m, n;
    std::cin >> m >> n;

    std::vector<int> dp(m + 1, -0x3f3f3f3f);

    dp[0] = 0;

    for (int i = 0; i < n; ++i) {
        int v, w;
        std::cin >> w >> v;
        for (int j = v; j <= m; ++j) {
            dp[j] = std::max(dp[j], dp[j - v] + w);
        }
    }

    std::cout << *std::max_element(dp.begin(), dp.end()) << '\n';

    return 0;
}