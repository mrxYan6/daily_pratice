//
// Created by mrx on 2023/2/28.
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
#include <cassert>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (auto& x: a)std::cin >> x;
    int cnt1 = std::count(a.begin(), a.end(), 1);
    if (cnt1 != 0 && cnt1 != n) {
        std::cout << "-1\n";
        return;
    } else {
        int mx = std::max_element(a.begin(), a.end()) - a.begin(), mn = std::min_element(a.begin(), a.end()) - a.begin();
        std::vector<std::pair<int, int>> ans;
        while (a[mx] != a[mn]) {
            int nxt = mn;
            mx = mn;
            for (int i = 0; i < n; ++i) {
                if (a[i] == a[mn])continue;
                a[i] = (a[i] + a[mn] - 1) / a[mn];
//                assert(ans.size() < 30 * n);
                ans.emplace_back(i, mn);
                if (a[i] > a[mx]) mx = i;
                if (a[i] < a[nxt]) nxt = i;
            }
            assert(a[nxt] == *std::min_element(a.begin(), a.end()));
            mn = nxt;
        }
//        assert(ans.size() < 30 * n);
        std::cout << ans.size() << '\n';
        for (auto [x, y]: ans)std::cout << x + 1 << ' ' << y + 1 << '\n';
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