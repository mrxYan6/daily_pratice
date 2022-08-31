//
// Created by mrx on 2022/7/17.
//
#include <bits/stdc++.h>

using ll = long long;

struct nod {
    int cost, val;

    nod(int c, int v) : cost(c), val(v) {}
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
    int h1, h2, m1, m2;
    char c;
    std::cin >> h1 >> c >> m1 >> h2 >> c >> m2;
    int n;
    std::cin >> n;
    std::vector<nod> zeroone, hole;
    for (int i = 1; i <= n; ++i) {
        int t, v, p;
        std::cin >> t >> v >> p;
        if (p == 0)hole.emplace_back(t, v);
        else {
            for (int cur = 1; cur <= p; cur *= 2) {
                zeroone.emplace_back(cur * t, cur * v);
                p -= cur;
            }
            if (p) {
                zeroone.emplace_back(p * t, p * v);
            }
        }
    }
    int time = (h2 - h1) * 60 + (m2 - m1);
    std::vector<int> bag(time + 1, -1);
    bag[0] = 0;
    for (auto [cost, val]: hole) {
        for (int i = cost; i <= time; ++i) {
            if (bag[i - cost] == -1)continue;
            bag[i] = std::max(bag[i], bag[i - cost] + val);
        }
    }
    for (auto [cost, val]: zeroone) {
        for (int i = time; i >= cost; --i) {
            if (bag[i - cost] == -1)continue;
            bag[i] = std::max(bag[i], bag[i - cost] + val);
        }
    }
    std::cout << bag[time] << "\n";
    return 0;
}