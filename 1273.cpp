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
		for (int j = 0; j <= cnt; ++j) {
			int v, w;
			std::cin >> v >> w;
			G[u].emplace_back(v, w);
		}
	}

	std::vector<int> val(n + 1);
	for (int i = n - m + 1; i <= n; ++i)std::cin >> val[i];
	std::vector<std::vector<int>> dp(n + 1, std::vector<int>(n + 1, -0x3f3f3f3f));

	for (int i = 1; i <= n; ++i)dp[i][0] = 0;

	std::function<void(int)> dfs = [&](int u) {

	};
	dfs(1);

	return 0;
}