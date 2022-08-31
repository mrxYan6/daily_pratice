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
    int mv, mw, n;
    std::cin >> mv >> mw >> n;
    std::vector<ll> cv(n), cw(n), w(n);
    for (int i = 0; i < n; ++i)std::cin >> cv[i] >> cw[i] >> w[i];

    std::vector<std::vector<ll>> dp(mv + 1, std::vector<ll>(mw + 1, -0x3f3f3f3f3f3f3f3f));
    dp[mv][mw] = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= mv - cv[i]; ++j) {
            for (int k = 0; k <= mw - cw[i]; ++k) {
                dp[j][k] = std::max(dp[j][k], dp[j + cv[i]][k + cw[i]] + w[i]);
            }
        }
    }

    ll ans = 0;
    for (auto &x: dp)for (auto &y: x)ans = std::max(ans, y);
    std::cout << ans << '\n';
    return 0;
}