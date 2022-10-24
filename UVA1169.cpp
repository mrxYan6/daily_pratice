//
// Created by mrx on 2022/10/24.
//

#include <vector>
#include <algorithm>
#include <iostream>
#include <array>
#include <numeric>
#include <cmath>
#include <functional>
#include <queue>

using i64 = long long;

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	int t;
	std::cin >> t;
	while (t--) {
		int c, n;
		std::cin >> c >> n;
		std::vector<std::pair<int, int>> point(n + 2);
		std::vector<int> sum(n + 2);
		point[0] = {0, 0};
		point[n + 1] = {0, 0};
		for (int i = 1; i <= n; ++i)std::cin >> point[i].first >> point[i].second >> sum[i];
		auto dis_1 = [&](const std::pair<int, int>& a, const std::pair<int, int>& b) {
			return std::abs(a.first - b.first) + std::abs(a.second - b.second);
		};
		std::vector<int> dp(n + 2, 0);
		std::vector<int> dis(n + 2);
		for (int i = 1; i <= n + 1; ++i) {
			dis[i] = dis[i - 1] + dis_1(point[i], point[i - 1]);
			sum[i] += sum[i - 1];
		}

		std::deque<int> q;
		q.push_back(0);
		for (int i = 1; i <= n; ++i) {
			while (!q.empty() && sum[i] - sum[q.front()] > c)q.pop_front();
			if (!q.empty())
				dp[i] = dp[q.front()] - dis[q.front() + 1] + dis[i] + dis_1(point[i], std::pair<int, int>{0, 0}) + dis_1(point[q.front() + 1], std::pair<int, int>{0, 0});
			while (!q.empty() &&
			       dp[q.back()] - dis[q.back() + 1] + dis_1(point[q.back() + 1], std::pair<int, int>{0, 0}) >
			       dp[i] - dis[i + 1] + dis_1(point[i + 1], std::pair<int, int>{0, 0}))
				q.pop_back();
			q.push_back(i);
		}
		std::cout << dp[n] << '\n';
		if (t)std::cout << '\n';
	}


	return 0;
}