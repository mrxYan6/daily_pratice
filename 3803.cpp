//
// Created by mrx on 2022/7/13.
//
#include <bits/stdc++.h>

#define ll long long
#define endl '\n'
using namespace std;

inline void FFT(vector<complex<long double>> &a, vector<long long> &inv, long long limit, int type) {
    if (limit == 1)return;
    for (int i = 0; i < limit; ++i) {
        if (i < inv[i])swap(a[i], a[inv[i]]);
    }
    for (long long mid = 1; mid < limit; mid <<= 1) {
        long long r = mid << 1;
        complex<long double> wn(cos(acos(-1) / mid), type * sin(acos(-1) / mid));
        for (long long i = 0; i < limit; i += r) {
            complex<long double> w(1, 0);
            for (long long k = i; k < i + mid; ++k) {
                complex<long double> u = a[k];
                complex<long double> t = w * a[k + mid];
                a[k] = u + t;
                a[k + mid] = u - t;
                w = w * wn;
            }
        }
    }
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
    int n, m;
    std::cin >> n >> m;
    long long limit = 1;
    while (limit <= (max(n, m) << 1))limit <<= 1;
    vector<complex<long double>> F(limit + 10);
    vector<long long> inv(limit + 10);
    for (int i = 0; i < limit; ++i) {
        inv[i] = (inv[i >> 1] >> 1) | ((i & 1) ? limit >> 1 : 0);
    }
    for (int i = 0; i <= n; ++i) {
        long double tmp;
        cin >> tmp;
        F[i].real(tmp);
    }
    for (int i = 0; i <= m; ++i) {
        long double tmp;
        cin >> tmp;
        F[i].imag(tmp);
    }


    FFT(F, inv, limit, 1);
    for (int i = 0; i <= limit; ++i) {
        F[i] = F[i] * F[i];
    }
    FFT(F, inv, limit, -1);
    for (int i = 0; i <= n + m; ++i) {
        long long ans = F[i].imag() / limit / 2 + 0.5;
        cout << ans << ' ';
    }
    cout << endl;
    return 0;
}
