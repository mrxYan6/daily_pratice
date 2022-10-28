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

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::vector<double> dp(220 + 1);
	dp[0] = 0;
	std::vector<std::pair<int, double>> pii{
			{36, 171.3},
			{44, 39.09},
			{48, 151.52},
			{56, 223.9},
			{60, 402.7}};
	std::vector<std::vector<int>> fangan(220 + 1, std::vector<int>());
	for (int j = 0; j < pii.size(); ++j) {
		auto nfangan = fangan;
		auto [v, w] = pii[j];
		auto ndp = dp;
		for (int i = v; i <= 220; ++i) {
			if (dp[i - v] + w >= ndp[i]) {
				ndp[i] = dp[i - v] + w;
				nfangan[i] = fangan[i - v];
				nfangan[i].push_back(j);
			}
		}
		dp = ndp;
		fangan = nfangan;
	}
	std::cout << dp[220] << '\n';
	for (auto x: fangan[220])std::cout << char('A' + x) << ' ';
	return 0;
}