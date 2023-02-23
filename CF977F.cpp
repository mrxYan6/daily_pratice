//
// Created by mrx on 2023/2/23.
//
#include <functional>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
#include <cmath>
#include <queue>
#include <array>
#include <map>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    std::vector<int> dp(n), prev(n);
    std::map<int, int> mp;
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    std::iota(prev.begin(), prev.end(), 0);
    for (int i = 0; i < n; ++i) {
        mp[a[i]] = i;
        if (mp.count(a[i] - 1)) {
            if (dp[i] < dp[mp[a[i] - 1]] + 1) {
                dp[i] = dp[mp[a[i] - 1]] + 1;
                prev[i] = mp[a[i] - 1];
            }
        } else dp[i] = 1;
    }
    int ans = 0, id = 0;
    for (int i = 0; i < n; ++i) {
        if (ans <= dp[i])ans = dp[i], id = i;
    }
    std::vector<int> res;
    while (prev[id] != id) {
        res.push_back(id + 1);
        id = prev[id];
    }
    res.push_back(id + 1);

    std::reverse(res.begin(), res.end());
    std::cout << ans << '\n';
    for (auto x: res)std::cout << x << ' ';
    std::cout << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    solve();

    return 0;
}