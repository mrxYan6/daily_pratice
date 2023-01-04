//
// Created by mrx on 2022/9/23.
//
#include <algorithm>
#include <vector>
#include <iostream>
#include <array>

using ll = long long;

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);


	std::string s;
	std::cin >> s;

	int cnt = 0;
	int n = s.length();

	std::function<std::array<int, 6>()> dfs = [&]() -> std::array<int, 6> {
		int cur = s[cnt++] - '0';
		if (cur == 0) {
			return {0, 0, 1, 0, 0, 1};
		} else if (cur == 1) {
			auto s1 = dfs();
			auto ret = s1;
			ret[0] = std::min(s1[1], s1[2]);
			ret[1] = std::min(s1[0], s1[2]);
			ret[2] = std::min(s1[1], s1[0]) + 1;
			ret[3] = std::max(s1[4], s1[5]);
			ret[4] = std::max(s1[3], s1[5]);
			ret[5] = std::max(s1[3], s1[4]) + 1;
			return ret;
		} else {
			auto s1 = dfs();
			auto s2 = dfs();
			auto ret = s1;
			ret[0] = std::min(s1[1] + s2[2], s1[2] + s2[1]);
			ret[1] = std::min(s1[0] + s2[2], s1[2] + s2[0]);
			ret[2] = std::min(s1[1] + s2[0], s1[0] + s2[1]) + 1;
			ret[3] = std::max(s1[4] + s2[5], s1[5] + s2[4]);
			ret[4] = std::max(s1[3] + s2[5], s1[5] + s2[3]);
			ret[5] = std::max(s1[3] + s2[4], s1[4] + s2[3]) + 1;
			return ret;
		}
	};
	auto ans = dfs();
	std::cout << std::max({ans[3], ans[4], ans[5]}) << ' ' << std::min({ans[0], ans[1], ans[2]}) << '\n';
	return 0;
}