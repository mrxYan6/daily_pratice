//
// Created by mrx on 2023/2/27.
//
#include <functional>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
#include <cmath>
#include <queue>
#include <array>
#include <map>

using i64 = long long;
std::array<int, 277> f;

void solve() {
    int m;
    i64 L;
    std::cin >> m >> L;
    std::vector<int> a(m);
    for (int i = 0; i < m; ++i)std::cin >> a[i];
    std::vector<int> bits;
    i64 x = L;
    do {
        bits.push_back(x & 1);
        x >>= 1;
    } while (x);
    std::vector dp(bits.size(), std::vector<i64>(8, -1));//pos,status

    auto cacal = [&](int status) -> i64 {
        int lmt = status & 1;
        int cnt1 = (status >> 2) & 1;
        int cnt2 = (status >> 1) & 1;
        i64 hi = lmt ? L % 128 : 127;
        i64 res = 0;
        for (int i = 0; i <= hi; ++i) {
            int ok = 1;
            for (int j = 0; j < m && ok; ++j) {
                if (i + j < 128) ok &= (f[i + j] ^ cnt1) == a[j];
                else ok &= (f[i + j] ^ cnt1 ^ cnt2) == a[j];
            }
            res += ok;
        }
        return res;
    };
    std::function<i64(int, int)> dfs = [&](int pos, int status) -> i64 {
        auto& res = dp[pos][status];
        if (res != -1)return res;
        else if (pos <= 6)return res = cacal(status);
        res = 0;
        int cnt1 = (status >> 2) & 1, cnt2 = (status >> 1) & 1, lmt = status & 1;
        int up = lmt ? bits[pos] : 1;
        for (int i = 0; i <= up; ++i) {
            int nxl = lmt & (i == up), nxc1 = cnt1 ^ i, nxc2 = (!cnt2) & i;
            res += dfs(pos - 1, (nxl) | (nxc1 << 2) | (nxc2 << 1));
        }
        return res;
    };
    std::cout << dfs((int(bits.size())) - 1, 1) << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int t;
    std::cin >> t;
    for (int i = 0; i < 277; ++i)f[i] = __builtin_parity(i);
    while (t--) {
        solve();
    }
    return 0;
}