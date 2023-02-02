//
// Created by meiru on 2023/1/14.
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
#include <stack>

using i64 = long long;

struct Fin {
	std::vector<int> f;
	int n;

	Fin(int n) : n(n), f(n + 1) {}

	int qry(int x) {
		int ret = 0;
		for (int i = x; i; i -= i & -i)ret += f[i];
		return ret;
	}

	void add(int x, int v) {
		for (int i = x; i <= n; ++i) f[i] += v;
	}
};

struct acam {
	struct Trie {
		int dfn;
		std::vector<int> nxt;
		int fail, prev;
		int end;

		Trie() : nxt(26, 0), fail(0), end(0), cnt(0), prev(0) {}
	};

	std::vector<Trie> nodes;

	acam() : nodes(1) {}

	int NEW() {
		int id = nodes.size();
		nodes.emplace_back();
		return id;
	}

	void build() {
		std::queue<int> q;
		for (int i = 0; i < 26; i++) {
			if (nodes[0].nxt[i]) {
				q.push(nodes[0].nxt[i]);
			}
		}
		while (!q.empty()) {
			auto u = q.front();
			q.pop();
			for (int i = 0; i < 26; i++) {
				if (nodes[u].nxt[i]) {
					nodes[nodes[u].nxt[i]].fail = nodes[nodes[u].fail].nxt[i];
					q.push(nodes[u].nxt[i]);
				} else {
					nodes[u].nxt[i] = nodes[nodes[u].fail].nxt[i];
				}
			}
		}
	}

	Trie& operator [](int idx) { return nodes[idx]; }
};


void solve() {
	std::string s;
	std::cin >> s;

	acam AC;
	int cur = 0;
	std::vector<int> ends;
	for (auto x: s) {
		if (x == 'B')cur = AC[cur].prev;
		else if (x == 'P') {
			AC[cur].end++;
			ends.push_back(cur);
		} else {
			if (AC[cur].nxt[x - 'a'] == 0) {
				AC[cur].nxt[x - 'a'] = AC.NEW();
			}
			cur = AC[cur].nxt[x - 'a'];
		}
	}

	int n;
	std::cin >> n;
	std::vector<std::tuple<int, int, int>> qry(n);
	for (int i = 0; i < n; ++i) {
		auto& [u, v, id] = qry[i];
		id = i;
		std::cin >> u >> v;
		u--, v--;
	}

	std::vector adj(AC.nodes.size(), std::vector<int>());

	AC.build();
	int dfn = 0;
	std::function<void(int)> dfs = [&](int x) {
		AC[x].dfn = ++dfn;

	};

}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	solve();

	return 0;
}