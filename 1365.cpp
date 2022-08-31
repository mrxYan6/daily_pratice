//
// Created by mrx on 2022/8/15.
//
#include <bits/stdc++.h>

using ll = long long;

int main() {
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
#ifdef ONLINE_JUDGE
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#endif
    int n;
    std::cin >> n;
    std::string s;
    std::cin >> s;
    long double len = 0;
    long double ans = 0;
    for (int i = 0; i < n; ++i) {
        if (s[i] == 'o') {
            ans += len * 2 + 1;
            len++;
        } else if (s[i] == '?') {
            ans += (2 * len + 1) / 2;
            len++;
            len /= 2;
        } else {
            len = 0;
        }
    }
    std::cout << std::fixed << std::setprecision(4) << ans << '\n';
    return 0;
}