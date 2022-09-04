//
// Created by mrx on 2022/9/4.
//
#include <bits/stdc++.h>

using ll = long long;

struct edge
{
    int v;
    int wei;
    edge(int v, int w) : v(v), wei(w) {}
};

int main()
{
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
#endif
#ifndef LOCAL
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#endif
    int n, q;
    std::cin >> n >> q;
    std::vector<edge> G[n + 1];
    for (int i = 1; i < n; ++i)
    {
        int u, v, w;
        std::cin >> u >> v >> w;
        G[u].emplace_back(v, w);
        G[v].emplace_back(u, w);
    }

    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(q + 1, 0));
    std::vector<int> size(n + 1, 0);
    std::function<void(int, int)> dfs = [&](int u, int fa)
    {
        size[u] = 1;
        for (auto [v, wei] : G[u])
        {
            if (v == fa)
                continue;
            dfs(v,u);
            size[u] += size[v];
            for (int i = std::min(q, size[u]); i; --i)
            {
                for (int j = std::min(i - 1, size[v]); j >= 0; --j)
                {
                    dp[u][i]=std::max(dp[u][i],dp[u][i-j-1]+dp[v][j]+wei);
                }
            }
        }
    };
    dfs(1,-1);
    std::cout<<dp[1][q]<<'\n';
    return 0;
}