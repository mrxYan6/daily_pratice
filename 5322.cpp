//
// Created by mrx on 2022/8/3.
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
    int s, n, m;
    std::cin >> s >> n >> m;
    std::vector<std::vector<std::pair<int, int>>> x(n + 1, std::vector<std::pair<int, int>>(s + 1, std::pair(-1, 0)));

    for (int i = 1; i <= s; ++i) {
        for (int j = 1; j <= n; ++j) {
            std::cin >> x[j][i].first;
            x[j][i].first *= 2;
            x[j][i].first++;
        }
    }
    for (int i = 1; i <= n; ++i) {
        std::sort(x[i].begin(), x[i].end());
        for (int j = 1; j <= s; ++j)x[i][j].second = i * j;
    }

    std::vector<ll> dp(m + 1, 0);
    for (int i = 1; i <= n; ++i) {
        std::vector<ll> ndp(dp);
        for (int j = 1; j <= s; ++j) {
            auto w = x[i][j].first, c = x[i][j].second;
            for (int k = m; k >= w; --k) {
                ndp[k] = std::max(ndp[k], dp[k - w] + c);
            }
        }
        dp = ndp;
    }
    std::cout << *std::max_element(dp.begin(), dp.end()) << '\n';
    return 0;
}