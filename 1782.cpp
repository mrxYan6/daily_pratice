//
// Created by mrx on 2022/8/3.
//
#include <bits/stdc++.h>

using ll = long long;

struct nod {
    int w, v, c;

    nod() {}

    nod(int w, int v, int c) : w(w), v(v), c(c) {}
};

int main() {
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
#ifdef ONLINE_JUDGE
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#endif
    int n, m, C;
    std::cin >> n >> m >> C;


    std::vector<ll> dp(C + 1, 0);
    for (int i = 0; i < n; ++i) {
        int v, w, d;
        std::cin >> v >> w >> d;

        int max_cnt = std::min(d, C / v);
        for (int rem = 0; rem < v; ++rem) {
            std::deque<std::pair<ll, ll>> q;
            int can_put = (C - rem) / v;
            for (int x = 0; x <= can_put; ++x) {
                while (!q.empty() && dp[rem + x * v] - x * w >= q.back().second)q.pop_back();
                q.emplace_back(x, dp[rem + x * v] - x * w);
                while (!q.empty() && x - q.front().first > max_cnt)q.pop_front();
                dp[rem + x * v] = std::max(dp[rem + x * v], q.front().second + x * w);
            }
        }
    }

    for (int i = 0; i < m; ++i) {
        ll a, b, c;
        std::cin >> a >> b >> c;
        for (int j = C; j >= 0; --j) {
            for (int k = 0; k <= j; ++k) {
                dp[j] = std::max(dp[j], dp[j - k] + a * k * k + b * k + c);
            }
        }
    }
    std::cout << *std::max_element(dp.begin(), dp.end()) << '\n';
    return 0;
}