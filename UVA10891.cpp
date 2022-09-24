//
// Created by mrx on 2022/9/24.
//
#include <iostream>
#include <algorithm>
#include <vector>
#include <array>

using ll = long long;

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int n;
	while (std::cin >> n && n) {
		std::vector<int> a(n + 1);
		for (int i = 1; i <= n; ++i)std::cin >> a[i];
		std::vector<int> sum(n + 1);
		for (int i = 1; i <= n; ++i)sum[i] = sum[i - 1] + a[i];
		std::vector<std::vector<int>> dp(n + 1, std::vector<int>(n + 1, 0));
		std::vector<int> lmin(n + 1, 0x3f3f3f3f), rmin(n + 1, 0x3f3f3f3f);

		for (int len = 1; len <= n; ++len) {
			for (int l = 1; l + len - 1 <= n; ++l) {
				int r = l + len - 1;
				dp[l][r] = sum[r] - sum[l - 1] - std::min({0, lmin[l], rmin[r]});
				lmin[l] = std::min(lmin[l], dp[l][r]);
				rmin[r] = std::min(rmin[r], dp[l][r]);
			}
		}
		std::cout << 2 * dp[1][n] - sum[n] << '\n';
	}
	return 0;
}