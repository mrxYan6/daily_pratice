#include <iostream>
#include <vector>
#include <functional>
#include <unordered_map>

using i64 = long long;

i64 power(i64 a, i64 b, i64 m) {
    i64 ret = 1;
    for (; b; b >>= 1, a = a * a % m) {
        if (b & 1) {
            ret = ret * a % m;
        }
    }
    return ret;
}

std::vector<int> minp, phi, primes;

void sieve(int n) {
    minp.resize(n + 1);
    phi.resize(n + 1);

    phi[1] = 1;
    for (int i = 2; i <= n; ++i) {
        if (!minp[i]) {
            minp[i] = i;
            phi[i] = i - 1;
            primes.push_back(i);
        }
        for (auto p : primes) {
            if (i * p > n) {
                break;
            }
            minp[i * p] = p;
            if (minp[i] == p) {
                phi[i * p] = phi[i] * p;
                break;
            }
            phi[i * p] = phi[i] * (p - 1);
        } 
    }
}
int main () {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N = 1e7 + 10;
    sieve(N);

    i64 n, p;
    std::cin >> p >> n;
    
    std::vector<i64> sum(N + 1);
    for (int i = 1; i <= N; ++i) {
        sum[i] = 1ll * phi[i] * i % p * i % p;
    }

    for (int i = 1; i <= N; ++i) {
        sum[i] = (sum[i] + sum[i - 1]) % p;
    }
    
    i64 inv2 = (p + 1) / 2;
    i64 inv6 = power(6, p - 2, p);
    auto f_g_sum = [&] (i64 x) {
        x %= p;
        x = x * (x + 1) % p * inv2 % p;
        return x * x % p;
    };

    auto g_sum = [&] (i64 x) {
        x %= p;
        x = (x + 1) * x % p * (2 * x + 1) % p * inv6 % p;
        return x;
    };

    std::unordered_map<i64, i64> mp;

    std::function<i64(i64)> GetSum = [&] (i64 x) {
        if (x <= 0) return 0ll;
        if (x < N) {
            return sum[x];
        }
        if (mp.count(x)) {
            return mp[x];
        }
        i64 res = f_g_sum(x);
        for (i64 l = 2, r; l <= x; l = r + 1) {
            i64 t = x / l;
            r = x / t;
            res = ((res - ((g_sum(r) - g_sum(l - 1)) % p + p) % p * GetSum(t) % p) % p + p) % p;
        }
        return mp[x] = res;
    };

    i64 ans = 0;
    for (i64 l = 1, r; l <= n; l = r + 1) {
        i64 t = n / l;
        r = n / t;
        i64 tmp = ((GetSum(r) - GetSum(l - 1)) % p + p) % p;
        i64 now = tmp * f_g_sum(t) % p;
        ans = (ans + now) % p;
    }

    std::cout << ans << '\n';

    return 0;
}