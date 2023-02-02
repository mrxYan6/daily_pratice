//
// Created by mrx on 2022/9/29.
//
#include <vector>
#include <algorithm>
#include <iostream>
#include <array>

using ll = long long;

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int n;
	int cas = 0;
	while (std::cin >> n && n) {
		std::vector<int> adj(n);
		for (int i = 0; i < n; ++i) {
			int cnt;
			std::cin >> cnt;
			adj[i] = 1 << i;
			while (cnt--) {
				int x;
				std::cin >> x;
				adj[i] |= (1 << x);
			}
		}

		std::cout << "Case " << ++cas << ": ";

		std::vector<int> cover(1 << n);
		for (int s = 0; s < (1 << n); ++s) {
			cover[s] = 0;
			for (int i = 0; i < n; ++i) {
				if (s & (1 << i))cover[s] |= adj[i];
			}
		}

		std::vector<int> dp(1 << n);
		int all = (1 << n) - 1;
		for (int s = 1; s < (1 << n); ++s) {
			dp[s] = 0;
			for (int subs = s; subs; subs = (subs - 1) & s) {
				if (cover[subs] == all)dp[s] = std::max(dp[s], dp[s ^ subs] + 1);
			}
		}
		std::cout << dp[all] << '\n';
	}
	return 0;
}