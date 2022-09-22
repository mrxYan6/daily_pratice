//
// Created by mrx on 2022/9/20.
//
#include <vector>
#include <algorithm>
#include <iostream>
#include <array>

using ll = long long;
const int mod = 1e9 + 7;

int main() {
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
#endif
#ifndef LOCAL
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
#endif
	int n, k;
	std::cin >> n >> k;

	std::vector<std::vector<int>> G(n + 1);
	for (int i = 1; i < n; ++i) {
		int x, y;
		std::cin >> x >> y;
		G[x].push_back(y);
		G[y].push_back(x);
	}
	std::vector<int> color(n + 1);
	for (int i = 0; i < k; ++i) {
		int p, c;
		std::cin >> p >> c;
		color[p] = c;
	}
	std::vector<std::array<ll, 3>> dp(n + 1);

	std::function<void(int, int)> dfs = [&](int u, int fa) {
		if (!color[u]) {
			dp[u].fill(1);
		} else dp[u][color[u] - 1] = 1;

		for (auto v: G[u]) {
			if (v == fa)continue;
			dfs(v, u);
			dp[u][0] = dp[u][0] * ((dp[v][1] + dp[v][2]) % mod) % mod;
			dp[u][1] = dp[u][1] * ((dp[v][0] + dp[v][2]) % mod) % mod;
			dp[u][2] = dp[u][2] * ((dp[v][0] + dp[v][1]) % mod) % mod;
		}
	};
	dfs(1, 1);
	std::cout << (dp[1][0] + dp[1][1] + dp[1][2]) % mod << '\n';
	return 0;
}