//
// Created by mrx on 2023/3/9.
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

struct Hash {
    static constexpr int P1 = 1000000829;
    static constexpr int P2 = 1000000579;
    i64 x, y;

    Hash(i64 x, i64 y) : x(x % P1), y(y % P2) {}

    Hash(i64 x = 0) : x(x % P1), y(x % P2) {}

    Hash& operator +=(const Hash& rhs) {
        x = (x + rhs.x) % P1, y = (y + rhs.y) % P2;
        return *this;
    }

    Hash& operator -=(const Hash& rhs) {
        x = (x - rhs.x + P1) % P1, y = (y - rhs.y + P2) % P2;
        return *this;
    }

    Hash& operator *=(const Hash& rhs) {
        x = x * rhs.x % P1, y = y * rhs.y % P2;
        return *this;
    }

    friend Hash operator +(const Hash& lhs, const Hash& rhs) {
        Hash res = lhs;
        return res += rhs;
    }

    friend Hash operator -(const Hash& lhs, const Hash& rhs) {
        Hash res = lhs;
        return res -= rhs;
    }

    friend Hash operator *(const Hash& lhs, const Hash& rhs) {
        Hash res = lhs;
        return res *= rhs;
    }

    friend bool operator ==(const Hash& lhs, const Hash& rhs) {
        return lhs.x == rhs.x && lhs.y == rhs.y;
    }

    friend bool operator <(const Hash& lhs, const Hash& rhs) {
        return lhs.x == rhs.x ? lhs.y < rhs.y : lhs.x < rhs.x;
    }
};

void solve() {
    int n;
    std::cin >> n;

    std::random_device dv;
    std::mt19937_64 rng(dv());
    i64 base = rng() % 19260 + 817 + n;

    std::vector<Hash> base_exp(n + 1);
    base_exp[0] = {1, 1};
    for (int i = 1; i <= n; i++) {
        base_exp[i] = base_exp[i - 1] * base;
    }

    Hash sum = Hash();
    for (int i = 0; i < n - 1; i++) {
        int x;
        std::cin >> x;
        sum += base_exp[x];
    }

    std::vector adj(n, std::vector<int>());
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        std::cin >> u >> v;
        u--, v--;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    std::vector<Hash> possibility(n + 1);
    for (int i = 0; i <= n; i++) {
        possibility[i] = sum + base_exp[i];
    }

    std::sort(possibility.begin(), possibility.end());

    std::vector<Hash> dp(n, {1, 1});
    std::function<void(int, int)> dfs1 = [&](int x, int p) -> void {
        for (auto y: adj[x]) {
            if (y != p) {
                dfs1(y, x);
                dp[x] = dp[x] + dp[y] * base;
            }
        }
    };

    std::vector<bool> good(n, false);
    std::function<void(int, int)> dfs2 = [&](int x, int p) -> void {
        good[x] = std::binary_search(possibility.begin(), possibility.end(), dp[x]);
        for (auto y: adj[x]) {
            if (y != p) {
                Hash tmp = dp[x] - dp[y] * base;
                dp[y] = dp[y] + tmp * base;
                dfs2(y, x);
            }
        }
    };

    dfs1(0, 0);
    dfs2(0, 0);

    std::cout << std::count(good.begin(), good.end(), true) << '\n';

    for (int i = 0; i < n; i++) {
        if (good[i]) {
            std::cout << i + 1 << ' ';
        }
    }

    std::cout << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    solve();
    
    return 0;
}