//
// Created by mrx on 2022/8/1.
//
#include <bits/stdc++.h>

using ll = long long;

int main() {
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stderr);
#endif
#ifdef ONLINE_JUDGE
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#endif
    int n, m, k;
    std::cin >> n >> m >> k;

    std::vector<int> up(n + 1), down(n + 1);
    for (int i = 1; i <= n; ++i) {
        std::cin >> up[i] >> down[i];
    }
    std::vector<std::pair<int, int>> tube(n + 1, std::pair<int, int>(0, m + 1));

    for (int i = 0; i < k; ++i) {
        int x, u, d;
        std::cin >> x >> u >> d;
        tube[x] = {u, d};
    }

    std::vector<int> dp(m + 1, 0);
    int cnt = 0;
    dp[0] = 0x3f3f3f3f;
    for (int i = 1; i <= n; ++i) {
        std::vector<int> ndp(m + 1, 0x3f3f3f3f);
        int x = up[i], y = down[i];

        for (int j = 0; j <= m; ++j) {
            int nxt = std::min(m, j + x);
            ndp[nxt] = std::min({ndp[j] + 1, ndp[nxt], dp[j] + 1});
        }

        for (int j = m; j > y; --j) {
            int nxt = j - y;
            ndp[nxt] = std::min(ndp[nxt], dp[j]);
        }
        for (int j = 0; j <= m; ++j)if (j <= tube[i].first || j >= tube[i].second)ndp[j] = 0x3f3f3f3f;
        if (*std::min_element(ndp.begin(), ndp.end()) == 0x3f3f3f3f) {
            std::cout << 0 << '\n';
            std::cout << cnt << '\n';
            return 0;
        }
        if (tube[i] != std::make_pair(0, m + 1))cnt++;
        dp = ndp;
    }

    int ans = *std::min_element(dp.begin(), dp.end());
    std::cout << 1 << '\n';
    std::cout << ans << '\n';
    return 0;
}
