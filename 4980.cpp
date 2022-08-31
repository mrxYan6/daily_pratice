//
// Created by mrx on 2022/7/1.
//
#include <bits/stdc++.h>

#define ll long long
#define endl '\n'
using namespace std;
const long long mod = 1e9 + 7;

long long phi(long long x) {
    long long res = x, m;
    m = sqrt(x + 0.5);
    for (long long i = 2; i <= m; ++i) {
        if (x % i == 0) {
            x /= i;
            res -= res / i;
            while (x % i == 0)x /= i;
        }
    }
    if (x > 1)res -= res / x;
    return res;
}

ll quickPow(ll base, ll fact) {
    ll ans = 1;
    while (fact) {
        if (fact & 1) ans = ans * base % mod;
        base = base * base % mod;
        fact >>= 1;
    }
    return ans;
}

void sol() {
    long long n;
    cin >> n;
    long long ans = 0;
    for (int i = 1; i * i <= n; ++i) {
        if (n % i == 0) {
            ans = (ans + phi(i) * quickPow(n, n / i) % mod) % mod;
            if (i * i != n) {
                ans = (ans + phi(n / i) * quickPow(n, i) % mod) % mod;
            }
        }
    }
    ans = ans * quickPow(n, mod - 2) % mod;
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
    int t;
    cin >> t;
    while (t--)sol();
    return 0;
}