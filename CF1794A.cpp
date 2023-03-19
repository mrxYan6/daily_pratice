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
    std::vector<std::string> strs(2 * n - 2);
    for (int i = 0; i < 2 * n - 2; ++i)std::cin >> strs[i];
    std::sort(strs.begin(), strs.end(), [&](auto& a, auto& b) {
        return a.length() < b.length();
    });
    auto pref = strs[2 * n - 3], suf = strs[2 * n - 4];
//    std::cerr << suf.substr(0, n - 2) << '\n';
    if (suf.substr(0, n - 2) != pref.substr(1)) {
        std::swap(pref, suf);
    }
//    std::cout << pref << ' ' << suf << '\n';
    pref += suf.back();
    auto rev = pref;
    std::reverse(rev.begin(), rev.end());
    if (rev == pref)std::cout << "YES\n";
    else std::cout << "NO\n";
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