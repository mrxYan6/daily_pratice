//
// Created by mrx on 2022/8/3.
//
#include <bits/stdc++.h>

using ll = long long;

struct dsu {
    std::vector<int> f, s;

    dsu(int n) : f(n), s(n, 1) {
        for (int i = 0; i < n; ++i)f[i] = i;
    }

    int find(int x) {
        return x != f[x] ? f[x] = find(f[x]) : x;
    }

    void merge(int a, int b) {
        if (find(a) == find(b))return;
        if (s[find(a)] < s[find(b)]) {
            std::swap(a, b);
        }
        s[f[find(a)]] += s[find(b)];
        s[find(b)] = 0;
        f[find(b)] = find(a);
    }

    int size(int x) {
        return s[find(x)];
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
    int n, m, k;
    std::cin >> n >> m >> k;
    dsu d(n + 1);
    for (int i = 0; i < k; ++i) {
        int u, v;
        std::cin >> u >> v;
        d.merge(u, v);
    }

    std::bitset<40004> dp;
    dp[0] = 1;
    std::vector<int> vis(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        if (vis[d.find(i)])continue;
        vis[d.find(i)] = 1;
        dp |= dp << d.size(i);
    }
    for (int i = 0; i <= std::max(n - m, m); ++i) {
        if (dp[m - i] && m - i >= 0) {
            std::cout << m - i << '\n';
            return 0;
        } else if (dp[m + i] && m + i <= n) {
            std::cout << m + i << '\n';
            return 0;
        }
    }
    return 0;
}