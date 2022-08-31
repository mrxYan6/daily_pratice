//
// Created by mrx on 2022/8/9.
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
    int n;
    std::cin >> n;
    std::vector<int> digit(2 * n), operate(2 * n);
    for (int i = 0; i < n; ++i) {
        char opt;
        int x;
        std::cin >> opt >> x;
        digit[i] = digit[i + n] = x;
        operate[i] = operate[i + n] = (opt == 'x');
    }

    std::vector<std::vector<ll>> dp(2 * n, std::vector<ll>(n + 1, -0x3f3f3f3f3f3f3f3f));
    std::vector<std::vector<ll>> dp2(2 * n, std::vector<ll>(n + 1, 0x3f3f3f3f3f3f3f3f));
    for (ll i = 0; i < 2 * n; ++i)dp2[i][1] = dp[i][1] = digit[i];

    for (ll len = 2; len <= n; ++len) {
        for (ll l = 0; l < 2 * n; ++l) {
            ll r = len + l;
            if (r >= 2 * n)break;
            for (ll k = 1; k < len; ++k) {
                if (operate[l + k]) {
                    dp[l][len] = std::max({dp[l][len], dp[l][k] * dp[l + k][len - k],
                                           dp2[l][k] * dp[l + k][len - k],
                                           dp[l][k] * dp2[l + k][len - k],
                                           dp2[l][k] * dp2[l + k][len - k]});
                    dp2[l][len] = std::min({dp2[l][len], dp[l][k] * dp[l + k][len - k],
                                            dp2[l][k] * dp[l + k][len - k],
                                            dp[l][k] * dp2[l + k][len - k],
                                            dp2[l][k] * dp2[l + k][len - k]});
                } else {
                    dp[l][len] = std::max(dp[l][len], dp[l][k] + dp[l + k][len - k]);
                    dp2[l][len] = std::min(dp2[l][len], dp2[l][k] + dp2[l + k][len - k]);
                }
            }
        }


    }

    ll ans = -0x3f3f3f3f3f3f3f3f;
    for (ll i = 0; i < n; ++i)ans = std::max(ans, dp[i][n]);
    std::cout << ans << '\n';

    for (ll i = 0; i < n; ++i)if (dp[i][n] == ans)std::cout << i + 1 << ' ';
    return 0;
}