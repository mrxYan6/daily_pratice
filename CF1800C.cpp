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

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    std::priority_queue<int> q;
    i64 ans = 0;
    for (int i = 0; i < n; ++i) {
        int x;
        std::cin >> x;
        if (x > 0) {
            q.push(x);
        } else {
            if (!q.empty()) {
                auto add = q.top();
                q.pop();
                ans += add;
            }
        }
    }
    std::cout << ans << '\n';
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