//
// Created by mrx on 2022/8/4.
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
    int n, t;
    std::cin >> n >> t;
    std::vector<int> v(n), c(n);
    for (auto &x: v)std::cin >> x;
    for (auto &x: c)std::cin >> x;
    int sum = 0;
    for (int i = 0; i < n; ++i)sum = std::max(sum, v[i] * v[i]);
    sum = sum + t;
    std::vector<int> dp(sum + 1, 0x3f3f3f3f);

    dp[0] = 0;
    for (int i = 0; i < n; ++i) {
        int vv = v[i], cc = c[i];
        int max_cnt = std::min(cc, sum / vv);
        for (int rem = 0; rem < vv; ++rem) {
            std::deque<std::pair<int, int>> q;
            int can_put = std::min(cc, (sum - rem) / vv);
            for (int kk = 0; kk <= can_put; ++kk) {
                while (!q.empty() && q.back().second >= dp[rem + vv * kk] - kk)q.pop_back();
                q.emplace_back(kk, dp[rem + kk * vv] - kk);
                while (!q.empty() && kk - q.front().first > max_cnt)q.pop_front();
                dp[rem + kk * vv] = std::min(dp[rem + kk * vv], q.front().second + kk);
            }
        }
    }

//    for (auto x: dp)std::cerr << x << ' ';
    for (int i = 0; i < n; ++i) {
        int vv = v[i];
        for (int j = sum - vv; j >= t; --j) {
            dp[j] = std::min(dp[j], 1 + dp[j + vv]);
        }
    }
    if (dp[t] == 0x3f3f3f3f)std::cout << -1 << '\n';
    else std::cout << dp[t] << '\n';
    return 0;
}