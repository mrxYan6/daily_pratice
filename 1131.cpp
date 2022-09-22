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
    int rt;
    std::cin >> rt;
    std::vector<std::pair<long long, long long >> G[n + 1];
    for (int i = 1; i < n; ++i) {
        long long u, v, w;
        std::cin >> u >> v >> w;
        G[u].emplace_back(v, w);
        G[v].emplace_back(u, w);
    }
    std::vector<long long> dp(n + 1), dis(n + 1);
    std::function<long long(int, int)> dfs = [&](int u, int fa) {
        long long mx = 0;
        for (auto [v, w]: G[u]) {
            if (v == fa)continue;
            dis[v] = dfs(v, u);
            dp[u] += dp[v];
            mx = std::max(mx, w + dis[v]);
        }
        for (auto [v, w]: G[u]) {
            if (v == fa)continue;
            dp[u] += mx - w - dis[v];
        }
        return mx;
    };

    dfs(rt, 0);
    std::cout << dp[rt] << '\n';
    return 0;
}