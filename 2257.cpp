#include <iostream>
#include <vector>
using i64 = long long;
std::vector<int> minp, mu, primes;

void sieve(int n) {
    minp.resize(n + 1);
    mu.resize(n + 1);

    mu[1] = 1;
    for (int i = 2; i <= n; ++i) {
        if (!minp[i]) {
            minp[i] = i;
            mu[i] = -1;
            primes.push_back(i);
        }
        for (auto p : primes) {
            if (i * p >= n) {
                break;
            }
            minp[i * p] = p;
            if (minp[i] == p) {
                break;
            }
            mu[i * p] = -mu[i];
        } 
    }
}


int main () {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N = 1e7 + 10;
    sieve(N);
    

    std::vector<i64> sum(N + 1);
    for (auto p : primes) {
        for (int i = 1; i * p <= N; ++i) {
            sum[i * p] += mu[i];
        }
    }

    for (int i = 1; i <= N; ++i) {
        sum[i] += sum[i - 1];
    }

    int t;
    std::cin >> t;
    while (t--) {
        int n, m;
        std::cin >> n >> m;
        if (n >= m) std::swap(n, m);
        
        i64 ans = 0;
        for (int l = 1, r; l <= n; l = r + 1) {
            r = std::min(n / (n / l), m / (m / l));
            // std::cout << (n / l) * (m / l) * (sum[r] - sum[l - 1]) << '\n';
            ans += 1ll * (n / l) * (m / l) * (sum[r] - sum[l - 1]);
        }
        std::cout << ans << '\n';
    }

    return 0;
}