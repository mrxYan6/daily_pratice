//
// Created by mrx on 2022/6/29.
//
#include<bits/stdc++.h>

const int mod = 998244353;

long long quickpow(long long a, long long b) {
    long long ans = 1;
    while (b) {
        if (b & 1) ans = ans * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return ans;
}

using namespace std;

int main() {
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
#ifdef ONLINE_JUDGE
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
#endif
    int n;
    long long k;
    std::cin >> n >> k;
    std::vector<long long> x(n + 1), y(n + 1);
    for (int i = 1; i <= n; ++i) {
        std::cin >> x[i] >> y[i];
    }

    auto Lagrange = [&](std::vector<long long> &x, std::vector<long long> &y) -> long long {
        long long ans = 0;
        for (int i = 1; i <= n; ++i) {
            long long fz = 1, fm = 1;
            for (int j = 1; j <= n; ++j) {
                if (i == j)continue;
                fz = fz * (k - x[j]) % mod;
                fm = fm * (x[i] - x[j]) % mod;
            }
            ans = (ans + y[i] * fz % mod * quickpow(fm, mod - 2) % mod) % mod;
            ans = (ans + mod) % mod;
        }
        return ans;
    };

    std::cout << Lagrange(x, y) << std::endl;
}
