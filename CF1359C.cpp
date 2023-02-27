//
// Created by mrx on 2023/2/24.
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
    i64 c, t, h;

    std::cin >> h >> c >> t;
    if (t * 2 <= h + c) {
        std::cout << 2 << "\n";
    } else {
        i64 a = (t - c) / (2 * t - h - c);
        if ((2 * a + 1) * (a * h + (a - 1) * c - t * (2 * a - 1)) > (t * (2 * a + 1) - ((a + 1) * h + a * c)) * (2 * a - 1))a++;
        std::cout << a * 2 - 1 << '\n';
    }
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