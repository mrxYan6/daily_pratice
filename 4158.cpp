//
// Created by mrx on 2023/4/11.
//sig=
#include <functional>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
#include <cmath>
#include <queue>
#include <array>
#include <map>

using i64 = long long;

void solve() {
    int n, m, t;
    std::cin >> n >> m >> t;
    std::vector cells(n + 1, std::vector<int>(m + 1));
    for (int i = 0; i < n; ++i) {
        cells[i][0] = 0;
        for (int j = 1; j <= m; ++j) {
            char c;
            std::cin >> c;
            cells[i][j] = c == '1';
            cells[i][j] += cells[i][j - 1];
        }
    }

    std::vector dp(n + 1, std::vector(m + 1, std::vector(m + 1, 0)));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            for (int k = 1; k <= m; ++k) {
                for (int l = j - 1; l < k; ++l) {
                    dp[i][j][k] = std::max(dp[i][j][k], dp[i][j - 1][l] + std::max(cells[i - 1][k] - cells[i - 1][l], k - l - cells[i - 1][k] + cells[i - 1][l]));
                }
            }
        }
    }

    std::vector ans(n + 1, std::vector(t + 1, 0));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= t; ++j) {
            for (int k = 0; k <= std::min(j, m); ++k) {
                ans[i][j] = std::max(ans[i][j], ans[i - 1][j - k] + dp[i][k][m]);
            }
        }
    }
    std::cout << *std::max_element(ans[n].begin(), ans[n].end()) << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    solve();

    return 0;
}