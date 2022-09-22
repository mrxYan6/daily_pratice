//
// Created by mrx on 2022/8/10.
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
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<int>> G(n, std::vector<int>(n, 0x3f3f3f3f));
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        std::cin >> u >> v >> w;
        u--, v--;
        G[u][v] = G[v][u] = std::min(G[u][v], w);
    }

    std::vector<std::vector<std::vector<ll>>> dp(n + 1, std::vector<std::vector<ll>>(n + 1, std::vector<ll>(1 << n, 0x3f3f3f3f)));
    //i->root    j->point set   k->depth  val->ans
    std::vector<std::vector<std::vector<int>>> vis(n + 1, std::vector<std::vector<int>>(n + 1, std::vector<int>(1 << n, 0)));
    int all = (1 << n) - 1;
    std::function<ll(int, int, int)> dfs = [&](int root, int dep, int s) {
        auto &x = dp[root][dep][s];
        if (s == 0)return x = 0;
        if (vis[root][dep][s])return x;
        vis[root][dep][s] = true;
        x = 0x3f3f3f3f;
        for (int v = 0; v < n; ++v) {
            if (G[root][v] != 0x3f3f3f3f && (s >> v & 1))
                for (int s0 = s; s0; s0 = (s0 - 1) & s) {
                    if (s0 >> v & 1)
                        x = std::min(x, dfs(v, dep + 1, s0 ^ (1 << v)) + dep * G[root][v] + dfs(root, dep, s ^ s0));

                }
        }
        return x;
    };
    ll ans = 0x3f3f3f3f3f3f3f3f;
    for (int start = 0; start < n; ++start) {
        ans = std::min(ans, dfs(start, 1, all ^ (1 << start)));
    }

    std::cout << ans << '\n';
    return 0;
}