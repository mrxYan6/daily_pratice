//
// Created by mrx on 2022/8/3.
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
    ll m;
    std::cin >> n >> m;
    std::vector<std::pair<int, int>> p(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> p[i].first;
    }
    int maxcost = 0;
    for (int i = 0; i < n; ++i) {
        std::cin >> p[i].second;
        maxcost += p[i].first * p[i].second;
    }

    std::vector<ll> dp(maxcost + 1, 0);
    dp[0] = 1;
    for (int i = 0; i < n; ++i) {
        std::vector<ll> ndp(dp);
        for (int j = 1; j <= p[i].first; ++j) {
//            std::cout << j << '*';
            for (int k = j * p[i].second; k <= maxcost; ++k) {
                ndp[k] = std::max(ndp[k], dp[k - j * p[i].second] * j);
            }
        }
        dp = ndp;
//        for (auto x: dp)std::cerr << x << ' ';
//        std::cerr << '\n';
    }

    for (int i = 0; i <= maxcost; ++i) {
        if (dp[i] > m) {
            std::cout << i << '\n';
            break;
        }
    }
    return 0;
}