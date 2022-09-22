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
    int n;
    std::cin >> n;
    int sum = (n) * (n + 1) / 2;
    if (sum & 1) {
        std::cout << 0 << '\n';
        return 0;
    }
    std::vector<ll> dp(1 + sum / 2, 0);
    dp[sum / 2] = 1;
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= sum / 2 - i; ++j) {
            dp[j] += dp[j + i];
        }
    }
    std::cout << dp[0] / 2 << '\n';
    return 0;
}