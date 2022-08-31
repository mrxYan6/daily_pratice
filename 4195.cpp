//
// Created by meiru on 2022/8/22.
//

#include <bits/stdc++.h>

using ll = long long;

ll quick_power(ll base, ll fact, ll mod) {
    ll ans = 1;
    while (fact) {
        if (fact & 1) ans = ans * base % mod;
        base = base * base % mod;
        fact >>= 1;
    }
    return ans;
}


ll exgcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) {
        x = 1, y = 0;
        return a;
    }
    ll d = exgcd(b, a % b, x, y);
    ll t = x;
    x = y;
    y = t - a / b * x;
    return d;
}

ll bsgs(ll a, ll b, ll p) {
    std::unordered_map<ll, ll> mp;
    ll m = ceil(sqrt(p));
    b %= p;
    for (int i = 1; i <= m; i++) {
        b = a * b % p;
        mp[b] = i;
    }
    ll tmp = quick_power(a, m, p);
    b = 1;
    for (int i = 1; i <= m; i++) {
        b = b * tmp % p;
        if (mp[b])return (i * m - mp[b] + p) % p;
    }
    return -1;
}

ll inv(ll a, ll b) {
    ll x, y;
    exgcd(a, b, x, y);
    return (x % b + b) % b;
}

ll ex_bsgs(ll a, ll b, ll p) {
    if (b == 1 || p == 1)return 0;
    ll g = std::__gcd(a, p), k = 0, na = 1;
    while (g > 1) {
        if (b % g != 0)return -1;
        k++, b /= g, p /= g, na = na * (a / g) % p;
        if (na == b)return k;
        g = std::__gcd(a, p);
    }
    ll f = bsgs(a, b * inv(na, p) % p, p);
    if (f == -1)return -1;
    return f + k;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
#ifdef ONLINE_JUDGE
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#endif
    ll a, b, p;
    while (std::cin >> a >> p >> b && a + b + p) {
        a %= p, b %= p;
        ll ans = ex_bsgs(a, b, p);
        if (ans == -1)std::cout << "No Solution\n";
        else std::cout << ans << '\n';
    }
    return 0;
}