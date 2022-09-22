//
// Created by mrx on 2022/9/3.
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

    long long n;
    std::cin >> n;
    long long nn = n;
    long long ans = 1;
    for (long long i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            nn /= i;
            int t = 0;
            while (n % i == 0)++t, n /= i;
            ans = ans * (t * (i - 1) + i);
        }
    }
    if (n != 1)nn /= n, ans = ans * (2 * n - 1);
    std::cout << ans * nn << '\n';
    return 0;
}