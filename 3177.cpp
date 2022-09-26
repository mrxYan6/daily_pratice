//
// Created by mrx on 2022/9/26.
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
	int n, k;
	std::cin >> n >> k;
	std::vector<std::vector<std::pair<int, int>>> G(n + 1);
	for (int i = 1; i < n; ++i) {
		int u, v, w;
		std::cin >> u >> v >> w;
		G[u].emplace_back(v, w);
		G[v].emplace_back(u, w);
	}

	std::vector<std::vector<ll>> dp(n + 1, std::vector<ll>(n + 1));
	std::vector<int> siz(n + 1);
	std::function<void(int, int)> dfs = [&](int u, int fa) {
		siz[u] = 1;
		std::fill(dp[u].begin(), dp[u].end(), -1);
		dp[u][0] = dp[u][1] = 0;
		for (auto [v, w]: G[u]) {
			if (v == fa)continue;
			dfs(v, u);
			siz[u] += siz[v];
		}
		for (auto [v, w]: G[u]) {
			if (v == fa)continue;
			for (int i = std::min(k, siz[u]); i >= 0; --i) {
				for (int j = 0; j <= std::min(i, siz[v]); ++j) {
					if (~dp[u][i - j]) {
						ll val = (ll) j * (k - j) * w + (ll) (siz[v] - j) * (n - k + j - siz[v]) * w;
						dp[u][i] = std::max(dp[u][i], dp[u][i - j] + dp[v][j] + val);
					}
				}
			}
		}
	};
	dfs(1, 1);
	std::cout << dp[1][k] << '\n';
	return 0;
}