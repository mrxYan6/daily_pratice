//
// Created by mrx on 2022/10/28.
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

#include <iomanip>

using i64 = long long;

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int t, r;
	std::cin >> t >> r;
	int n, m;
	std::cin >> n >> m;
	std::vector<std::vector<std::pair<int, int>>> adj(n + 1);
	for (int i = 0; i < m; ++i) {
		int u, v, w;
		std::cin >> u >> v >> w;
		adj[u].emplace_back(v, w);
		adj[v].emplace_back(u, w);
	}

	int k;
	std::cin >> k;
	std::vector<std::vector<std::pair<int, int>>> adj2(k + 2);
	std::vector<int> prob(k + 2);
	std::vector<int> gra_2(k + 2);
	gra_2[0] = 1;
	gra_2[k + 1] = n;
	prob[0] = 100;
	for (int i = 1; i <= k; ++i) {
		std::cin >> gra_2[i] >> prob[i];
	}

	std::vector mp(k + 2, std::vector<int>(k + 2, 0));

	for (int i = 0; i <= k + 1; ++i) {
		std::vector<int> dis(n + 1, 0x3f3f3f3f);
		auto dij = [&](int start) {
			std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> q;
			dis[start] = 0;
			q.emplace(0, start);
			while (!q.empty()) {
				auto [dist, u] = q.top();
				q.pop();
				if (dis[u] != dist)continue;
				for (auto [v, w]: adj[u]) {
					if (dis[v] > dis[u] + w) {
						dis[v] = dis[u] + w;
						q.emplace(dis[v], v);
					}
				}
			}
		};

		dij(gra_2[i]);
		for (int j = 0; j <= k + 1; ++j)mp[i][j] = dis[gra_2[j]];
	}

	if (mp[0][k + 1] == 0x3f3f3f3f)std::cout << -1 << '\n';
	else {
		std::vector dp(1 << (k + 2), std::vector<double>(k + 2, -1));
		std::function<double(int, int)> dfs = [&](int s, int x) {
			if (dp[s][x] >= 0)return dp[s][x];
			if (!s) {
				return dp[s][x] = 0.01 * (100 - prob[x]) * mp[x][k + 1] / r + 0.01 * prob[x] * mp[x][k + 1] / t;
			}
			double cur = 1.0 * mp[x][k + 1] / t;
			for (int i = 0; i <= k; ++i) {
				if ((s >> i & 1) && mp[x][gra_2[i + 1]] < 0x3f3f3f3f) {
					cur = std::min(cur, 1.0 * mp[x][i + 1] / t + dfs(s ^ 1 << i, i + 1));
				}
			}
			return dp[s][x] = 0.01 * (100 - prob[x]) * mp[x][k + 1] / r + 0.01 * prob[x] * cur;
		};
		double ans = dfs((1 << (k + 1)) - 1, 0);
		std::cout << std::fixed << std::setprecision(6) << ans << '\n';
	}

	return 0;
}