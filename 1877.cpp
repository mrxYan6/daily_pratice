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
    int n, bg, mx;
    std::cin >> n >> bg >> mx;

    std::vector<int> dp(mx + 1);
    dp[bg] = 1;
    for (int i = 0; i < n; ++i) {
        int c;
        std::cin >> c;
        std::vector<int> ndp(mx + 1);
        for (int j = 0; j <= mx; ++j) {
            if (dp[j] == 0)continue;
            if (j + c <= mx)ndp[j + c] = 1;
            if (j >= c)ndp[j - c] = 1;
        }
        dp = ndp;
    }
    int ans = -1;
    for (int i = 0; i <= mx; ++i)if (dp[i])ans = i;
    std::cout << ans << '\n';
    return 0;
}