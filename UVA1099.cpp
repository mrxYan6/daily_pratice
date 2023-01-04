//
// Created by mrx on 2022/10/28.
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

	int n;
	int cas = 1;
	while (std::cin >> n && n) {
		int x, y;
		std::cin >> x >> y;
		std::vector<int> a(n);
		for (int i = 0; i < n; ++i)std::cin >> a[i];
		std::vector<int> sum(1 << n);
		for (int s = 0; s < 1 << n; ++s) {
			int tmp = s;
			while (tmp) {
				int lbt = tmp & -tmp;
				int i = __builtin_ctz(lbt);
				sum[s] += a[i];
				tmp -= lbt;
			}
		}

//		std::vector<std::vector<std::vector<bool>>> mp(105, std::vector<std::vector<bool>>(105, std::vector<bool>(1 << n)));
//		std::vector<std::vector<std::vector<bool>>> vis(105, std::vector<std::vector<bool>>(105, std::vector<bool>(1 << n)));
//
//		std::function<bool(int, int, int)> dfs = [&](int c, int r, int s) -> bool {
//			if (vis[c][r][s])return mp[c][r][s];
//			vis[c][r][s] = true;
//
//			if (c == 1) return mp[c][r][s] = r >= sum[s];
//			if (r == 1) return mp[c][r][s] = c >= sum[s];
//
//			for (int s0 = s; s0; s0 = s & (s0 - 1)) {
//				for (int j = 1; j < c; ++j) if (dfs(c - j, r, s0) && dfs(j, r, s ^ s0))return mp[c][r][s] = true;
//				for (int j = 1; j < r; ++j) if (dfs(c, r - j, s0) && dfs(c, j, s ^ s0))return mp[c][r][s] = true;
//			}
//
//			return mp[c][r][s] = false;
//		};

		std::vector<std::vector<bool>> dp(101, std::vector<bool>(1 << n));
		std::vector<std::vector<bool>> vis(101, std::vector<bool>(1 << n));

		std::function<bool(int, int)> dfs = [&dp, &vis, &sum, &dfs](int x, int s) -> bool {
			if (vis[x][s])return dp[x][s];
			vis[x][s] = true;
			if (__builtin_popcount(s) == 1)return dp[x][s] = true;
			int y = sum[s] / x;
			for (int s0 = (s - 1) & s; s0; s0 = (s0 - 1) & s) {
				int x0 = sum[s0] / y;
				int y0 = sum[s0] / x;
				int x1 = sum[s ^ s0] / y;
				int y1 = sum[s ^ s0] / x;
				if (sum[s0] % x == 0 && dfs(std::min(x, y0), s0) && dfs(std::min(x, y1), s0 ^ s))return dp[x][s] = true;
				if (sum[s0] % y == 0 && dfs(std::min(x0, y), s0) && dfs(std::min(x1, y), s ^ s0))return dp[x][s] = true;
			}
			return dp[x][s] = false;
		};

		std::cout << "Case " << cas++ << ": ";
		if (sum[(1 << n) - 1] != x * y)std::cout << "No\n";
		else std::cout << (dfs(std::min(x, y), (1 << n) - 1) ? "Yes" : "No") << '\n';
	}
	return 0;
}