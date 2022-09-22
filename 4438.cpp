//
// Created by mrx on 2022/9/21.
//
#include <vector>
#include <algorithm>
#include <iostream>
#include <array>

using ll = long long;

int main() {
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
#endif
#ifndef LOCAL
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
#endif
	int n;
	std::cin >> n;
	std::vector<int> l(n + 1);
	std::vector<int> r(n + 1);
	for (int i = 1; i < n; ++i) {
		int s, t;
		std::cin >> s >> t;
		if (s > 0)l[i] = s;
		else l[i] = (n - 1 - s);
		if (t > 0)r[i] = (t);
		else r[i] = (n - 1 - t);
	}

	std::vector<std::array<ll, 3>> val(2 * n);
	for (int i = 1; i <= n; ++i) {
		for (int j = 0; j < 3; ++j)std::cin >> val[i][j];
	}

	std::vector<std::vector<std::array<ll, 42>>> dp(n + 1, std::vector<std::array<ll, 42>>(42));

	std::function<ll(int, int, int)> dfs = [&](int i, int j, int k) {
		if (i >= n)return val[i - n + 1][2] * (val[i - n + 1][0] + j) * (val[i - n + 1][1] + k);
		if (dp[i][j][k] != 0)return dp[i][j][k];
		return dp[i][j][k] = std::min(dfs(l[i], j, k) + dfs(r[i], j, k + 1), dfs(l[i], j + 1, k) + dfs(r[i], j, k));
	};
	std::cout << dfs(1, 0, 0);

	return 0;
}