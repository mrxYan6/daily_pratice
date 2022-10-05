//
// Created by mrx on 2022/10/5.
//

#include <vector>
#include <algorithm>
#include <iostream>
#include <array>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <iomanip>
#include <numeric>

using ll = long long;

struct dsu {
	std::vector<int> f, dis;

	dsu(int n) : f(n), dis(n) {
		std::iota(f.begin(), f.end(), 0);
	}

	void merge(int u, int v) {
		f[u] = v;
		dis[u] = std::abs(u - v) % 1000;
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

void sol() {
	int n;
	std::cin >> n;
	char opt;
	dsu d(n + 1);
	while (std::cin >> opt && opt != 'O') {
		if (opt == 'E') {
			int u;
			std::cin >> u;
			d.qry(u);
			std::cout << d.dis[u] << '\n';
		} else if (opt == 'I') {
			int u, v;
			std::cin >> u >> v;
			d.merge(u, v);
		}
	}
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);


	int t;
	std::cin >> t;
	while (t--) {
		sol();
	}

	return 0;
}