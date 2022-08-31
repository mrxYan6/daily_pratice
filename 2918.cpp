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
    int n, h;
    std::cin >> n >> h;

    std::vector<std::pair<int, int>> comp(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> comp[i].first >> comp[i].second;
    }

    std::vector<ll> dp(h + 1, 0x3f3f3f3f3f3f3f3f);
    dp[0] = 0;
    for (auto [w, v]: comp) {
        for (int i = 0; i <= h; ++i) {
            dp[std::min(h, i + w)] = std::min(dp[std::min(h, i + w)], dp[i] + v);
        }
    }

    std::cout << dp[h] << '\n';

    return 0;
}