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
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<int>> G(n + 1);
    m++;

    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(m + 1, 0));
    std::vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        int s, k;
        std::cin >> k >> s;
        dp[i][1] = s;
        G[k].push_back(i);
    }
    std::vector<int> size(n + 1, 0);
    std::function<void(int, int)> dfs = [&](int u, int fa) {
        size[u] = 1;
        for (auto v: G[u]) {
            if (v == fa)continue;
            dfs(v, u);
            size[u] += size[v];
            for (int i = std::min(m, size[u]); i > 1; --i) {
                for (int j = std::min(i - 1, size[v]); j >= 0; --j) {
                    dp[u][i] = std::max(dp[u][i], dp[u][i - j] + dp[v][j]);
                }
            }
        }
    };
    dfs(0, -1);
    std::cout << dp[0][m] << '\n';
    return 0;
}