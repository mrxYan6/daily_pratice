//
// Created by mrx on 2022/11/16.
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
const i64 mod = 1e9 + 7;

i64 power(i64 a, i64 b) {
	i64 res = 1;
	for (; b; b >>= 1, a = a * a % mod) if (b & 1)res = res * a % mod;
	return res;
}

i64 inv(i64 a) {
	return power(a, mod - 2);
}

void sol() {
	int n;
	std::cin >> n;

	std::vector<std::vector<int>> adj(n + 1);
	for (int i = 1; i < n; ++i) {
		int u, v;
		std::cin >> u >> v;
		adj[u].emplace_back(v);
		adj[v].emplace_back(u);
	}
//	std::vector<i64> a(n + 1), b(n + 1), c(n + 1);
	std::vector<i64> a(n + 1), p(n + 1);

	i64 sum = 0;
	for (int i = 1; i <= n; ++i) {
		i64 A, B, C;
		std::cin >> A >> B >> C;
		a[i] = A;
		sum += A;
		p[i] = B * inv(C) % mod;
	}

	std::vector<std::vector<std::array<i64, 2>>> dp(n + 1, std::vector<std::array<i64, 2>>(n + 1));
	std::vector<int> siz(n + 1);
	std::vector<i64> ans(n + 1);
	std::function<void(int, int)> dfs = [&](int u, int fa) {
		siz[u] = 1;
		dp[u][1][0] = p[u];
		dp[u][1][1] = a[u] * inv(sum) % mod;
		for (auto v: adj[u]) {
			if (v == fa)continue;
			dfs(v, u);
			std::vector<std::array<i64, 2>> tmp(siz[u] + siz[v] + 1);
			for (int i = siz[u]; i >= 1; --i) {
				for (int j = 1; j <= siz[v]; ++j) {
					dp[u][i + j][0] = (dp[u][i + j][0] + dp[u][i][0] * dp[v][j][0] % mod) % mod;
					dp[u][i + j][1] = (dp[u][i + j][1] + dp[u][i][0] * dp[v][j][1] % mod) % mod;
					dp[u][i + j][1] = (dp[u][i + j][1] + dp[u][i][1] * dp[v][j][0] % mod) % mod;
				}
				dp[u][i][0] = (dp[u][i][0] * (1 - p[v])) % mod;
				dp[u][i][1] = (dp[u][i][1] * (1 - p[v])) % mod;
			}
			siz[u] += siz[v];
		}
//		std::cerr << u << ' ' << siz[u] << '\n';
		for (int i = 1; i <= siz[u]; i++) {
			if (u == 1)ans[i] = (ans[i] + dp[u][i][1]) % mod;
			else ans[i] = (ans[i] + 1ll * dp[u][i][1] * (1 - p[fa]) % mod) % mod;
		}
	};
	dfs(1, 1);

	for (int i = 1; i <= n; ++i)std::cout << (mod + ans[i]) % mod << '\n';
}

int main() {
	sol();
	return 0;
}