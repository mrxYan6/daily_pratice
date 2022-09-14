//
// Created by mrx on 2022/9/14.
//
#include <bits/stdc++.h>

using ll = long long;

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
#endif
#ifndef LOCAL
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#endif
    int n;
    while (std::cin >> n) {
        std::vector<ll> c(n);
        for (int i = 0; i < n; ++i) {
            std::cin >> c[i];
            if (i) c[i] += c[i - 1];
        }
        ll ave = c[n - 1] / n;
        for (int i = 0; i < n; ++i) {
            c[i] = (i + 1) * ave - c[i];
        }

        std::nth_element(c.begin(), c.begin() + n / 2, c.end());
        ll x1 = c[n / 2];
        ll ans = 0;
        for (int i = 0; i < n; ++i) {
            ans += std::abs(c[i] - x1);
        }
        std::cout << ans << '\n';
    }
    return 0;
}