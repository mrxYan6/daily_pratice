//
// Created by mrx on 2023/3/10.
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
#include <random>

using i64 = long long;
using ui64 = unsigned long long;
std::random_device rd;
std::mt19937_64 gen(rd());

void solve() {
    int n;
    std::cin >> n;

    std::vector adj(n, std::vector<int>());
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        std::cin >> u >> v;
        --u, --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    auto seed = gen();
    std::vector hash(n, seed);
    //重构代码
    std::function<void(int, int)> dfs = [&](int u, int p) {
        for (auto v: adj[u]) {
            if (v == p) continue;
            hash[v] = hash[u] ^ seed;
            dfs(v, u);
        }
    };
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}