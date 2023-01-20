//
// Created by meiru on 2023/1/10.
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

using i64 = long long;

void show(int x) {
	for (int i = 0; i < 20; ++i)std::cerr << (x >> i & 1);
	std::cerr << ' ';
}

void sol() {
	int n, m;
	std::cin >> n >> m;

	std::vector a(n, std::vector<int>(m));
	auto b = a;

	for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j)std::cin >> a[i][j];
	for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j)std::cin >> b[i][j];

	std::vector dp(std::vector<int>(1 << (n + m)));
	std::vector vis(std::vector<bool>(1 << (n + m)));
	std::function<int(int, int)> dfs = [&](int opt, int s) -> int {
		if (opt == n * m)return 0;
		if (vis[s]) return dp[s];
		vis[s] = true;
		int ans = opt & 1 ? 0x3f3f3f3f : -0x3f3f3f3f;
		int line = n, row = 0;
		bool prev = true;
		for (int i = 0; i < n + m; ++i) {
			if (s >> i & 1) {
				if (!prev) {
					auto tmp = dfs(opt + 1, s ^ (3 << (i - 1)));
					if (opt & 1) {
						ans = std::min(ans, -b[line][row] + tmp);
					} else {
						ans = std::max(ans, a[line][row] + tmp);
					}
				}
				row++;
				prev = true;
			} else {
				prev = false;
				line--;
			}
		}
		return dp[s] = ans;
	};

	int inits = 0;
	for (int i = n; i < n + m; ++i)inits |= 1 << i;
	std::cout << dfs(0, inits) << '\n';
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	sol();

	return 0;
}