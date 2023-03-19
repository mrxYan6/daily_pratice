//
// Created by mrx on 2022/10/3.
//
#include <vector>
#include <algorithm>
#include <iostream>
#include <array>

using ll = long long;


int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    ll l, r;
    std::cin >> l >> r;

    auto sol = [&](ll x, int d) {
        std::string s = std::to_string(x);
        int n = s.length();
        std::vector dp(n + 1, std::vector(n + 1, std::vector<ll>(10, -1)));

        std::function<ll(int, int, ll, bool, bool)> dfs = [&](int pos, int digit, ll tot, bool lead, bool limit) {
            if (pos == n)return tot;
            if (!limit && lead && dp[pos][tot][digit] != -1)return dp[pos][tot][digit];
            int up = limit ? s[pos] - '0' : 9;
            ll ans = 0;
            for (int i = 0; i <= up; ++i) {
                ans += dfs(pos + 1, digit, tot + ((lead || i) && (i == digit)), lead || i, (i == up) && limit);
            }
            if (!limit && lead)return dp[pos][tot][digit] = ans;
            return ans;
        };

        return dfs(0, d, 0, false, true);
    };

    for (int i = 0; i <= 9; ++i)std::cout << sol(r, i) - sol(l - 1, i) << " \n"[i == 9];

    return 0;
}