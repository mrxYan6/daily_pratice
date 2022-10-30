//
// Created by mrx on 2022/10/30.
//


#include <functional>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
#include <cmath>
#include <queue>
#include <array>
#include <iomanip>
#include <map>

using i64 = long long;

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::vector<int> prime;
	{
		std::vector<int> vis(1000006);
		for (int i = 2; i <= 1e6; ++i) {
			if (!vis[i])prime.push_back(i);
			for (int j = 0; j < prime.size() && i * prime[j] <= 1e6; ++j) {
				vis[i * prime[j]] = 1;
				if (i % prime[j] == 0)break;
			}
		}
	}

	std::vector<double> dp(1000006);
	std::vector<bool> vis(1000006, false);
	dp[1] = 0;
	vis[1] = true;

	int t;
	std::cin >> t;
	for (int cas = 1; cas <= t; ++cas) {
		int n;
		std::cin >> n;
		std::function<double(int)> dfs = [&](int x) {
			if (vis[x])return dp[x];

			vis[x] = true;

			auto& ans = dp[x];
			ans = 0;
			int useful = 0;
			int cnt = 0;
			for (int i = 0; i < prime.size() && prime[i] <= x; ++i) {
				cnt++;
				if (x % prime[i] == 0) {
					useful++;
					ans += dfs(x / prime[i]);
				}
			}
			ans = (ans + cnt) / useful;
			return ans;

		};
		double ans = dfs(n);
		std::cout << "Case " << cas << ": " << std::fixed << std::setprecision(10) << ans << '\n';
	}
	return 0;
}