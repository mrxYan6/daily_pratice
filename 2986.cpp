//
// Created by mrx on 2022/9/20.
//

#include <vector>
#include <algorithm>
#include <array>
#include <iostream>

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
	std::vector<std::vector<std::pair<int, int>>> G(n + 1);

	std::vector<ll> c(n + 1);

	for (int i = 1; i <= n; ++i) {
		std::cin >> c[i];
	}

	for (int i = 1; i < n; ++i) {
		int a, b, l;
		std::cin >> a >> b >> l;
		G[a].emplace_back(b, l);
		G[b].emplace_back(a, l);
	}

	std::vector<ll> size(n + 1, 0);

	std::vector<ll> dp(n + 1, 0);
	std::function<void(int, int)> dfs1 = [&](int u, int fa) {
		size[u] = c[u];
		for (auto [v, w]: G[u]) {
			if (v == fa)continue;
			dfs1(v, u);
			size[u] += size[v];
			dp[u] += size[v] * w + dp[v];
		}
	};
	dfs1(1, 1);
	std::function<void(int, int)> dfs2 = [&](int u, int fa) {
		for (auto [v, w]: G[u]) {
			if (v == fa)continue;
			dp[v] = dp[u] - size[v] * w + (size[1] - size[v]) * w;
			dfs2(v, u);
		}
	};
	dfs2(1, 1);
	std::cout << *std::min_element(dp.begin() + 1, dp.end()) << '\n';
	return 0;
}