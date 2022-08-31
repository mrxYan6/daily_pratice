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
    ll n, m, t;
    std::cin >> n >> m >> t;

    std::vector<ll> cm(n), ct(n);
    for (ll i = 0; i < n; ++i)std::cin >> cm[i] >> ct[i];

    std::vector<std::vector<ll>> dp(m + 1, std::vector<ll>(t + 1, -0x3f3f3f3f));
    dp[m][t] = 0;

    for (ll i = 0; i < n; ++i) {
        for (ll j = 0; j <= m - cm[i]; ++j) {
            for (ll k = 0; k <= t - ct[i]; ++k)
                dp[j][k] = std::max(dp[j][k], dp[j + cm[i]][k + ct[i]] + 1);
        }
    }
    ll ans = 0;
    for (auto &x: dp)for (auto y: x)ans = std::max(ans, y);
    std::cout << ans << '\n';
    return 0;
}