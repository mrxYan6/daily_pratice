//
// Created by mrx on 2022/6/3.
//


#include <bits/stdc++.h>

#define ll long long
#define endl '\n'
using namespace std;
const int N = 1e5 + 100;
long long X;
long long a[N], b[N], m[N], sab[N];

ll exgcd(ll aa, long long bb, ll &x, ll &y) {
    if (bb == 0) {
        x = 1, y = 0;
        return aa;
    }
    ll d = exgcd(bb, aa % bb, x, y);
    ll t = x;
    x = y;
    y = t - aa / bb * x;
    return d;
}

long long slowMul(ll x, ll p, ll mod) {
    ll ans = 0;
    if (mod == 0)exit(4);

    while (p) {
        if (p & 1)ans = (ans + x) % mod;
        x = (x + x) % mod;
        p >>= 1;
    }
    return ans;
}

long long LCM;
long long maxn = 0;

long long EXCRT(int n) {
    long long c, xi, yi, gcd, t;
    LCM = 1, X = 0;
    for (int i = 0; i < n; ++i) {
        if (m[i] == 0)exit(1);


        c = (a[i] - slowMul(X, b[i], m[i]) + m[i]) % m[i];
        gcd = exgcd(slowMul(b[i], LCM, m[i]), m[i], xi, yi);
        xi = (xi % m[i] + m[i]) % m[i];
        if (gcd == 0)exit(2);
        if (c % gcd)return -1;
        t = LCM;
        LCM = LCM *( m[i]/ gcd );
        if(LCM==0)exit(5);
        if(m[i]/gcd==0)exit(6);
        X = (X + slowMul(slowMul(c / gcd, xi, m[i] / gcd), t, LCM)) % LCM;
    }
    if (X < maxn)X += ((maxn - X - 1) / LCM + 1) * LCM;
    return X;
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
    while (t--) {
        maxn = 0;
        multiset<long long> saber;
        int n, M;
        cin >> n >> M;
        for (int i = 0; i < n; ++i)cin >> a[i];
        for (int i = 0; i < n; ++i)cin >> m[i];
        for (int i = 0; i < n; ++i)cin >> sab[i];
        for (int i = 0; i < M; ++i) {
            long long x;
            cin >> x;
            saber.insert(x);
        }
        for (int i = 0; i < n; ++i) {
            auto it = saber.upper_bound(a[i]);
            if (it != saber.begin())it--;
            b[i] = *it;
            saber.erase(it);
            saber.insert(sab[i]);
            if (b[i] == 0)exit(3);
            maxn = max(maxn, (a[i] + b[i] - 1) / b[i]);
        }
        cout << EXCRT(n) << endl;

    }
    return 0;
}