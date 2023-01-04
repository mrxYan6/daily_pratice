//
// Created by mrx on 2022/10/8.
//
#include <vector>
#include <algorithm>
#include <iostream>
#include <array>
#include <cmath>
#include <numeric>
#include <iomanip>

using ll = long long;

struct point {
	int x, y;

	point(int x, int y) : x(x), y(y) {}

	point() {}


};

double dis(const point& lhs, const point& rhs) {
	return sqrt((lhs.x - rhs.x) * (lhs.x - rhs.x) + (lhs.y - rhs.y) * (lhs.y - rhs.y));
}

struct edg {
	int u, v;
	double dis;

	edg(int u, int v, double dis) : u(u), v(v), dis(dis) {}

	edg() {}

	bool operator <(const edg& rhs) const {
		return dis < rhs.dis;
	}
};

struct DSU {
	std::vector<int> f;

	DSU(int n) : f(n) {
		std::iota(f.begin(), f.end(), 0);
	}

	int find(int x) {
		return x == f[x] ? x : f[x] = find(f[x]);
	}

	void merge(int u, int v) {
		f[find(u)] = find(v);
	}
};

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int n, m;
	std::cin >> n >> m;
	std::vector<point> p(m + 1);
	for (int i = 1; i <= m; ++i) {
		std::cin >> p[i].x >> p[i].y;
	}

	std::vector<edg> e;
	for (int i = 1; i <= m; ++i) {
		e.emplace_back(0, i, p[i].x);
		e.emplace_back(i, m + 1, n - p[i].x);
		for (int j = i + 1; j <= m; ++j) {
			double dist = dis(p[i], p[j]);
			e.emplace_back(i, j, dist / 2);
		}
	}
	std::sort(e.begin(), e.end());

	DSU dsu(m + 2);
	double ans = 0;
	for (auto [u, v, w]: e) {
		if (dsu.find(0) == dsu.find(m + 1))break;
		ans = std::max(ans, w);
		dsu.merge(u, v);
	}
	std::cout << std::fixed << std::setprecision(2) << ans << '\n';

	return 0;
}