//
// Created by mrx on 2022/9/20.
//
#include <iostream>
#include <algorithm>
#include <vector>

using ll = long long;

int main() {
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
#endif
#ifndef LOCAL
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
#endif
	int n, m;
	std::cin >> n >> m;
	std::vector<std::vector<std::pair<int, int>>> G(n + 1);

	for (int u = 1; u <= n - m; ++u) {
		int cnt;
		std::cin >> cnt;
		for (int j = 0; j < cnt; ++j) {
			int v, w;
			std::cin >> v >> w;
			G[u].emplace_back(v, w);
		}
	}

	std::vector<int> val(n + 1);
	for (int i = n - m + 1; i <= n; ++i)std::cin >> val[i];
	std::vector<std::vector<int>> dp(n + 1, std::vector<int>(n + 1, -0x3f3f3f3f));
	std::vector<int> siz(n + 1, 0);
	for (int i = 1; i <= n; ++i)dp[i][0] = 0;

	std::function<void(int)> dfs = [&](int u) {
		siz[u] = 1;
		if (u > n - m) {
			dp[u][1] = val[u];
			return;
		}
		for (auto [v, c]: G[u]) {
			dfs(v);
			siz[u] += siz[v];
		}
		for (auto [v, c]: G[u]) {
			auto ndp = dp[u];
			for (int i = siz[v]; i; --i) {
				for (int j = siz[u]; j >= i; --j) {
					ndp[j] = std::max(ndp[j], dp[u][j - i] + dp[v][i] - c);
				}
			}
			dp[u] = ndp;
		}
	};
	dfs(1);
	for (int i = m; i >= 0; --i) {
		if (dp[1][i] >= 0) {
			std::cout << i << '\n';
			break;
		}
	}
	return 0;
}