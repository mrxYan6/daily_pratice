//
// Created by mrx on 2022/9/8.
//
#include <bits/stdc++.h>

using ll = long long;
const int maxn = 5e4;

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
#endif
#ifndef LOCAL
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#endif
    std::vector<long long> prime, vis(maxn + 100), mu(maxn + 100), sum(maxn + 100);
    mu[1] = 1;
    for (int i = 2; i <= maxn; ++i) {
        if (!vis[i]) {
            mu[i] = -1;
            prime.push_back(i);
        }
        for (int j = 0; j < prime.size() && prime[j] * i <= maxn; ++j) {
            vis[prime[j] * i] = 1;
            if (i % prime[j] == 0) {
                mu[prime[j] * i] = 0;
                break;
            } else {
                mu[prime[j] * i] = -mu[i];
            }
        }
    }

    for (int i = 1; i <= maxn; ++i) {
        sum[i] = sum[i - 1] + mu[i];
    }

    int t;
    std::cin >> t;
    while (t--) {
        long long a, b, c, d, k;
        std::cin >> a >> b >> c >> d >> k;

        std::function<long long(long long, long long)> cacal = [&](long long x, long long y) {
            long long ret = 0;
            for (long long l = 1, r; l <= std::min(x, y); l = r + 1) {
                r = std::min(x / (x / l), y / (y / l));
                ret += (sum[r] - sum[l - 1]) * (x / l) * (y / l);
            }
            return ret;
        };

        long long ans = 0;
        ans = cacal(b / k, d / k) - cacal((a - 1) / k, d / k) - cacal(b / k, (c - 1) / k) + cacal((a - 1) / k, (c - 1) / k);
        std::cout << ans << '\n';
    }
    return 0;
}