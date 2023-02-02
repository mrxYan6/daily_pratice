//
// Created by mrx on 2022/10/5.
//
#include <vector>
#include <algorithm>
#include <iostream>
#include <array>
#include <numeric>

using ll = long long;

struct DSU {
	std::vector<int> f, dis, siz;

	DSU(int n) : f(n), dis(n), siz(n, 1) {
		std::iota(f.begin(), f.end(), 0);
	}

	void merge(int u, int v) {
		int x = qry(u), y = qry(v);
		dis[x] += siz[y];
		siz[y] += siz[x];
		f[x] = y;
	}

	int qry(int x) {
		if (x != f[x]) {
			int root = qry(f[x]);
			dis[x] += dis[f[x]];
			return f[x] = root;
		}
		return x;
	}
};

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	DSU dsu(30001);
	int t;
	std::cin >> t;

	for (int i = 0; i < t; ++i) {
		char opt;
		int u, v;
		std::cin >> opt >> u >> v;
		if (opt == 'M') {
			dsu.merge(u, v);
		} else {
			if (dsu.qry(u) != dsu.qry(v))std::cout << -1 << '\n';
			else {
				std::cout << std::abs(dsu.dis[u] - dsu.dis[v]) - 1 << '\n';
			}
		}

	}

	return 0;
}