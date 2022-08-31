//
// Created by mrx on 2022/8/3.
//
#include <bits/stdc++.h>

using ll = long long;

void sol() {
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (auto &x: a)std::cin >> x;
    std::sort(a.begin(), a.end());

    std::vector<int> dp(a.back() + 1, 0x3f3f3f3f);
    dp[0] = 0;
    int cnt = 0;
    for (int i = 0; i < n; ++i) {
        if (dp[a[i]] == 0x3f3f3f3f)cnt++;
        else continue;
        for (int j = 0; j <= dp.size() - a[i]- 1; ++j) {
            dp[j + a[i]] = std::min(dp[j + a[i]], dp[j]);
        }
    }
    std::cout << cnt << '\n';
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
    while (t--)sol();
    return 0;
}