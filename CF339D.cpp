//
// Created by mrx on 2023/2/20.
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
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<int>> a(n + 1);

    for (int i = 0; i <= n; ++i) {
        a[i].resize(1 << (n - i));
    }

    for (int i = 0; i < 1 << n; ++i) {
        std::cin >> a[0][i];
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < 1 << (n - i); j += 2) {
            a[i + 1][j / 2] = i & 1 ? a[i][j] ^ a[i][j + 1] : a[i][j] | a[i][j + 1];
        }
    }

    while (m--) {
        int p, b;
        std::cin >> p >> b;
        p--;
        int cur = b;
        for (int i = 0; i <= n; ++i) {
            a[i][p] = cur;
            if (i < n) cur = i & 1 ? a[i][p] ^ a[i][p ^ 1] : a[i][p] | a[i][p ^ 1];
            p >>= 1;
        }
        std::cout << a[n][0] << "\n";
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    solve();

    return 0;
}