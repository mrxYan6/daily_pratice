//
// Created by mrx on 2022/8/10.
//
#include <bits/stdc++.h>

using ll = long long;
std::vector<int> prime = {2, 3, 5, 7, 11, 13, 17, 19};

struct nod {
    int d, s;

    nod(int x) {
        for (int i = 0; i < 8; ++i) {
            while (x % prime[i] == 0) {
                x /= prime[i];
                s |= 1 << i;
            }
        }

        d = x;
    }

    bool operator<(const nod &rhs) const {
        return d == rhs.d ? s < rhs.s : d < rhs.d;
    }
};

ll p;

ll norm(ll x) {
    int v;
    if (-p <= x && x < p) v = static_cast<int>(x);
    else v = static_cast<int>(x % p);
    if (v < 0) v += p;
    return v;
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

    int n;
    std::cin >> n >> p;
    std::vector<nod> digit;
    for (int i = 2; i <= n; ++i) {
        digit.emplace_back(i);
    }
    std::sort(digit.begin(), digit.end());

    std::vector<std::vector<ll>>
            f1(1 << 8, std::vector<ll>(1 << 8)),
            f2(1 << 8, std::vector<ll>(1 << 8)),
            dp(1 << 8, std::vector<ll>(1 << 8));

    dp[0][0] = 1;
    for (int i = 0; i < n - 1; ++i) {
        if (i == 0 || digit[i].d == 1 || digit[i].d != digit[i - 1].d) {
            f1 = dp;
            f2 = dp;
        }
        for (int j = (1 << 8) - 1; j >= 0; --j) {
            for (int k = (1 << 8) - 1; k >= 0; --k) {
                if (j & k)continue;
                auto s = digit[i].s;
                if (!(s & j))f2[j][k | s] = norm(f2[j][k | s] + f2[j][k]);
                if (!(s & k))f1[j | s][k] = norm(f1[j | s][k] + f1[j][k]);
            }
        }
        if (i == n - 2 || digit[i].d != digit[i + 1].d || digit[i].d == 1) {
            for (int j = 0; j < 1 << 8; ++j) {
                for (int k = 0; k < 1 << 8; ++k) {
                    if (j & k)continue;
                    dp[j][k] = norm(norm(f1[j][k] + f2[j][k]) - dp[j][k]);
                }
            }
        }
    }
    ll ans = 0;
    for (int i = 0; i < 1 << 8; ++i) {
        for (int j = 0; j < 1 << 8; ++j) {
            if (!(i & j))ans = norm(ans + dp[i][j]);
        }
    }
    std::cout << ans << '\n';
    return 0;
}