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
    int n, p, s;
    std::cin >> n >> p >> s;
    std::vector<std::pair<int, int>> wj(n);

    for (int i = 0; i < n; ++i) {
        std::cin >> wj[i].first >> wj[i].second;
    }
    std::sort(wj.begin(), wj.end());

    auto check = [&](int m) {
        std::vector<int> dp(s + 1);
        for (auto [w, v]: wj) {
            if (w > m)break;
            for (int j = s; j >= w; --j) {
                dp[j] = std::max(dp[j], dp[j - w] + v);
            }
        }
        return dp[s] >= p;
    };

    int l = 0, r = s, ans = -1;
    while (l <= r) {
        int m = l + r >> 1;
        if (check(m)) {
            r = m - 1;
            ans = m;
        } else l = m + 1;
    }
    if (~ans)std::cout << ans << '\n';
    else std::cout << "No Solution!\n";
    return 0;
}