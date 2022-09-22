//
// Created by mrx on 2022/9/11.
//

#include <bits/stdc++.h>

using ll = long long;
const double eps = 1e-8;

template<class T>
T quickPow(T base, ll fact) {
    T ans = 1;
    while (fact) {
        if (fact & 1) ans = ans * base;
        base = base * base;
        fact >>= 1;
    }
    return ans;
}

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
    double l, r;
    std::cin >> n >> l >> r;
    std::vector<double> X(n + 1);
    for (int i = 0; i <= n; ++i)std::cin >> X[i];
    std::reverse(X.begin(), X.end());

    auto f = [&](double x) {
        double ans = 0;
        double base = 1;
        for (int i = 0; i <= n; ++i) {
            ans += X[i] * base;
            base = base * x;
        }
        return ans;
    };

    while (r - l > eps) {
        double lm = (2 * l + r) / 3;
        double rm = (l + 2 * r) / 3;
        if (f(lm) > f(rm)) {
            r = rm;
        } else {
            l = lm;
        }
    }
    std::cout << std::fixed << std::setprecision(12) << l << '\n';

    return 0;
}