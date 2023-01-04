//
// Created by mrx on 2022/11/5.
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

	int n, m;
	std::cin >> n >> m;
	std::vector<int> w(m);
	for (int i = 0; i < m; ++i) {
		std::cin >> w[i];
	}

	std::vector<std::vector<std::pair<int, int>>> adj(n);

	for (int i = 0; i < m; ++i) {
		int u, v, c;
		std::cin >> u >> v >> c;
		u--, v--, c--;
		adj[u].emplace_back(v, c);
		adj[v].emplace_back(u, c);
	}

	std::vector<int> dis(n, 0);
	{
		std::vector<int> vis(n, false);
		std::queue<int> q;
		vis[0] = true;
		q.push(0);
		while (!q.empty()) {
			auto u = q.front();
			q.pop();
			for (auto [v, c]: adj[u]) {
				if (!vis[v]) {
					dis[v] = dis[u] + 1;
					vis[v] = true;
					q.push(v);
				}
			}
		}
	}

	std::vector<int> cnt(m, 0);
	std::vector<i64> ans(n, 0x3f3f3f3f);
	std::function<void(int, i64)> dfs = [&](int u, i64 cost) {
		ans[u] = std::min(ans[u], cost);
		for (auto [v, c]: adj[u]) {
			if (dis[v] == dis[u] + 1) {
				cnt[c]++;
				dfs(v, cost + cnt[c] * w[c]);
				cnt[c]--;
			}
		}
	};

	dfs(0, 0);
	for (int i = 1; i < n; ++i)std::cout << ans[i] << '\n';

	return 0;
}