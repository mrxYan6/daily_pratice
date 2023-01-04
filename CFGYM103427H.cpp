//
// Created by mrx on 2022/11/4.
//
#include <functional>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
#include <cmath>
#include <queue>
#include <stack>
#include <iomanip>
#include <array>
#include <map>

using i64 = long long;

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int n, m;
	std::cin >> n >> m;
	std::vector<std::vector<std::pair<int, int>>> adj(n);

	i64 sum = 0;

	for (int i = 0; i < m; ++i) {
		int u, v, w;
		std::cin >> u >> v >> w;
		sum += w;
		u--, v--;
		adj[u].emplace_back(v, w);
		adj[v].emplace_back(u, w);
	}


	std::stack<int> stk;
	std::vector<int> in_stack(n), siz(n), belong(n), dfn(n), low(n);
	int cnt = 0, scc = 0;
	std::function<void(int, int)> tarjan = [&](int u, int fa) {
		low[u] = dfn[u] = ++cnt;
		stk.push(u);
		for (auto [v, w]: adj[u]) {
			if (v == fa)continue;
			if (!dfn[v]) {
				tarjan(v, u);
				siz[u] += siz[v] + 1;
				low[u] = std::min(low[u], low[v]);
			} else if (!belong[v]) {
				low[u] = std::min(low[u], dfn[v]);
				if (dfn[v] > dfn[u])siz[u]++;
			}
		}
		if (dfn[u] == low[u]) {
			int v;
			scc++;
			do {
				v = stk.top();
				stk.pop();
				belong[v] = scc;
			} while (v != u);
		}
	};

	//如果是奇数的话就有一条边肯定匹配不上，那么就要删除掉。
	if (m & 1) {
		for (int i = 0; i < n; ++i) {
			if (!dfn[i])tarjan(i, i);
		}
		i64 ans = 0;
		for (int u = 0; u < n; ++u) {
			for (auto [v, w]: adj[u]) {
				//如果scc的大小是一个奇数，那么就要进行删边。
				if (belong[u] == belong[v] || (dfn[v] > dfn[u] && (!(siz[v] & 1))))ans = std::max(ans, sum - w);
			}
		}
		sum = ans;
	}

	std::cout << sum << '\n';

	return 0;
}