//
// Created by mrx on 2022/9/13.
//
#include <bits/stdc++.h>

using ll = long long;

template<typename T>
std::array<T, 3> exgcd(T a, T b) {
    if (b == 0)return {a, 1, 0};
    auto [g, x, y] = exgcd(b, a % b);
    return {g, y, x - a / b * y};
};

void sol(int n, int c) {
    std::vector<ll> m(n), a(n);
    std::vector<ll> solution;
    std::vector<std::vector<int>> g(n);
    ll LCM = 1;

    auto crt = [&](ll n) {
        ll ret = 0;
        for (int i = 0; i < n; ++i) {
            ll w = LCM / m[i];
            auto [g, x, y] = exgcd(w, (ll) m[i]);
            ret = (ret + x * w * a[i]) % LCM;
        }
        return ret;
    };
    std::function<void(int)> dfs = [&](int dep) {
        if (dep == n) {
            solution.push_back(crt(n));
        } else {
            for (int j = 0; j < g[dep].size(); ++j) {
                a[dep] = g[dep][j];
                dfs(dep + 1);
            }
        }
    };
    ll tot = 1, bestc = 0;
    for (int i = 0; i < n; ++i) {
        int k;
        std::cin >> m[i] >> k;
        tot *= k;
        g[i].resize(k);
        for (int j = 0; j < k; ++j) std::cin >> g[i][j];
        std::sort(g[i].begin(), g[i].end());
        if (m[bestc] * g[i].size() <= m[i] * g[bestc].size())bestc = i;
    }
    if (tot > 1e4) {
        std::vector<std::set<ll>> mp(n);
        for (int i = 0; i < n; ++i) {
            if (i != bestc) {
                for (int j = 0; j < g[i].size(); ++j) {
                    mp[i].insert(g[i][j]);
                }
            }
        }

        for (int k = 0;; k++) {
            for (int j = 0; j < g[bestc].size(); ++j) {
                ll cur = k * m[bestc] + g[bestc][j];
                if (cur == 0)continue;
                bool ok = true;
                for (int i = 0; i < n; ++i) {
                    if (i == bestc)continue;
                    if (!mp[i].count(cur % m[i])) {
                        ok = false;
                        break;
                    }
                }
                if (ok) {
                    std::cout << cur << '\n';
                    if (--c == 0)return;
                }
            }
        }
    } else {
        for (int i = 0; i < n; ++i)LCM *= m[i];
        dfs(0);
        std::sort(solution.begin(), solution.end());
        for (int i = 0;; ++i) {
            for (long long X: solution) {
                ll cur = i * LCM + X;
                if (cur > 0) {
                    std::cout << cur << '\n';
                    if (--c == 0)return;
                }
            }
        }
    }
}

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
#endif
#ifndef LOCAL
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#endif
    int n, c;
    while (std::cin >> n >> c && n + c) {
        sol(n, c);
        std::cout << '\n';
    }
}