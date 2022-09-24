//
// Created by mrx on 2022/9/23.
//
#include <algorithm>
#include <iostream>
#include <vector>
#include <array>

using ll = long long;

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int n, p;
	std::cin >> n >> p;
	std::vector<std::vector<int>> G(n + 1);
	for (int i = 1; i < n; ++i) {
		int u, v;
		std::cin >> u >> v;
		G[u].push_back(v);
	}

	std::vector<std::vector<int>> dp(n + 1, std::vector<int>(n + 1));
	std::vector<int> siz(n + 1);
	std::function<void(int, int)> dfs = [&](int u, int fa) {
		siz[u] = 1;
		for (auto v: G[u]) {
			if (v == fa)continue;
			dfs(v, u);
			siz[u] += siz[v];
		}
		std::fill(dp[u].begin(), dp[u].end(), 0x3f3f3f3f);
		dp[u][0] = 0;
		dp[u][siz[u]] = 1;
		for (auto v: G[u]) {
			if (v == fa)continue;
			auto tmp(dp[u]);
			for (int i = 0; i <= siz[v]; ++i) {
				for (int j = siz[u] - i; j >= 0; --j) {
					tmp[j + i] = std::min(tmp[j + i], dp[v][i] + dp[u][j]);
				}
			}
			for (int i = 0; i <= siz[v]; ++i)dp[v][i]++;
			dp[u] = tmp;
		}

	};
	dfs(1, 1);
//	for (int i = 1; i <= n; ++i)std::cerr << siz[i] << ' ';
//	std::cerr << '\n';
//	for (int i = 1; i <= n; ++i) {
//		for (int j = 0; j <= siz[i]; ++j) {
//			std::cerr << j << ":" << dp[i][j] << ' ';
//		}
//		std::cerr << '\n';
//	}
	int ans = 0x3f3f3f3f;
	for (int i = 1; i <= n; ++i) {
		if (siz[i] - p >= 0) {
			ans = std::min(ans, dp[i][siz[i] - p]);
//			std::cout << dp[i][siz[i] - p] << '\n';
		}
	}
	std::cout << ans << '\n';
	return 0;
}