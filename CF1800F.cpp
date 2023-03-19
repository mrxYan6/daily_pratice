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

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    std::vector<std::string> s(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> s[i];
    }

    std::vector vis(n, std::vector(26, 0));
    std::vector mask(n, 0);
    for (int i = 0; i < n; ++i) {
        for (char c: s[i]) {
            vis[i][c - 'a']++;
        }
        for (int j = 0; j < 26; ++j) {
            if (vis[i][j] & 1) {
                mask[i] |= (1 << j);
            }
        }
    }
    std::vector<int> cnt(1 << 26, 0);
    i64 ans = 0;
    for (int i = 0; i < 26; ++i) {
        for (int j = 0; j < n; ++j) {
            if (vis[j][i])continue;
            ans += cnt[mask[j] ^ ((1 << 26) - 1) ^ (1 << i)];
            cnt[mask[j]]++;
        }
        for (int j = 0; j < n; ++j) {
            if (vis[j][i])continue;
            cnt[mask[j]]--;
        }
    }
    std::cout << ans << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int t;
    t = 1;
//    std::cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}