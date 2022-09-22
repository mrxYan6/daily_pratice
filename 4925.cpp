//
// Created by mrx on 2022/6/28.
//

#include <bits/stdc++.h>

#define ll long long
#define endl '\n'
using namespace std;
long long mod;

long long quickpow(long long a, long long b) {
    long long ans = 1;
    while (b) {
        if (b & 1)ans = ans * a % mod;
        a = a * a % mod;
        b >>= 1;
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
    long long k, l;
    cin >> k >> l >> mod;
    long long s, w;
    cin >> s >> w;
    k %= mod;
    if (l == 1) {
        if (s)cout << 1 << endl;
        else cout << k << endl;
    } else {
        long long ans;
        if (s) {
            ans = k - 1;
        } else ans = k * (k - 1) % mod;
        ans = ans * quickpow(k - 2, l - 2) % mod;
        cout << ans << endl;
    }
    return 0;
}