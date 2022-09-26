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

	int n, m;
	std::cin >> n >> m;
	std::vector<std::vector<int>> G(n + 1);
	for (int i = 1; i < n; ++i) {
		int a, b;
		std::cin >> a >> b;
		G[a].push_back(b);
		G[b].push_back(a);
	}

	std::vector<int> dep(n + 1);
	std::vector<int> dp(n + 1);
	int ans = 0;

	std::function<void(int, int)> dfs = [&](int u, int fa) {
		int mx0 = 0, mx1 = 0;
		for (auto v: G[u])
			if (v != fa) {
				dfs(v, u);
				dp[u] = std::max(dp[u], dp[v]);
				if (dp[v] > mx0) mx1 = mx0, mx0 = dp[v];
				else if (dp[v] > mx1) mx1 = dp[v];
			}
		int cnt = G[u].size() - (fa != 0);
		dp[u] += (1 + std::max(0, cnt - 1));
		ans = std::max(ans, mx0 + mx1 + 1 + std::max(0, cnt - 1 - (fa == 0)));
	};

	dfs(1, 0);
	std::cout << ans << '\n';
	return 0;
}