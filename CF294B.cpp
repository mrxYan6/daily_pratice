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
    std::cin >> n;
    std::vector<std::pair<int, int>> book(n);
    int sum = 0;
    for (int i = 0; i < n; ++i) {
        std::cin >> book[i].first >> book[i].second;
        sum += book[i].first;
    }

    std::vector<ll> dp(sum + 1, 0x3f3f3f3f);
    dp[0] = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = sum; j >= book[i].first; --j) {
            dp[j] = std::min(dp[j - book[i].first] + book[i].second, dp[j]);
        }
    }
    for (int i = sum; i >= 0; --i) {
        if (sum - i >= dp[i]) {
            std::cout << sum - i << '\n';
            break;
        }
    }
    return 0;
}