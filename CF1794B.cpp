//
// Created by mrx on 2023/3/7.
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
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i)std::cin >> a[i];
    for (int i = 0; i < n; ++i) {
        while (a[i] < 2)a[i]++;
    }
    for (int i = 1; i < n; ++i) {
        while (a[i] % a[i - 1] == 0)a[i]++;
    }
    for (auto x: a)std::cout << x << ' ';
    std::cout << '\n';
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