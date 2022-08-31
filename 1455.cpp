//
// Created by mrx on 2022/7/31.
//
#include <bits/stdc++.h>

using ll = long long;

struct dsu {
    std::vector<int> f;

    dsu(int n = 0) {
        f.resize(n + 1);
        for (int i = 0; i <= n; ++i)f[i] = i;
    }

    int find(int x) {
        return x != f[x] ? f[x] = find(f[x]) : x;
    }

    void merge(int a, int b) {
        if (find(a) != find(b)) f[find(a)] = find(b);
    }
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
    int n, m, mo;
    std::cin >> n >> m >> mo;
    dsu a(n);
    std::vector<std::pair<int, int>> p(n + 1);
    for (int i = 1; i <= n; ++i) {
        std::cin >> p[i].first >> p[i].second;
    }

    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        a.merge(u, v);
    }

    for (int i = 1; i <= n; ++i) {
        if (a.find(i) == i)continue;
        p[a.find(i)].first += p[i].first;
        p[a.find(i)].second += p[i].second;
        p[i].first = p[i].second = 0;
    }

    std::vector<int> dp(mo + 1, 0);
    for (auto [w, v]: p) {
        if (w == 0 && v == 0)continue;
        for (int j = mo; j >= w; --j) {
            dp[j] = std::max(dp[j], dp[j - w] + v);
        }
    }
    std::cout << dp[mo] << '\n';
    return 0;
}