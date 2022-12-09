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

void sol() {
	int n;
	std::cin >> n;
	i64 ans = 1ll * ((n + 1) / 2) * (n + 1 - (n + 1) / 2);
	std::cout << ans << '\n';

	std::string s(n, ' ');
	int cnt = 0;
	std::function<void(int, int, int, int)> dfs = [&](int len, int cur, int odd, int even) {
		if (odd > (n + 2) / 2 || even >= (n + 2) / 2 || cnt >= 100)return;
		if (len == n) {
			if (cnt++ < 100) std::cout << s << '\n';
			return;
		}
		s[len] = 'b';
		dfs(len + 1, cur, odd + cur, even + (cur ^ 1));
		s[len] = 'r';
		dfs(len + 1, cur ^ 1, odd + (cur ^ 1), even + cur);
	};

	dfs(0, 0, 0, 0);
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	sol();

	return 0;
}