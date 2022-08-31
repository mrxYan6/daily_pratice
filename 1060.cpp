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
    std::cin >> n >> m;
    std::vector<ll> w(m), v(m);

    std::vector<ll> dp(n + 1, -0x3f3f3f3f3f3f3f3f);
    for (int i = 0; i < m; ++i) {
        std::cin >> w[i] >> v[i];
        v[i] *= w[i];
    }

    dp[n] = 0;

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j <= n - w[i]; ++j) {
            dp[j] = std::max(dp[j], dp[j + w[i]] + v[i]);
        }
    }
    std::cout << *std::max_element(dp.begin(), dp.end()) << '\n';

    return 0;
}