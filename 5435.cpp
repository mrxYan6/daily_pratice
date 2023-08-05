#include <iostream>
#include <numeric>
#include <vector>
#include <array>
#include <algorithm>
#include <cmath>

const int mod = 998244353;

std::vector<int> minp, primes;
std::vector<std::array<int,3>> factors;
void sieve(int n) {
    minp.resize(n + 1);
    factors.resize(n + 1, {1, 1, 1});
    for (int i = 2; i <= n; ++i) {
        if (!minp[i]) {
            minp[i] = i;
            primes.push_back(i);
            factors[i][2] = i;
        }
        for (auto p: primes) {
            if (p * i > n)break;
            minp[i * p] = p;
            factors[i * p] = factors[i];
            factors[i * p][0] *= p;
            std::sort(factors[i * p].begin(), factors[i * p].end());
            if (p == minp[i]) {
                break;
            }
        }
    }
}
void solve() {
    int n;
    std::cin >> n;
    std::vector<int> a(n), b(n);

    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }
    
    for (int i = 0; i < n; ++i) {
        std::cin >> b[i];
    }

    int v = std::max(*std::max_element(a.begin(), a.end()), *std::max_element(b.begin(), b.end()));
    int vv = std::sqrt(v) + 1;

    sieve(v);

    std::vector<std::vector<int>> gcd(vv + 1, std::vector<int> (vv + 1));
    for (int i = 1; i <= vv; ++i) gcd[i][0] = gcd[0][i] = i;
    for (int i = 1; i <= vv; ++i) {
        for (int j = 1; j <= i; ++j) {
            gcd[i][j] = gcd[j][i] = gcd[i % j][j];
        }
    }

    auto calc = [&] (int x, int y) {
        int g = 1;
        for (int tmp, i = 0; i < 3; ++i) {
            if (factors[x][i] > vv) {
                if (y % factors[x][i] == 0) {
                    tmp = factors[x][i];
                } else tmp = 1;
            } else {
                tmp = gcd[factors[x][i]][y % factors[x][i]];
            }
            y /= tmp;
            g *= tmp;
        }
        return g;
    };

    for (int i = 0; i < n; ++i) {
        int base = 1, ans = 0;
        for (int j = 0; j < n; ++j) {
            base = 1ll * base * (i + 1) % mod;
            ans = (ans + 1ll * base * calc(a[i], b[j])) % mod;
        }
        std::cout << ans << '\n';
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    solve();
    return 0;
}