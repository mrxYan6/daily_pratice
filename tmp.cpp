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
    i64 d, k, n;
    std::cin >> d >> k >> n;
    i64 rest_time = (n - 1) / d;
    i64 remain = (n - 1) % d + 1;
    std::cout << rest_time * (k + d) + remain << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}