#include <bits/stdc++.h>

using ll = long long;
int s, c[5], d[5], v[5];
ll ans;//n表示N展开后各项的系数
std::complex<long double> f[300001], g[300001];

ll rev[300001], m[100001];
long double pi = acos(-1);

void fft(ll n, std::complex<long double> *fx, ll type) {
    for (int i = 0; i < n; ++i) rev[i] = (rev[i >> 1] >> 1) | (i & 1) * (n >> 1);
    for (int i = 0; i < n; ++i)
        if (rev[i] < i) {
            std::complex<long double> tmp = fx[i];
            fx[i] = fx[rev[i]];
            fx[rev[i]] = tmp;
        }
    for (int mid = 1; mid < n; mid <<= 1) {
        ll len = mid << 1;
        std::complex<long double> omg(cos(pi * 2 / len), type * sin(pi * 2 / len));
        for (int j = 0; j < n - len + 1; j += len) {
            std::complex<long double> cur(1, 0);
            for (int k = 0; k < mid; ++k) {
                std::complex<long double> c1 = fx[j + k], c2 = cur * fx[mid + j + k];
                fx[j + k] = c1 + c2;
                fx[mid + j + k] = c1 - c2;
                cur = cur * omg;
            }
        }
    }
}

void dft(ll n, std::complex<long double> *fx) {
    fft(n, fx, 1);
}

void idft(ll n, std::complex<long double> *fx) {
    fft(n, fx, -1);
    for (int i = 0; i < n; ++i) {
        fx[i] /= n;
    }
}

void init() {
    pi = acos(-1);
    ll n = 100000, len = 1 << (ll) ceil(log2(n << 1 | 1));
    f[0].real(1);//初始多项式为1
    for (int i = 1; i <= 4; ++i) {
        dft(len, f);
        for (int j = 0; j < len; ++j) g[j] = std::complex<long double>();//清空
        for (int j = 0; j <= n; j += c[i]) g[j].real(1);//第i种硬币的生成函数
        dft(len, g);
        for (int j = 0; j < len; ++j) f[j] = f[j] * g[j];
        idft(len, g);
        idft(len, f);
        for (int j = n + 1; j < len; ++j) f[j] = std::complex<long double>();//舍弃高次项
    }
    for (int i = 0; i <= 100000; ++i) m[i] = (ll) (f[i].real() + 0.5);
}

ll calc(ll x) {
    ll del = (x & 1 ? v[1] : 0) + (x & 2 ? v[2] : 0) + (x & 4 ? v[3] : 0) + (x & 8 ? v[4] : 0);
    if (s < del) return 0;
    return m[s - del] * (__builtin_popcount(x) % 2 == 0 ? 1 : -1);
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
    int t;
    for (int i = 1; i <= 4; ++i)std::cin >> c[i];
    std::cin >> t;
    init();
    while (t--) {
        for (int i = 1; i <= 4; ++i)std::cin >> d[i];
        std::cin >> s;
        for (int i = 1; i <= 4; ++i) v[i] = c[i] * (d[i] + 1);
        ans = 0;
        for (int i = 0; i < 16; ++i) ans += calc(i);
        std::cout << ans << '\n';
    }
    return 0;
}
