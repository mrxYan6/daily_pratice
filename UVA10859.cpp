//
// Created by mrx on 2022/10/15.
//

#include <vector>
#include <algorithm>
#include <iostream>
#include <array>
#include <numeric>
#include <functional>

using ll = long long;

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int t;
	std::cin >> t;
	while (t--) {
		int n, m;
		std::cin >> n >> m;
		std::vector<std::vector<int>> adj(n);
		for (int i = 0; i < m; ++i) {
			int u, v;
			std::cin >> u >> v;
			adj[u].push_back(v);
			adj[v].push_back(u);
		}

		std::vector<int> vis(n);
		std::vector<std::array<int, 2>> dp(n), cnt(n);
		std::function<void(int, int)> dfs = [&](int u, int fa) {
			vis[u] = 1;
			dp[u][1] = 1;
			for (auto v: adj[u]) {
				if (v == fa)continue;
				dfs(v, u);
				dp[u][0] += dp[v][1];
				cnt[u][0] += cnt[v][1];
				if (dp[v][1] < dp[v][0]) {
					dp[u][1] += dp[v][1];
					cnt[u][1] += cnt[v][1] + 1;
				} else if (dp[v][0] < dp[v][1]) {
					dp[u][1] += dp[v][0];
					cnt[u][1] += cnt[v][0];
				} else {
					dp[u][1] += dp[v][0];
					cnt[u][1] += std::max(cnt[v][1] + 1, cnt[v][0]);
				}
			}
		};
		std::vector<int> root;
		for (int i = 0; i < n; ++i) {
			if (!vis[i]) {
				root.push_back(i);
				dfs(i, i);
			}
		}
		ll ans1 = 0, ans2 = 0;
		for (auto x: root) {
			if (dp[x][0] > dp[x][1]) {
				ans1 += dp[x][1];
				ans2 += cnt[x][1];
			} else if (dp[x][0] < dp[x][1]) {
				ans1 += dp[x][0];
				ans2 += cnt[x][0];
			} else {
				ans1 += dp[x][0];
				if (cnt[x][1] > cnt[x][0]) {
					ans2 += cnt[x][1];
				} else {
					ans2 += cnt[x][0];
				}
			}
		}
		std::cout << ans1 << ' ' << ans2 << ' ' << m - ans2 << '\n';

	}

	return 0;
}