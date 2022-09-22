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
    ll n;
    std::cin >> n;
    std::vector<ll> pri, vis(n + 1, 0);
    vis[0] = vis[1] = 0;
    pri.push_back(1);
    for (ll i = 2; i <= n; ++i) {
        if (!vis[i]) { pri.push_back(i); }
        for (auto j: pri) {
            if (i * j <= n)
                vis[i * j] = 1;
//            if (i * j > n || i % j)break;
        }
    }

    for (auto &x: pri)std::cerr << x << ' ';
    std::cerr << '\n';

    std::vector<ll> dp(n + 1, 0);
    dp[0] = 1;
    for (auto x: pri) {
        if (x == 1)continue;
        for (ll j = x; j <= n; ++j) {
            dp[j] += dp[j - x];
        }
    }
    std::cout << dp[n] << '\n';
    return 0;
}