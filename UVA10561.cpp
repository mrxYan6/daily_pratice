//
// Created by mrx on 2022/11/24.
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
#include <set>

using i64 = long long;

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::vector<int> sg(250, -1);
	std::function<int(int)> dfs = [&](int x) {
		if (x <= 5)return 1;
		if (sg[x] != -1)return sg[x];
		std::map<int, int> s;
		for (int i = 3; i <= 5; ++i) {
			s[dfs(x - i)]++;
		}
		for (int i = 1; i <= x - 5; ++i) {
			s[dfs(i) ^ dfs(x - 5 - i)]++;
		}
		int ret = 0;
		while (s[ret] != 0)ret++;
		return sg[x] = ret;
	};

	for (int i = 1; i <= 200; ++i) if (sg[i] == -1)dfs(i);

	int t;
	std::cin >> t;
	while (t--) {
		std::string s;
		std::cin >> s;
		int n = s.length();
		int sgg = 0;
		int cur = 0;
		for (int i = 0; i < n; ++i) {

		}
	}
	return 0;
}
