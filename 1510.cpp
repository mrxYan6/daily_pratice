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
    int n, v, c;
    std::cin >> v >> n >> c;

    std::vector<int> w(n), d(n);
    for (int i = 0; i < n; ++i)std::cin >> d[i] >> w[i];

    std::vector<ll> dp(c + 1, -0x3f3f3f3f3f3f3f3f);
    dp[c] = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= c - w[i]; ++j) {
            dp[j] = std::max(dp[j], dp[j + w[i]] + d[i]);
        }
    }

    int ans = -1;
    for (int i = 0; i <= c; ++i) {
        if (dp[i] >= v)ans = i;
    }

    if (~ans)std::cout << ans << '\n';
    else std::cout << "Impossible\n";
    return 0;
}