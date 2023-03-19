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
    int n, k;
    std::cin >> n >> k;
    std::string s, t;
    std::cin >> s >> t;
    std::map<char, int> cnt;
    for (int i = 0; i < n; ++i) {
        if (i + k >= n && i - k < 0) {
            if (s[i] != t[i]) {
                std::cout << "NO\n";
                return;
            }
        } else {
            cnt[s[i]]++;
            cnt[t[i]]--;
        }
    }
    for (auto [c, v]: cnt) {
        if (v != 0) {
            std::cout << "NO\n";
            return;
        }
    }
    std::cout << "YES\n";
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