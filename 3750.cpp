//
// Created by mrx on 2022/7/10.
//
#include <bits/stdc++.h>

#define ll long long
#define endl '\n'
using namespace std;
const long long mod = 100003;

ll quickPow(ll base, ll fact) {
    ll ans = 1;
    while (fact) {
        if (fact & 1) ans = ans * base % mod;
        base = base * base % mod;
        fact >>= 1;
    }
    return ans;
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
    long long n, k;
    cin >> n >> k;
    long long cnt = 0;
    vector<long long> a(n + 1);
    for (long long i = 1; i <= n; ++i)cin >> a[i];
    for (long long i = n; i; --i) {
        if (a[i]) {
            cnt++;
            for (long long j = 1; j * j <= i; ++j) {
                if (i % j == 0) {
                    if (j * j != i) {
                        a[j] ^= 1, a[i / j] ^= 1;
                    } else {
                        a[j] ^= 1;
                    }
                }
            }
        }
    }
    vector<long long> dp(n + 2, 0);
    dp[n + 1] = 0;
    for (long long i = n; i; --i) {
        dp[i] = (n + (n - i) * (dp[i + 1]) % mod) % mod * quickPow(i, mod - 2) % mod;
    }
    long long ans = 0;
    if (k >= cnt) {
        ans = cnt;
    } else {
        for (int i = cnt; i > k; --i)ans = (ans + dp[i]) % mod;
        ans = (ans + k) % mod;
    }
    for (int i = 1; i <= n; ++i)ans = ans * i % mod;
    cout << ans << endl;
    return 0;
}