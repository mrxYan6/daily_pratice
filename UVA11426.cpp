//
// Created by mrx on 2022/9/13.
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
    std::vector<ll> prime, vis(1e6 + 100), phi(1e6 + 100);
    phi[0] = 1;
    for (int i = 2; i <= 1e6 + 1; ++i) {
        if (!vis[i]) {
            prime.push_back(i);
            phi[i] = i - 1;
        }
        for (int j = 0; j < prime.size() && i * prime[j] <= 1e6 + 1; ++j) {
            vis[i * prime[j]] = 1;
            if (i % prime[j]) {
                phi[i * prime[j]] = phi[i] * (prime[j] - 1);
            } else {
                phi[i * prime[j]] = phi[i] * prime[j];
                break;
            }
        }
    }

    std::vector<ll> f(1e6 + 100), sum(1e6 + 100);
    for (int i = 1; i <= 1e6 + 1; ++i)
        for (int n = i * 2; n <= 1e6 + 1; n += i) f[n] += phi[n / i] * i;

    sum[2] = f[2];
    for (int i = 3; i <= 1e6 + 1; ++i)sum[i] = sum[i - 1] + f[i];

    int n;
    while (std::cin >> n && n) {
        std::cout << sum[n] << '\n';
    }
    return 0;
}