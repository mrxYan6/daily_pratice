//
// Created by mrx on 2022/8/3.
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
    int n, k, v;
    std::cin >> k >> v >> n;
    std::vector<std::vector<ll>> dp(v + 1, std::vector<ll>(k, -0x3f3f3f3f3f3f3f3f));

    dp[0][0] = 0;
    for (int i = 0; i < n; ++i) {
        int vol, value;
        std::cin >> vol >> value;
        for (int j = v; j >= vol; --j) {
            auto prev = dp[j - vol];
            for (auto &x: prev)x += value;
            auto cur(prev);
            for (auto y: dp[j])cur.push_back(y);
            std::sort(cur.begin(), cur.end(), std::greater());
            dp[j] = std::vector(cur.begin(), cur.begin() + k);
        }
    }

    ll ans = 0;
    for (auto &x: dp[v])ans += x;
    std::cout << ans << '\n';
    return 0;
}