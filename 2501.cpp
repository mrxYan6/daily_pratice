//
// Created by mrx on 2023/4/11.
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
    int n;
    std::cin >> n;
    std::vector<int> a(n + 2);
    for (int i = 1; i <= n; ++i)std::cin >> a[i];
    std::vector<i64> b(n + 2);
    //if a[i] - a[j] > i - j ————》 a[i] - i > a[j] - j
    for (int i = 1; i <= n; ++i) {
        b[i] = a[i] - i;
    }

    std::vector<i64> last(n + 2), len(n + 2);
    std::vector<std::vector<int>> lasts(n + 2);
    int cur = 1;
    last[1] = b[1];
    len[1] = 1;
    lasts[1].push_back(1);
    b[n + 1] = 0x3f3f3f3f;
    for (int i = 2; i <= n + 1; ++i) {
        if (last[cur] <= b[i]) {
            last[++cur] = b[i];
            len[i] = cur;
            lasts[cur].push_back(i);
        } else {
            int pos = std::upper_bound(last.begin() + 1, last.begin() + cur + 1, b[i]) - last.begin();
            last[pos] = b[i];
            len[i] = pos;
            lasts[pos].push_back(i);
        }
    }

    std::cout << n - cur + 1 << '\n';

    b[0] = -0x3f3f3f3f;
    lasts[0].push_back(0);

    std::vector<i64> f(n + 2, 0x3f3f3f3f);
    std::vector<i64> sum1(n + 2, 0), sum2(n + 2, 0);
    f[0] = 0;
    for (int i = 1; i <= n + 1; ++i) {
        for (auto j: lasts[len[i] - 1]) {
            if (j > i || b[j] > b[i]) continue;
            sum1[j] = 0;
            for (int k = j + 1; k <= i - 1; k++) sum1[k] = sum1[k - 1] + std::abs(b[k] - b[j]);
            sum2[i - 1] = 0;
            for (int k = i - 2; k >= j; k--) sum2[k] = sum2[k + 1] + std::abs(b[k + 1] - b[i]);
            for (int k = j; k <= i - 1; k++) f[i] = std::min(f[i], f[j] + sum1[k] + sum2[k]);
        }
    }
    std::cout << f[n + 1] << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    solve();

    return 0;
}