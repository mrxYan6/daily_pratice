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
    int m;
    std::cin >> m;

    std::vector<ll> dp(m + 1, 0x3f3f3f3f3f);
    dp[0] = 0;

    for (int i = 1; i <= sqrt(sqrt(m)) + 0.5; ++i) {
        int cur = i * i * i * i;
        for (int j = cur; j <= m; ++j) {
            dp[j] = std::min(dp[j], 1 + dp[j - cur]);
        }
//        for (auto &x: dp)std::cerr << x << ' ';
//        std::cerr << '\n';
    }
    std::cout << dp[m] << '\n';

    return 0;
}