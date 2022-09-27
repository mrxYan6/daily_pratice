//
// Created by mrx on 2022/9/27.
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

	int n;
	std::cin >> n;
	std::vector<std::vector<int>> G(n + 1);
	for (int i = 1; i < n; ++i) {
		int u, v;
		std::cin >> u >> v;
		G[u].push_back(v);
		G[v].push_back(u);
	}

	std::vector<int> siz(n + 1), max_son(n + 1), max_legal(n + 1), h(n + 1);
	std::vector<std::array<int, 2>> f(n + 1);//最大和此大紫薯
	std::function<void(int, int)> dfs1 = [&](int u, int fa) {
		siz[u] = 1;
		for (auto v: G[u]) {
			if (v == fa)continue;
			dfs1(v, u);
			siz[u] += siz[v];
			if (siz[v] > siz[max_son[u]])max_son[u] = v;
			if (siz[v] <= n / 2) {
				if (siz[v] > f[u][0])f[u][1] = f[u][0], f[u][0] = siz[v], max_legal[u] = v;
				else if (siz[v] > f[u][1])f[u][1] = siz[v];
			} else {
				if (f[v][0] > f[u][0])f[u][1] = f[u][0], f[u][0] = f[v][0], max_legal[u] = v;
				else if (f[v][0] > f[u][1])f[u][1] = f[v][0];
			}
		}
	};


	std::vector<int> ans(n + 1);
	std::function<void(int, int)> dfs2;
	dfs2 = [&](int u, int fa) {
		ans[u] = 1;
		if (siz[max_son[u]] > n / 2) {
			if (siz[max_son[u]] - f[max_son[u]][0] > n / 2)ans[u] = 0;
		} else if (n - siz[u] > n / 2) {
			if (n - siz[u] - h[u] > n / 2)ans[u] = 0;
		}

		for (auto v: G[u]) {
			if (v == fa)continue;

			if (n - siz[u] <= n / 2) {
				h[v] = std::max({h[v], n - siz[u], f[u][max_legal[u] == v]});
			} else {
				h[v] = std::max({h[v], h[u], f[u][max_legal[u] == v]});
			}
			dfs2(v, u);
		}
	};
	dfs1(1, 0);
	dfs2(1, 0);
	for (int i = 1; i <= n; ++i)std::cout << ans[i] << ' ';
	std::cout << '\n';
	return 0;
}