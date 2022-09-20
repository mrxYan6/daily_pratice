//
// Created by mrx on 2022/9/20.
//
#include <iostream>
#include <vector>
#include <algorithm>
#include <array>

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
	int n;
	std::cin >> n;
	std::vector<std::vector<int>> G(n + 1);
	for (int i = 1; i < n; ++i) {
		int u, v;
		std::cin >> u >> v;
		G[u].push_back(v);
		G[v].push_back(u);
	}

	std::vector<std::array<int, 3>> dp(n + 1);
	//根消防员设立差不多
	std::function<void(int, int)> dfs = [&](int u, int fa) {
		//0->他父亲被覆盖
		//1->他自己被覆盖
		//2->他儿子被覆盖
		std::array<int, 3> sum{};
		for (auto v: G[u]) {
			if (v == fa)continue;
			dfs(v, u);
			for (int i = 0; i < 3; ++i)sum[i] += dp[v][i];
		}
		dp[u].fill(1);
		dp[u][0] = 1 + sum[2];
		dp[u][2] = sum[1];
		if (G[u].size()) {
			dp[u][1] = 0x3f3f3f3f;
			for (auto v: G[u]) {
				if (v == fa)continue;
				dp[u][1] = std::min(dp[u][1], sum[1] - dp[v][1] + dp[v][0]);
			}
		}
		for (int i = 1; i < 3; ++i)dp[u][i] = std::min(dp[u][i - 1], dp[u][i]);
	};

	dfs(1, 1);
	std::cout << dp[1][1] << '\n';
	return 0;
}