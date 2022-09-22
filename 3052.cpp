//
// Created by mrx on 2022/8/10.
//
#include <bits/stdc++.h>

using ll = long long;

void solve() {
    int N, W;
    std::cin >> N >> W;
    std::vector<int> v(N);
    for (int i = 0; i < N; ++i) {
        std::cin >> v[i];
    }
    std::vector<int> rem(1 << N);
    std::vector<int> dp(1 << N, 0x3f3f3f3f);
    dp[0] = 0;
    for (int s = 0; s < (1 << N); ++s) {
        for (int j = 0; j < N; ++j) {
            if (s >> j & 1)continue;
            int s0 = s | (1 << j);
            if (v[j] <= rem[s]) {
                if (dp[s0] < dp[s])continue;
                else {
                    if (dp[s0] == dp[s])rem[s0] = std::max(rem[s0], rem[s] - v[j]);
                    else {
                        dp[s0] = dp[s];
                        rem[s0] = rem[s] - v[j];
                    }
                }
            } else {
                if (dp[s0] < dp[s] + 1)continue;
                else {
                    if (dp[s0] == 1 + dp[s])rem[s0] = std::max(rem[s0], W - v[j]);
                    else {
                        dp[s0] = dp[s] + 1;
                        rem[s0] = W - v[j];
                    }
                }
            }
        }
    }
//    for (auto &x: dp)std::cerr << x << ' ';
//    std::cerr << '\n';
//    for (auto &x: rem)std::cerr << x << ' ';

    std::cout << dp[(1 << N) - 1] << '\n';
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