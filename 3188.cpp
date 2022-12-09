//
// Created by mrx on 2022/11/20.
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

int lowbit(int x) {
	return x & (-x);
}

int lg(int x) {
	return 31 - __builtin_clz(x);
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	int n, w;
	while (std::cin >> n >> w && n + w >= 0) {
		int len = lg(w);
		std::vector<int> a(n), b(n), v(n);
		for (int i = 0; i < n; ++i) {
			int tmp;
			std::cin >> tmp >> v[i];
			a[i] = lg(lowbit(tmp));
			b[i] = tmp >> a[i];
		}
		std::vector<std::vector<std::pair<int, int>>> bag(len + 1);
		for (int i = 0; i < n; ++i) bag[a[i]].emplace_back(b[i], v[i]);
		std::vector f(len + 1, std::vector<int>(10 * n + 1));
		for (int i = 0; i <= len; ++i) {
			for (int j = 0; j < bag[i].size(); ++j) {
				auto [c, val] = bag[i][j];
				for (int k = 10 * n; k >= c; --k) {
					f[i][k] = std::max(f[i][k], f[i][k - c] + val);
				}
			}
		}


		std::vector dp(len + 1, std::vector<int>(10 * n + 1));
		dp[0] = f[0];
		for (int i = 1; i <= len; ++i) {
			for (int j = 0; j <= 10 * n; ++j) {
				for (int k = 0; k <= j; ++k) {
					dp[i][j] = std::max(dp[i][j], dp[i - 1][std::min(10 * n, k * 2 + ((w >> (i - 1)) & 1))] + f[i][j - k]);
				}
			}
		}
		std::cout << dp[len][1] << '\n';
	}
	return 0;
}