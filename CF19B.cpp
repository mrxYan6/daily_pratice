//
// Created by mrx on 2022/8/4.
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
    std::vector<std::pair<int, int>> p(n);
    int max = 0;
    for (int i = 0; i < n; ++i) {
        std::cin >> p[i].first >> p[i].second;
        max = std::max(p[i].first, max);
    }

    std::vector<ll> dp(n + max + 1, 0x3f3f3f3f3f3f3f3f);
    dp[0] = 0;
    for (auto [t, c]: p) {
        for (int j = n + max; j >= t + 1; --j) {
            dp[j] = std::min(dp[j], dp[j - t - 1] + c);
        }
    }
    ll ans = 0x3f3f3f3f3f3f3f3f;
    for (int i = n; i <= n + max; ++i)ans = std::min(ans, dp[i]);
    std::cout << ans << '\n';
    return 0;
}