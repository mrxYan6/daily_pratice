//
// Created by mrx on 2022/6/2.
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
    int n, m;
    std::cin >> n >> m;
    std::vector<int> cnt(4e6, 0), sum(4e6, 0);
    int maxt = 0;
    for (int i = 0; i < n; ++i) {
        int x;
        std::cin >> x;
        maxt = std::max(maxt, x);
        cnt[x]++;
        sum[x] += x;
    }
    for (int i = 1; i <= maxt + m; ++i) {
        sum[i] += sum[i - 1];
        cnt[i] += cnt[i - 1];
    }


    std::vector<int> dp(maxt + m + 1);
    dp[0] = 0;
    std::deque<int> q;
    for (int i = 0; i < maxt + m; ++i) {
        if (i >= m) {
            while (q.size() > 1 && (dp[i - m] - dp[q[q.size() - 1]] + sum[i - m] - sum[q[q.size() - 1]]) * (cnt[q[q.size() - 1]] - cnt[q[q.size() - 2]]) <=
                                   (dp[q[q.size() - 1]] - dp[q[q.size() - 2]] + sum[q[q.size() - 1]] - sum[q[q.size() - 2]]) * (cnt[i - m] - cnt[q[q.size() - 1]]))
                q.pop_back();
            q.push_back(i - m);
        }
        while (q.size() > 1 && (dp[q[1]] - dp[q[0]] + sum[q[1]] - sum[q[0]]) <= i * (cnt[q[1]] - cnt[q[0]]))q.pop_front();
        dp[i] = i * cnt[i] - sum[i];
        if (q.size())dp[i] = std::min(dp[i], dp[q.front()] + i * (cnt[i] - cnt[q.front()]) - sum[i] + sum[q.front()]);
    }
    int ans = 1e9;
//    for (int i = 1; i <= maxt + m; ++i)std::cerr << dp[i] << ' ';
//    std::cerr << '\n';
    for (int i = maxt; i < maxt + m; ++i)ans = std::min(ans, dp[i]);
    std::cout << ans << '\n';
    return 0;
}