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
    std::vector<std::vector<int>> G(n + 1);
    for (int i = 1; i < n; ++i) {
        int u, v;
        std::cin >> u >> v;
        G[u].push_back(v), G[v].push_back(u);
    }

    std::vector<long long> dep(n + 1), size(n + 1), dp(n + 1);

    std::function<void(int, int)> dfs1 = [&](int u, int fa) {
        size[u] = 1;
        dep[u] = dep[fa] + 1;
        for (auto v: G[u]) {
            if (v == fa)continue;
            dfs1(v, u);
            size[u] += size[v];
        }
    };

    std::function<void(int, int)> dfs2 = [&](int u, int fa) {
        for (auto v: G[u]) {
            if (v == fa)continue;
            dp[v] = dp[u] + n - 2 * size[v];
            dfs2(v, u);
        }
    };

    dep[0] = -1;
    dfs1(1, 0);
    for (int i = 1; i <= n; ++i)dp[1] += dep[i];
    dfs2(1, 0);

    std::cout << std::max_element(dp.begin(), dp.end()) - dp.begin() << '\n';
    return 0;
}