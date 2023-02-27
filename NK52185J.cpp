//
// Created by mrx on 2023/2/27.
//
#include <functional>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
#include <cmath>
#include <queue>
#include <array>
#include <map>

using i64 = long long;

void solve() {
    int n;

    std::cin >> n;
    std::vector adj(n, std::vector<int>());
    for (int i = 1; i < n; ++i) {
        int u, v;
        std::cin >> u >> v;
        u--, v--;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    std::vector<std::vector<int>> cl(2);
    std::vector<int> color(n);
    std::function<void(int, int, int)> dfs = [&](int u, int p, int c) {
        cl[c].emplace_back(u);
        color[u] = c;
        for (auto x: adj[u]) {
            if (x == p)continue;
            dfs(x, u, c ^ 1);
        }
    };
    dfs(0, 0, 0);
    if (cl[0].size() > cl[1].size())std::swap(cl[0], cl[1]);
    std::vector<i64> ans(n, (1ll << 60) - (1ll << cl[0].size()));
    std::vector<int> pos(n, -1);
    for (int i = 0; i < cl[0].size(); ++i)pos[cl[0][i]] = i;
    for (auto x: cl[0])ans[x] ^= 1ll << 59, ans[x] ^= ((1ll << cl[0].size()) - 1) ^ 1ll << pos[x];
    for (auto x: cl[1])ans[x] ^= 1ll << 58;
    for (auto x: cl[1])for (auto v: adj[x])ans[x] ^= 1ll << pos[v];

//    for (int i = 0; i < n; ++i) {
//        for (int j = i + 1; j < n; ++j) {
//            if ((ans[i] | ans[j]) == (1ll << 60) - 1)std::cout << i + 1 << ' ' << j + 1 << '\n';
//        }
//    }
    for (auto x: ans)std::cout << x << ' ';
}


int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    solve();
    return 0;
}