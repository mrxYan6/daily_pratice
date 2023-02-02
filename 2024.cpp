//
// Created by mrx on 2022/10/12.
//
#include <vector>
#include <algorithm>
#include <iostream>
#include <array>
#include <numeric>

using ll = long long;

struct DSU {
	std::vector<int> f;

	DSU(int n) : f(n) {
		std::iota(f.begin(), f.end(), 0);
	}

	int find(int x) {
		return x == f[x] ? x : f[x] = find(f[x]);
	}

	bool merge(int x, int y) {
		int fx = find(x);
		int fy = find(y);
		if (fx == fy)return false;
		else {
			f[fx] = fy;
			return true;
		}
	}
};

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int n, k;
	std::cin >> n >> k;
	DSU dsu(n + 1);
	int cnt = 0;
	for (int i = 0; i < k; ++i) {
		int opt, x, y;
		std::cin >> opt >> x >> y;
		if (x > n || y > n) {
			cnt++;
			continue;
		}
		if (opt == 1) {
			if (!dsu.merge(x, y))cnt++;
		} else {
			if (dsu.find(x) == dsu.find(y))cnt++;
		}
	}
	std::cout << cnt << '\n';

	return 0;
}