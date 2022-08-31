//
// Created by mrx on 2022/6/29.
//
#include <bits/stdc++.h>

#define ll long long
#define endl '\n'
const long long mod = 1e9 + 7;

long long quickpow(long long a, long long b) {
    long long ans = 1;
    while (b) {
        if (b & 1)ans = ans * a % mod;
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
//#ifdef ONLINE_JUDGE
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
//#endif
    std::vector<long long> fact(1e6 + 100), invfact(1e6 + 100), y(1e6 + 100);
    fact[0] = invfact[0] = 1;
    for (int i = 1; i <= 1e6 + 20; ++i) {
        fact[i] = fact[i - 1] * i % mod;
        invfact[i] = quickpow(fact[i], mod - 2);
    }
    int n, k;
    std::cin >> n >> k;
    long long fz = 1;
    for (int i = 1; i <= k + 2; ++i) {
        fz = fz * (n - i) % mod;
    }
    for (int i = 1; i <= k + 2; ++i) {
        y[i] = y[i - 1] + quickpow(i, k);
        y[i] %= mod;
    }
    if (n <= k + 2) {
        std::cout << y[n] << endl;
        return 0;
    }

    long long ans = 0;
    for (int i = 1; i <= k + 2; ++i) {
        long long fm = y[i] * invfact[i - 1] % mod * invfact[k - i + 2] % mod;
        long long sign = (k - i) & 1 ? -1 : 1;
        ans = (ans + mod + fz * quickpow(n - i, mod - 2) % mod * fm % mod * sign % mod) % mod;
    }
    std::cout << ans << endl;
    return 0;
}