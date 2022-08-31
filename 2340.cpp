//
// Created by mrx on 2022/8/9.
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
    std::vector<std::pair<int, int>> cow(n);
    int sum = 0;
    for (int i = 0; i < n; ++i) {
        std::cin >> cow[i].first >> cow[i].second;
        if (cow[i].first > 0)sum += cow[i].first;
    }
    std::sort(cow.begin(), cow.end());
    std::reverse(cow.begin(), cow.end());
    std::vector<int> dp(sum + 1, -0x3f3f3f3f);
    dp[0] = 0;
    for (auto [iq, eq]: cow) {
        std::vector<int> ndp(dp);
        for (int i = 0; i <= sum; ++i) {
            if (iq + i >= 0 && iq + i <= sum) {
                ndp[i + iq] = std::max(dp[i] + eq, dp[i + iq]);
            }
        }
        dp = ndp;
//        for (auto x: dp)std::cerr << x << ' ';
//        std::cerr << '\n';
    }
    int ans = 0;
    for (int i = 0; i <= sum; ++i) {
        if (dp[i] >= 0)
            ans = std::max(ans, dp[i] + i);
    }
    std::cout << ans << '\n';
    return 0;
}