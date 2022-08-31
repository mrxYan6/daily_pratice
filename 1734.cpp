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
    int s;
    std::cin >> s;
    std::vector<ll> v(s + 1, 0);
    for (int i = 1; i <= s; ++i) {
        for (int j = 1; j < i; ++j) {
            if (i % j == 0)v[i] += j;
        }
    }

    std::vector<ll> dp(s + 1, 0);
    for (int i = 1; i <= s; ++i) {
        for (int j = 0; j <= s - i; ++j) {
            dp[j] = std::max(dp[j], dp[j + i] + v[i]);
        }
    }

    std::cout << *std::max_element(dp.begin(), dp.end()) << '\n';
    return 0;
}