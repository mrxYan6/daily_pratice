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
    std::vector<std::vector<int>> g(n + 1);
    for (int i = 0; i < n; ++i) {
        int u;
        int k;
        std::cin >> u >> k;
        for (int j = 0; j < k; ++j) {
            int v;
            std::cin >> v;
            g[u].push_back(v);
        }
    }

    std::vector<std::array<int, 2>> dp(n + 1);
    std::function<void(int, int)> dfs = [&](int u, int fa) {
        dp[u][1] = 1;
        for (auto v: g[u]) {
            if (v == fa)continue;
            dfs(v, u);
            dp[u][0] += dp[v][1];
            dp[u][1] += std::min(dp[v][1], dp[v][0]);
        }
    };

    dfs(0, -1);
    std::cout << std::min(dp[0][0], dp[0][1]) << '\n';
    return 0;
}