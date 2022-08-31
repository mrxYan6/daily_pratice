//
// Created by mrx on 2022/7/16.
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
    std::string c, p;
    std::cin >> c >> p;
    std::vector<std::vector<int>> d(4, std::vector<int>(4));
    std::unordered_map<char, int> mp;
    mp['A'] = 0, mp['T'] = 1, mp['G'] = 2, mp['C'] = 3;

    for (int i = 0; i < 4; ++i) for (int j = 0; j < 4; ++j)std::cin >> d[i][j];

    int A, B;
    std::cin >> A >> B;

    auto getG = [&](int k) {
        return -A - B * (k - 1);
    };
    int n = c.length(), m = p.length();

    std::vector<int> x(n + 1, -1), y(m + 1, -1);
    for (int i = 1; i <= n; ++i) x[i] = mp[c[i - 1]];
    for (int i = 1; i <= m; ++i) y[i] = mp[p[i - 1]];

    std::vector<std::vector<std::vector<ll>>>
            dp(n + 1, std::vector<std::vector<ll>>(m + 1, std::vector<ll>(3, -0x3f3f3f3f3f3f3f3f)));

    dp[0][0][0] = 0;
    for (int i = 1; i <= n; ++i)dp[i][0][2] = -A - (i - 1) * B;
    for (int i = 1; i <= m; ++i)dp[0][i][1] = -A - (i - 1) * B;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            dp[i][j][2] = std::max({dp[i - 1][j][0] - A, dp[i - 1][j][2] - B, dp[i - 1][j][1] - A});
            dp[i][j][1] = std::max({dp[i][j - 1][0] - A, dp[i][j - 1][1] - B, dp[i][j - 1][2] - A});
            dp[i][j][0] = std::max(
                    {dp[i - 1][j - 1][0] + d[x[i]][y[j]], dp[i - 1][j - 1][2] + d[x[i]][y[j]],
                     dp[i - 1][j - 1][1] + d[x[i]][y[j]]});
        }
    }
    std::cout << std::max({dp[n][m][0], dp[n][m][1], dp[n][m][2]}) << '\n';
    return 0;
}