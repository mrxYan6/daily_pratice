//
// Created by meiru on 2023/1/4.
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

void sol() {
	int n;
	std::cin >> n;

	std::vector<int> deg(n);
	for (int i = 0; i < n; ++i) {
		std::string s(n, '1');
		s[i] = '0';
		std::cout << "? " << i + 1 << ' ' << s << std::endl;
		std::cin >> deg[i];
	}

	std::vector<int> id(n);
	std::iota(id.begin(), id.end(), 0);
	std::sort(id.begin(), id.end(), [&](int x, int y) {
		return deg[x] < deg[y];
	});

	int sum = 0;
	int cur = 0;
	for (int i = 0; i < n - 1; ++i) {
		sum += deg[id[i]];
		if (sum == i * (i + 1) / 2)cur = i + 1;
	}

	std::string ans(n, '0');
	for (int i = cur; i < n; ++i)ans[id[i]] = '1';
	std::cout << "! " << ans << std::endl;
}

int main() {
	sol();
	return 0;
}