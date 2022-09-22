//
// Created by mrx on 2022/7/31.
//
#include <bits/stdc++.h>

using ll = long long;
struct nod {
    int rmb, rp, ti;
};

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
    std::cin >> n;
    std::vector<nod> mm(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> mm[i].rmb >> mm[i].rp >> mm[i].ti;
    }

    int m, r;
    std::cin >> m >> r;

    std::vector<std::vector<int>> dpcnt(m + 1, std::vector<int>(r + 1, 0));
    std::vector<std::vector<int>> dptim(m + 1, std::vector<int>(r + 1, 0));
    dptim[0][0] = dpcnt[0][0] = 0;
    for (auto [rmb, rp, ti]: mm) {
        for (int i = m; i >= rmb; --i) {
            for (int j = r; j >= rp; --j) {
                if (dpcnt[i][j] < dpcnt[i - rmb][j - rp] + 1) {
                    dpcnt[i][j] = dpcnt[i - rmb][j - rp] + 1;
                    dptim[i][j] = dptim[i - rmb][j - rp] + ti;
                } else if (dpcnt[i][j] == dpcnt[i - rmb][j - rp] + 1) {
                    dptim[i][j] = std::min(dptim[i][j], dptim[i - rmb][j - rp] + ti);
                }
            }
        }
    }


    std::cout << dptim[m][r] << '\n';

    return 0;
}