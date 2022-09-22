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
    int n, m;
    std::cin >> m >> n;
    std::vector<int> v(n);
    for (int i = 0; i < n; ++i)std::cin >> v[i];

    std::vector<int> dp(m + 1, -0x3f3f3f3f);
    dp[m] = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= m - v[i]; ++j) {
            dp[j] = std::max(dp[j], dp[j + v[i]] + v[i]);
        }
    }

    std::cout << *std::max_element(dp.begin(), dp.end()) << '\n';
    return 0;
}