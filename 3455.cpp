//
// Created by mrx on 2022/9/8.
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

    std::vector<int> prime, vis(1e6 + 10), mu(1e6 + 10);
    mu[1] = 1;
    for (int i = 2; i <= 1e6; ++i) {
        if (!vis[i]) {
            mu[i] = -1;
            prime.push_back(i);
        }
        for (int j = 0; j < prime.size() && i * prime[j] <= 1e6; ++j) {
            vis[i * prime[j]] = 1;
            if (i % prime[j] == 0) {
                mu[i * prime[j]] = 0;
                break;
            } else {
                mu[i * prime[j]] = -mu[i];
            }
        }
    }
    std::vector<int> sum(1e6 + 10, 0);
    for (int i = 1; i <= 1e6; ++i) {
        sum[i] = sum[i - 1] + mu[i];
    }

    int t;
    std::cin >> t;
    while (t--) {
    long long a, b, d;
    std::cin >> a >> b >> d;
    long long ans = 0;
    a /= d, b /= d;
    for (long long l = 1, r; l <= std::min(a, b); l = r + 1) {
        r = std::min(b / (b / l), a / (a / l));
        ans += (a / l) * (b / l) * (sum[r] - sum[l - 1]);

    }
    std::cout << ans << '\n';
    }

    return 0;
}