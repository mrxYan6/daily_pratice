//
// Created by mrx on 2022/8/1.
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
    int a[3];
    int n;
    std::cin >> n >> a[0] >> a[1] >> a[2];
    std::vector<int> dp(n + 1, -0x3f3f3f3f);
    dp[0] = 0;

    for (int i: a) {
        for (int j = i; j <= n; ++j) {
            dp[j] = std::max(dp[j - i] + 1, dp[j]);
        }
    }
    std::cout << dp[n] << '\n';

    return 0;
}