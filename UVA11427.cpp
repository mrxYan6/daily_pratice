//
// Created by mrx on 2022/10/24.
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

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	int t;
	std::cin >> t;
	for (int cas = 1; cas <= t; ++cas) {
		i64 fz, fm;
		char c;
		std::cin >> fz >> c >> fm;
		double p = fz * 1.0 / fm;
		int n;
		std::cin >> n;

		std::vector<double> dp(n + 1, 0);
		dp[0] = 1;
		for (int i = 1; i <= n; ++i) {
			std::vector<double> ndp(n + 1, 0);
			for (int j = 0; j <= n; ++j) {
				if (j * fm <= i * fz) {
					if (j)ndp[j] += (p) * dp[j - 1];
					ndp[j] += (1 - p) * dp[j];
				} else break;
			}
			dp = ndp;
		}
		double q = std::accumulate(dp.begin(), dp.end(), 0.0);


		int ans;
		ans = 1 / q;
		std::cout << "Case #" << cas << ": ";
		std::cout << ans << '\n';
	}
	return 0;
}