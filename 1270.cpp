//
// Created by mrx on 2022/9/4.
//
#include <bits/stdc++.h>

using ll = long long;

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
#endif
#ifndef LOCAL
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#endif
    int limit;
    std::cin >> limit;
    std::vector<std::pair<int, int>> s;
    s.emplace_back(0, 0);
    int tot = 0;
    int c, paint;
    while (std::cin >> c >> paint) {
        s.emplace_back(c * 2, paint);
        tot += paint;
    }
    int n = s.size();
    std::vector<std::vector<std::pair<int, int>>> G(n + 1);
    std::vector<int> fa(n + 1);
    std::vector<int> wei(n + 1);
    int cur = 1;
    std::function<void(int)> build = [&](int id) {
        wei[id] = s[id].second;
        if (wei[id] == 0) {
            G[id].emplace_back(cur + 1, s[cur + 1].first);
            build(++cur);//ls
            G[id].emplace_back(cur + 1, s[cur + 1].first);
            build(++cur);//rs
        }
    };
    G[0].emplace_back(1, s[1].first);
    build(1);
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(tot + 1, 0x3f3f3f3f));

    std::function<void(int)> dfs = [&](int u) {
        if (G[u].empty()) {
            for (int i = 0; i <= wei[u]; ++i) {
                dp[u][i] = i * 5;
            }
        }
        dp[u][0] = 0;
        for (auto [v, w]: G[u]) {
            dfs(v);
            wei[u] += wei[v];
            for (int i = std::min(tot, wei[u]); i >= 1; --i) {
                for (int j = std::min(i , wei[v]); j >= 0; --j) {
                    dp[u][i] = std::min(dp[u][i], dp[u][i - j] + dp[v][j] + w);
                }
            }
        }

    };
    dfs(0);
    int ans = 0;
    for (int i = 0; i <= tot; ++i) {
        if (dp[0][i] <limit)ans = i;
    }
    std::cout << ans << '\n';
    return 0;
}