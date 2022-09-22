//
// Created by mrx on 2022/6/29.
//
#include <bits/stdc++.h>

#define ll long long
#define endl '\n'
using namespace std;
const long long mod = 1e9 + 7;
vector<long long> fact(100), invfact(100);

long long quickpow(long long a, long long b) {
    long long ans = 1;
    while (b) {
        if (b & 1)ans = a * ans % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return ans;
}

long long Lagrange(std::vector<long long> &y, long long x, long long k) {
    long long ans = 0;
    long long fz = 1;
    if (x <= k)return y[x];
    for (int i = 1; i <= k; ++i) {
        fz = fz * (x - i) % mod;
    }
    for (int i = 1; i <= k; ++i) {
        long long inv1 = quickpow(x - i, mod - 2);
        long long inv2 = invfact[i - 1] * invfact[k - i] % mod;
        long long sign = (k - i) & 1 ? -1 : 1;
        ans += sign * inv1 % mod * inv2 % mod * y[i] % mod * fz % mod;
        ans = (ans % mod + mod) % mod;
    }
    return ans;
}

void sol() {
    int n, m;
    cin >> n >> m;
    vector<int> hole(m + 1, 0);
    for (int i = 1; i <= m; ++i) {
        cin >> hole[i];
    }
    std::sort(hole.begin() + 1, hole.end());
    vector<long long> y(m + 4);
    for (int i = 1; i <= m + 3; ++i) {
        y[i] = y[i - 1] + quickpow(i, m + 1);
        y[i] %= mod;
    }
    long long ans = 0;
    for (int i = 0; i <= m; ++i) {
        ans = (ans + Lagrange(y, n - hole[i], m + 3)) % mod;
        for (int j = i + 1; j <= m; ++j) {
            ans = (ans + mod - quickpow(hole[j] - hole[i], m + 1)) % mod;
        }
    }
    cout << ans << endl;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
#ifdef ONLINE_JUDGE
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
#endif
    fact[0] = invfact[0] = 1;
    for (int i = 1; i <= 60; ++i) {
        fact[i] = fact[i - 1] * i % mod;
        invfact[i] = quickpow(fact[i], mod - 2);
    }
    int t;
    cin >> t;
    while (t--)sol();
    return 0;
}