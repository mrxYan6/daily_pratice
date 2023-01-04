//
// Created by mrx on 2022/9/26.
//
#include <vector>
#include <algorithm>
#include <iostream>
#include <array>
#include <iomanip>

using ll = long long;

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int n;
	std::cin >> n;
	std::vector<std::vector<int>> G(n + 1);
	for (int i = 1; i < n; ++i) {
		int u, v;
		std::cin >> u >> v;
		G[u].push_back(v);
		G[v].push_back(u);
	}

	std::vector<ll> val(n + 1);
	for (int i = 1; i <= n; ++i)std::cin >> val[i];
	std::vector<ll> dp(n + 1);
	std::vector<ll> leaf(n + 1);
	std::vector<int> is_leaf(n + 1);
	int rt = 1;
	for (int i = 1; i <= n; ++i) {
		if (G[i].size() > 1) {
			rt = i;
			break;
		}
	}
	std::function<void(int, int)> dfs1 = [&](int u, int fa) {
		bool f = false;
		for (auto v: G[u]) {
			if (v == fa)continue;
			dfs1(v, u);
			leaf[u] += leaf[v];
			dp[u] += dp[v];
			f = true;
		}
		dp[u] += val[u] * leaf[u];
		if (!f)leaf[u] = 1, dp[u] = val[u], is_leaf[u] = 1;
	};

	std::function<void(int, int)> dfs2 = [&](int u, int fa) {
		for (auto v: G[u]) {
			if (v == fa)continue;
			if (is_leaf[v]) {
				dp[v] = dp[u] - val[u] + val[v] * (leaf[rt] - 2);
			} else {
				dp[v] = dp[u] - val[u] * leaf[v] + val[v] * (leaf[rt] - leaf[v]);
			}
			dfs2(v, u);
		}
	};

	dfs1(rt, 0);
	dfs2(rt, 0);
	double ans = -1e18;
	for (int i = 1; i <= n; ++i) {
		ans = std::max(ans, (double) dp[i] / (leaf[rt] - is_leaf[i]));
	}
	std::cout << std::fixed << std::setprecision(10) << ans << '\n';
	return 0;
}