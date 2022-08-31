//
// Created by mrx on 2022/7/31.
//
#include <bits/stdc++.h>

using ll = long long;

struct nod {
    int h, a, c;

    nod() {}

    bool operator<(const nod &rhs) const {
        return a < rhs.a;
    }
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
    std::vector<nod> p(n);

    int mx = 0;
    for (int i = 0; i < n; ++i) {
        std::cin >> p[i].h >> p[i].a >> p[i].c;
        mx = std::max(mx, p[i].a);
    }

    std::sort(p.begin(), p.end());
    std::vector<std::vector<int>> dp_cnt(mx + 1, std::vector<int>(n, 0));
    std::vector<int> dp_h(mx + 1, 0);
    dp_h[0] = 1;
    for (int i = 0; i < n; ++i) {
        for (int j = p[i].h; j <= p[i].a; ++j) {
            if (dp_h[j] == 1)continue;
            if (dp_h[j - p[i].h] == 1 && dp_cnt[j - p[i].h][i] < p[i].c) {
                dp_cnt[j][i] = dp_cnt[j - p[i].h][i] + 1;
                dp_h[j] = 1;
            }
        }
    }

    int ans = 0;
    for (int i = 0; i <= mx; ++i)
        if (dp_h[i])ans = i;
    std::cout << ans << '\n';
    return 0;
}