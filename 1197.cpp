//
// Created by mrx on 2022/10/8.
//
#include <vector>
#include <algorithm>
#include <iostream>
#include <array>
#include <numeric>

using ll = long long;


struct DSU {
	std::vector<int> f, siz;

	DSU(int n) : f(n), siz(n, 1) {
		std::iota(f.begin(), f.end(), 0);
	}

	int find(int x) {
		return x == f[x] ? x : f[x] = find(f[x]);
	}

	bool merge(int u, int v) {
		int fu = find(u), fv = find(v);
		if (fu == fv)return false;
		if (siz[fu] > siz[fv])f[fv] = fu;
		else f[fu] = fv;
		return true;
	}

};

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int n, m;
	std::cin >> n >> m;
	std::vector<std::vector<int>> adj(n);
	for (int i = 0; i < m; ++i) {
		int u, v;
		std::cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	int k;
	std::cin >> k;

	std::vector<int> order(k);
	std::vector<bool> exist(n, true);
	for (int i = 0; i < k; ++i) {
		std::cin >> order[i];
		exist[order[i]] = false;
	}
	std::reverse(order.begin(), order.end());

	DSU dsu(n);
	int cnt = n - k;
	for (int i = 0; i < n; ++i) {
		if (exist[i]) {
			for (auto v: adj[i]) {
				if (exist[v])cnt -= dsu.merge(i, v);
			}
		}
	}
	std::vector<int> ans;
	ans.push_back(cnt);
	for (int i = 0; i < k; ++i) {
		int u = order[i];
		exist[u] = true;
		for (auto v: adj[u]) {
			if (exist[v]) cnt -= dsu.merge(u, v);
		}
		ans.push_back(++cnt);
	}
	std::reverse(ans.begin(), ans.end());
	for (int i = 0; i <= k; ++i)std::cout << ans[i] << '\n';
	return 0;
}