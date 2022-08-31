//
// Created by mrx on 2022/8/12.
//
#include <bits/stdc++.h>

using ll = long long;

void solve() {
    int n, m, k;
    std::cin >> n >> m >> k;
    int cnt = (n * m) / k;
    int rem = n * m - (n * m) / k * k;
    std::vector<std::pair<int, int>> tube[k];
    int cur = 0, tmp = -rem;
    for (int i = 1; i <= n; ++i) {
        if (i & 1) {
            for (int j = 1; j <= m; ++j) {
                tube[cur].emplace_back(i, j);
                tmp++;
                if (tmp == cnt) {
                    cur++;
                    tmp = 0;
                }
            }
        } else {
            for (int j = m; j; --j) {
                tube[cur].emplace_back(i, j);
                tmp++;
                if (tmp == cnt) {
                    cur++;
                    tmp = 0;
                }
            }
        }
    }
    for (int i = 0; i < k; ++i) {
        std::cout << tube[i].size() << ' ';
        for (auto [u, v]: tube[i])std::cout << u << ' ' << v << ' ';
        std::cout << '\n';
    }
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