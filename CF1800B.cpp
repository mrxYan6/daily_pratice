//
// Created by mrx on 2023/3/5.
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
    std::string s;
    std::cin >> s;
    std::map<int, int> cnt;
    i64 ans = 0;
    for (int i = 0; i < n; ++i) {
        //如果s[i]为小写字母则cnt[s[i]]++
        if (s[i] >= 'a' && s[i] <= 'z') {
            if (cnt[s[i] - 'a'] < 0)ans++;
            cnt[s[i] - 'a']++;
        } else {
            if (cnt[s[i] - 'A'] > 0)ans++;
            cnt[s[i] - 'A']--;
        }
    }
    for (auto [x, c]: cnt) {
        ans += std::min(std::abs(c) / 2, k);
        k -= std::min(std::abs(c) / 2, k);
    }
    std::cout << ans << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}