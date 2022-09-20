//
// Created by mrx on 2022/9/19.
//
//#include <bits/stdc++.h>
#include <iostream>
#include <algorithm>
#include <vector>
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

	std::vector<std::vector<int>> G(n + 1);

	for (int i = 2; i <= n; ++i) {
		int fa;
		std::cin >> fa;
		G[fa].push_back(i);
	}

	std::vector<std::array<ll, 5>> dp(n + 1);
	std::function<void(int, int)> dfs = [&](int u, int fa) {
		//0->覆盖祖父所需到最小消防站数量     ->  自己设立，下面取最小
		//1->覆盖父亲所需到最小消防站数量     ->  有一个儿子设立，另外的都能覆盖到他们自己的儿子
		//2->覆盖自己所需到最小消防站数量     ->  有一个孙子有消防站，另外的自己都能被覆盖到
		//3->覆盖儿子所需到最小消防站数量     ->  儿子全都被覆盖
		//4->覆盖孙子所需到最小消防站数量     ->  孙子全覆盖

		std::array<ll, 5> sum{};
		for (auto v: G[u]) {
			if (v == fa)continue;
			dfs(v, u);
			for (int i = 0; i < 5; ++i) {
				sum[i] += dp[v][i];
			}
		}

		dp[u].fill(1);
		dp[u][0] = sum[4] + 1;
		dp[u][3] = sum[2];
		dp[u][4] = sum[3];
		if (G[u].size()) {
			dp[u][1] = dp[u][2] = 0x3f3f3f3f;
			for (auto v: G[u]) {
				if (v == fa)continue;
				dp[u][1] = std::min(dp[u][1], sum[3] - dp[v][3] + dp[v][0]);
				dp[u][2] = std::min(dp[u][2], sum[2] - dp[v][2] + dp[v][1]);
			}
		}
		for (int i = 1; i < 5; ++i)dp[u][i] = std::min(dp[u][i - 1], dp[u][i]);
	};

	dfs(1, 1);

	std::cout << dp[1][2];

	return 0;
}