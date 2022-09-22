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
    int t, n, m;
    std::cin >> t >> n >> m;
    std::vector<std::vector<int>> p(t, std::vector<int>(n));

    for (int i = 0; i < t; ++i) for (int j = 0; j < n; ++j)std::cin >> p[i][j];
    //I天的时候有前j个纪念品,有k元钱,i+1天卖出所有的马内
    int ans = m;
    for (int i = 0; i < t - 1; ++i) {
        std::vector<int> dp(ans + 1, -0x3f3f3f3f);
        dp[ans] = ans;
        for (int j = 0; j < n; ++j) {
            for (int k = ans; k >= p[i][j]; --k) {
                dp[k - p[i][j]] = std::max(dp[k - p[i][j]], dp[k] + p[i + 1][j] - p[i][j]);
            }
        }
        int nxtmn = 0;
        for (int j = 0; j <= ans; ++j)nxtmn = std::max(dp[j], nxtmn);
        ans = nxtmn;
    }
    std::cout << ans << '\n';\
    return 0;
}