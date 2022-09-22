//
// Created by mrx on 2022/8/10.
//
#include <bits/stdc++.h>

using ll = long long;

void sol() {
    int n;
    std::cin >> n;
    std::vector<std::array<ll, 2>> building(n);
    for (int i = 0; i < n; ++i)std::cin >> building[i][0] >> building[i][1];
    std::vector<std::array<ll, 2>> prefix_sum2(n + 2), suffix_sum2(n + 2);
    std::vector<std::array<ll, 2>> prefix_sum1(n + 2), suffix_sum1(n + 2);

    for (int i = 1; i <= n; ++i) {
        prefix_sum1[i][0] = prefix_sum1[i - 1][0] + building[i - 1][0];
        prefix_sum1[i][1] = prefix_sum1[i - 1][1] + building[i - 1][1];
    }
    for (int i = 1; i <= n; ++i) {
        prefix_sum2[i][0] = prefix_sum2[i - 1][0] + prefix_sum1[i][0];
        prefix_sum2[i][1] = prefix_sum2[i - 1][1] + prefix_sum1[i][1];
    }

    for (int i = n; i > 0; --i) {
        suffix_sum1[i][0] = suffix_sum1[i + 1][0] + building[i - 1][0];
        suffix_sum1[i][1] = suffix_sum1[i + 1][1] + building[i - 1][1];
    }
    for (int i = n; i > 0; --i) {
        suffix_sum2[i][0] = suffix_sum1[i][0] + suffix_sum2[i + 1][0];
        suffix_sum2[i][1] = suffix_sum1[i][1] + suffix_sum2[i + 1][1];
    }

    std::vector<std::vector<ll>> dp(n + 1, std::vector<ll>(2, 0x3f3f3f3f3f3f3f3f));
    auto cacal = [&](int l, int r, int type) {
        return prefix_sum2[r][type] - prefix_sum2[l - 1][type] - (r - l + 1) * prefix_sum1[l - 1][type];
    };
    auto cacal2 = [&](int l, int r, int type) {
        return suffix_sum2[l][type] - suffix_sum2[r + 1][type] - (r - l + 1) * suffix_sum1[r + 1][type];
    };
    auto cost = [&](int l, int r, int type) -> ll {
        if (l == 1 && r == n) {
            return 0x3f3f3f3f3f3f3f3f;
        } else if (l == 1) {
            return cacal(l, r, type);
        } else if (r == n) {
            return cacal2(l, r, type);
        } else {
            int mid = (l + r) >> 1;
            ll ret = 0;
            ret += cacal(mid + 1, r, type);
            ret += cacal2(l, mid, type);
            return ret;
        }
    };

    dp[0][0] = dp[0][1] = 0;
    for (int i = 1; i <= n; ++i) {
        dp[i][0] = dp[i][1] = 0x3f3f3f3f3f3f3f3f;
        for (int j = 0; j < i; ++j) {
            dp[i][0] = std::min(dp[i][0], dp[j][1] + cost(j + 1, i, 0));
            dp[i][1] = std::min(dp[i][1], dp[j][0] + cost(j + 1, i, 1));
        }
    }

    std::cout << std::min(dp[n][0], dp[n][1]) << '\n';
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
#ifdef ONLINE_JUDGE
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#endif
    int t;
    std::cin >> t;
    for (int i = 1; i <= t; ++i) {
        std::cout << "Case #" << i << ": ";
        sol();
    }
    return 0;
}