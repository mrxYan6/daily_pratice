//
// Created by mrx on 2022/9/29.
//
#include <vector>
#include <algorithm>
#include <iostream>
#include <array>
#include <queue>

using ll = long long;

struct line {
	ll k, b;

	line(ll k, ll b) : k(k), b(b) {}

	double intersect(const line& l) const { return 1.0 * (l.b - b) / (k - l.k); }

	bool operator <(const line& rhs) const {
		if (k == rhs.k) return b > rhs.b;
		return k < rhs.k;
	}

	ll operator ()(ll x) const {
		return k * x + b;
	}
};

struct ConvexHull {
	std::vector<double> points;
	std::vector<line> lines;

	int size() { return points.size(); }

	void reset() {
		points.clear();
		lines.clear();
	}

	void init(const line& l) {
		points.push_back(-1e9);
		lines.push_back(l);
	}

	void addLine(const line& l) {
		if (points.size() == 0) {
			points.push_back(-1e9);
			lines.push_back(l);
			return;
		}
		while (lines.size() >= 2 && l.intersect(lines[lines.size() - 2]) <= points.back()) {
			points.pop_back();
			lines.pop_back();
		}
		points.push_back(l.intersect(lines.back()));
		lines.push_back(l);
	}

	ll query(int x, int id) { return lines[id](x); }

	ll query(int x) {
		int id = upper_bound(points.begin(), points.end(), x) - points.begin() - 1;
		return lines[id](x);
	}
};

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int n, m, k;
	std::cin >> n >> m >> k;

	std::vector<std::vector<std::pair<int, ll>>> adj(n);
	for (int i = 0; i < m; ++i) {
		int u, v;
		ll w;
		std::cin >> u >> v >> w;
		u--, v--;
		adj[u].emplace_back(v, w);
		adj[v].emplace_back(u, w);
	}

	std::vector<ll> dis(n, 0x3f3f3f3f3f3f3f3f);
	std::function<void(const std::vector<int>&)> dijkstra = [&](const std::vector<int>& start) {
		std::priority_queue<std::pair<ll, int>, std::vector<std::pair<ll, int>>, std::greater<>> q;
		for (auto i: start)q.emplace(dis[i], i);
		while (!q.empty()) {
			auto [dist, u] = q.top();
			q.pop();
			if (dis[u] != dist)continue;
			for (auto [v, w]: adj[u]) {
				if (w + dis[u] < dis[v]) {
					dis[v] = w + dis[u];
					q.emplace(dis[v], v);
				}
			}
		}
	};

	dis[0] = 0;
	dijkstra((std::vector<int>(1)));

	for (int i = 0; i < k; ++i) {
		ConvexHull ch;
		std::vector<int> change;
		for (ll j = 0; j < n; ++j) {
			ch.addLine(line(-2 * j, dis[j] + j * j));
		}
		int id = 0;
		for (ll u = 1; u < n; u++) {
			while (id + 1 < ch.size() && ch.query(u, id + 1) < ch.query(u, id)) id++;
			ll cur = ch.query(u, id) + ll(u) * u;
			if (cur < dis[u]) {
				change.push_back(u);
				dis[u] = cur;
			}
		}
		dijkstra(change);
	}
	for (int i = 0; i < n; ++i)std::cout << dis[i] << " \n"[i == n - 1];
	return 0;
}