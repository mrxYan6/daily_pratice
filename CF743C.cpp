//
// Created by mrx on 2022/8/12.
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
    std::vector<std::pair<int, int>> p;
    for (int i = 0; i < n; ++i) {
        ll x, len;
        std::cin >> x >> len;
        p.emplace_back(x - len, x + len);
    }
    std::sort(p.begin(), p.end(), [&](const auto &x1, const auto &x2) {
        return x1.second < x2.second;
    });
    int cur = -1e9;
    int cnt = 0;
    for (auto [l, r]: p) {
        if (l >= cur) {
            cnt++;
            cur = r;
        }
    }
    std::cout << cnt << '\n';
    return 0;
}