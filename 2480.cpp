#include <vector>
#include <algorithm>
#include <functional>
#include <iostream>
#include <array>
#include <cmath>
#include <numeric>
using i64 = long long;

std::vector<int> primes, minp;

const int mod = 999911659;

void sieve (int n) {
    minp.resize(n);
    minp[1] = 1;
    for (int i = 2; i < n; ++i) {
        if (minp[i] == 0) {
            minp[i] = i;
            primes.push_back(i);
        }
        for (auto p : primes) {
            if (p * i >= n) break;
            minp[p * i] = p;
            if (minp[i] == p) break;
        }
    }
}

i64 power(i64 a, i64 b, i64 p) {
	i64 ans = 1;
	for (; b; b >>= 1, a = a * a % p)if (b & 1)ans = ans * a % p;
	return ans;
}


std::array<i64, 3> exgcd(i64 a, i64 b) {
	if (!b) {
		return {a, 1, 0};
	}
	auto [g, x, y] = exgcd(b, a % b);
	return {g, y, x - a / b * y};
}

void solve () {
    int n, g;
    std::cin >> n >> g;

    sieve(std::sqrt(mod) + 2);

    std::vector<std::array<int,2>> primf;

    int tmp = n;

    for (auto p : primes) {
        if (p * p > tmp) break;
        if (tmp % p) continue;

        int cnt = 0;
        while (tmp % p == 0) {
            tmp /= p;
            ++cnt;
        }
        primf.push_back({p, cnt});
    } 
    if (tmp > 1) {
        primf.push_back({tmp, 1});
    }

    // for (auto x : primf) {
    //     for (auto y : x) std::cout << y << ' ';
    //     std::cout << '\n';
    // }

    std::vector<int> divs;
    std::function<void(int,int)> dfs =[&] (int cur, int idx) {
        if (idx == primf.size()) {
            divs.push_back(cur);
            return;
        }
        for (int i = 0; i <= primf[idx][1]; ++i) {
            dfs(cur, idx + 1);
            cur *= primf[idx][0];
        }
    };

    dfs(1, 0);

    std::sort(divs.begin(), divs.end(), std::greater<int>());

    auto get_c = [&](int p) {
        std::vector<int> fact(p), inv(p);
        fact[0] = 1, inv[0] = 1;
        for (int i = 1; i < p; ++i) {
            fact[i] = 1ll * fact[i - 1] * i % p;
        }
        inv[p - 1] = power(fact[p - 1], p - 2, p);
        for (int i = p - 2; i >= 1; --i) {
            inv[i] = 1ll * inv[i + 1] * (i + 1) % p;
        }

        auto C = [&](int n, int m) {
            return n < m ? 0ll : 1ll * fact[n] * inv[m] % p * inv[n - m] % p;
        };

        std::function<i64(int, int, int)> lucas = [&] (int i, int j, int p) {
            return j == 0 ? 1ll : 1ll * C(i % p, j % p) * lucas(i / p, j / p, p) % p;
        };

        i64 ret = 0;
        for (auto x : divs) {
            ret = (ret + lucas(n, x, p)) % p;
        }
        return ret;
    };

    std::vector<int> m{2, 3, 4679, 35617};

    std::vector<i64> b{get_c(2), get_c(3), get_c(4679), get_c(35617)};
    // a ^ b % mod  -> a ^ (b % (phi(mod))) % mod
    // g ^ (\sum c (n,d) % (mod - 1)) % mod

    auto EXCRT = [&] (int n) {
        i64 xi, yi, gcd, c;
        i64 LCM = m[0], x0 = b[0];
        for (int i = 1; i < n; ++i) {
            auto [gcd, xi, yi] = exgcd(LCM, m[i]);
            c = b[i] - x0;
            if (c % gcd) return -1ll;
            i64 t = m[i] / gcd;
            xi = (xi * (c / gcd) % t + t) % t;
            x0 += xi * LCM;
            LCM *= m[i] / gcd;
            x0 %= LCM;
        }
        x0 = (x0 + LCM) % LCM;
        if(x0 == 0) x0 = LCM;
        return x0;
    }; 

    std::cout << power(g, EXCRT(4), mod) << '\n';
}

int main () {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    solve();

    return 0;
}
