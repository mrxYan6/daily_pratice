//
// Created by mrx on 2022/7/31.
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
    int n, m, k, r;
    std::cin >> n >> m >> k >> r;

    std::vector<int> nedt(n), val(m), cst(m);

    for (int i = 0; i < n; ++i)std::cin >> nedt[i];
    for (int j = 0; j < m; ++j)std::cin >> cst[j];
    for (int j = 0; j < m; ++j)std::cin >> val[j];

    std::vector<int> dp(r + 1, -0x3f3f3f3f);
    dp[r] = 0;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j <= r - cst[i]; ++j) {
            dp[j] = std::max(dp[j], dp[j + cst[i]] + val[i]);
        }
    }
    std::vector<int> dp2(r + 1, -0x3f3f3f3f);
    for (int i = 0; i <= r; ++i)if (dp[i] >= k)dp2[i] = 0;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= r - nedt[i]; ++j) {
            dp2[j] = std::max(dp2[j], dp2[j + nedt[i]] + 1);
        }
    }
    int ans = *std::max_element(dp2.begin(), dp2.end());
    std::cout << ans << '\n';
    return 0;
}