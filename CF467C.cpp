//
// Created by mrx on 2023/2/22.
//
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
    int n, m, k;
    std::cin >> n >> m >> k;
    std::vector<i64> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        std::cin >> a[i];
        a[i] += a[i - 1];
    }

    std::vector dp(n + 1, std::vector<i64>(k + 1));

    for (int i = m; i <= n; ++i) {
        for (int j = 1; j <= k; ++j) {
            dp[i][j] = dp[i - 1][j];
            dp[i][j] = std::max(dp[i][j], dp[i - m][j - 1] + a[i] - a[i - m]);
        }
    }

    i64 ans = 0;
    for (int i = 1; i <= n; ++i)ans = std::max(ans, dp[i][k]);
    std::cout << ans << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    solve();

    return 0;
}
