//
// Created by mrx on 2022/7/17.
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
    std::vector<int> G[m + 1];
    std::vector<std::pair<int, int>> p(m + 1);
    for (int i = 1; i <= m; ++i) {
        std::cin >> p[i].first >> p[i].second;
        p[i].second *= p[i].first;
        int fa;
        std::cin >> fa;
        G[fa].push_back(i);
    }

    std::vector<int> dp(n + 1, 0);
    for (auto fa: G[0]) {
        std::vector<std::pair<int, int>> wp;
        wp.push_back(p[fa]);
        for (int l = 0; l < G[fa].size(); ++l) {
            auto [w, v] = p[fa];
            for (int r = l; r < G[fa].size(); ++r) {
                w += p[G[fa][r]].first;
                v += p[G[fa][r]].second;
                wp.emplace_back(w, v);
            }
        }
        for (int i = n; i >= 0; --i) {
            for (auto [w, v]: wp) {
                if (i - w >= 0) {
                    dp[i] = std::max(dp[i], dp[i - w] + v);
                }
            }
        }
    }
    std::cout << dp[n] << '\n';

    return 0;
}