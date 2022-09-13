//
// Created by mrx on 2022/9/11.
//
#include <bits/stdc++.h>

using ll = long long;
const double eps = 1e-10;

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
#endif
#ifndef LOCAL
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#endif
    int t;
    std::cin >> t;
    while (t--) {
        int n;
        std::cin >> n;
        std::vector<std::array<double, 3>> f(n);
        for (int i = 0; i < n; ++i)for (int j = 0; j < 3; ++j)std::cin >> f[i][j];
        auto cacal = [&](double x) {
            double ans = -1e9;
            for (int i = 0; i < n; ++i) {
                ans = std::max(ans, x * x * f[i][0] + x * f[i][1] + f[i][2]);
            }
            return ans;
        };

        double l = 0, r = 1000;
        while (r - l > eps) {
            double lm = (2 * l + r) / 3;
            double rm = (l + 2 * r) / 3;
            if (cacal(lm) > cacal(rm)) {
                l = lm;
            } else {
                r = rm;
            }
        }
        std::cout << std::fixed << std::setprecision(4) << cacal(l) << '\n';
    }
    return 0;
}