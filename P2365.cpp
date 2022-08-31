//
// Created by mrx on 2022/8/12.
//
#include <bits/stdc++.h>

using ll = long long;

void solve() {
    int n, s;
    std::cin >> n >> s;
    std::vector<ll> dp(n + 1, 0x3f3f3f3f3f3f3f3f);//前i个 mission
    std::vector<std::pair<ll, ll>> job(n), sum(n + 1);
    for (int i = 0; i < n; ++i) {
        std::cin >> job[i].first >> job[i].second;
        sum[i + 1].first = sum[i].first + job[i].first;
        sum[i + 1].second = sum[i].second + job[i].second;
    }
    dp[0] = 0;
    std::deque<int> q;
    auto check = [&](ll k) -> bool {
        int i = q[0];
        int j = q[1];
        return dp[j] - dp[i] <= k * (sum[j].second - sum[i].second);
    };
    auto check_out = [&](int cur) -> bool {
        int n = q.size();
        int i = q[n - 1];
        int j = q[n - 2];
        return (dp[i] - dp[j]) * (sum[cur].second - sum[i].second) >= (dp[cur] - dp[i]) * (sum[i].second - sum[j].second);
    };
    q.push_back(0);
    for (int i = 1; i <= n; ++i) {
        ll k = s + sum[i].first;
        while (q.size() > 1 && check(k))q.pop_front();
        dp[i] = dp[q.front()] - sum[q.front()].second * (s + sum[i].first) + s * sum[n].second + sum[i].first * sum[i].second;
        while (q.size() > 1 && check_out(i))q.pop_back();
        q.push_back(i);
    }
    std::cout << dp[n] << '\n';
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
    solve();
    return 0;
}