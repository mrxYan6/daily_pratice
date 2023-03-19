//
// Created by mrx on 2023/3/2.
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

void solve() {
    i64 L, R;
    std::cin >> L >> R;

    std::string l = std::to_string(L);
    std::string r = std::to_string(R);

    std::vector dp(11, std::vector(11, std::vector(12, std::vector<i64>(32, -1))));
    std::function<i64(int, int, int, int)> dfs = [&](int pos, int digit, int len, int status) -> i64 {
        int have4 = status & 1, have8 = status >> 1 & 1, limitl = status >> 3 & 1, limitr = status >> 4 & 1;
        int continuous = status >> 2 & 1;
        int low = limitl ? l[pos] - '0' : 0;
        int high = limitr ? r[pos] - '0' : 9;
        if (pos == 11) {
            if (continuous) {
                if (have8 && have4)return 0;
                else return 1;
            } else return 0;
        }
        auto& res = dp[pos][digit][len][status];
        if (res != -1)return res;
        else {
            res = 0;
            for (int i = low; i <= high; ++i) {
                int nxt_len = digit == i ? len + 1 : 1;
                int next_have4 = have4 || i == 4, next_have8 = have8 || i == 8, next_limitl = limitl && i == low, next_limitr = limitr && i == high;
                int nxt_continuous = nxt_len == 3 || continuous;
                int nxt_s = next_have4 | (next_have8 << 1) | (nxt_continuous << 2) | (next_limitl << 3) | (next_limitr << 4);
                res += dfs(pos + 1, i, nxt_len, nxt_s);
            }
        }
        return res;
    };
    std::cout << dfs(0, 10, 0, 24) << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    solve();
    return 0;
}