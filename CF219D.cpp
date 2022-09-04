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
    int n;
    std::cin >> n;
    std::vector<std::vector<std::pair<int, int>>> g(n + 1);
    for (int i = 1; i < n; ++i) {
        int u, v;
        std::cin >> u >> v;
        g[u].emplace_back(v, 0);
        g[v].emplace_back(u, 1);
    }
    std::vector<int> cost(n + 1, 0);
    std::function<void(int, int)> dfs1 = [&](int u, int fa) {
        for (auto [v, c]: g[u]) {
            if (v == fa)continue;
            dfs1(v, u);
            cost[u] += c + cost[v];
        }
    };
    std::vector<int> dp(n + 1);

    std::function<void(int, int)> dfs2 = [&](int u, int fa) {
        for (auto [v, c]: g[u]) {
            if (v == fa)continue;
            dp[v] = dp[u] + (c == 1 ? -1 : 1);
            dfs2(v, u);
        }
    };

    dfs1(1, 0);
    dp[1] = cost[1];
    dfs2(1, 0);
    int ans = *std::min_element(dp.begin() + 1, dp.end());
    std::cout << ans << '\n';
    for (int i = 1; i <= n; ++i) {
        if (dp[i] == ans)std::cout << i << ' ';
    }

    return 0;
}