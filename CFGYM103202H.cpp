//
// Created by mrx on 2022/11/12.
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

struct crd {
	int d, k, c;

	crd(int d, int k, int c) : d(d), k(k), c(c) {}

	crd() {}
};

void sol() {
	int n, m, r;
	std::cin >> n >> m >> r;
	std::vector<crd> card(n);
	for (auto& [d, k, c]: card)std::cin >> d >> k >> c;
	card.emplace_back(1, 1, r);

	std::vector<int> rents;
	for (int i = 0; i < m; ++i) {
		int d, c;
		std::cin >> d >> c;
		for (int j = 0; j < c; ++j)rents.push_back(d);
	}

	std::sort(rents.begin(), rents.end());
	int tot = rents.size();

	std::vector<std::vector<int>> prev(n + 1, std::vector<int>(tot + 1));
	for (int i = 0; i <= n; ++i) {
		int l = 1;
		prev[i][1] = 0;
		for (int j = 2; j <= tot; ++j) {
			while (rents[j - 1] - rents[l - 1] + 1 > card[i].d || j - l + 1 > card[i].k)l++;
			prev[i][j] = l - 1;
		}
	}

	std::vector<i64> dp(tot + 1, 0x3f3f3f3f3f3f3f3f);
	dp[0] = 0;
	for (int i = 1; i <= tot; ++i) {
		for (int j = 0; j <= n; ++j) {
			int from = prev[j][i];
			dp[i] = std::min(dp[i], dp[from] + card[j].c);
		}
	}
	std::cout << dp[tot] << '\n';
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	sol();

	return 0;
}