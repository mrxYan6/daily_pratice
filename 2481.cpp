//
// Created by mrx on 2023/1/29.
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

void solve() {
	i64 a, b;
	std::cin >> a >> b;
	i64 n, m;
	std::cin >> n >> m;
	if (a * m < (m + 1) * b) {
		std::cout << a * (n / (m + 1)) * m + std::min(a, b) * (n - n / (m + 1) * (m + 1)) << '\n';
	} else {
		std::cout << b * n << '\n';
	}
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	int n;
	std::cin >> n;
	while (n--)solve();

	return 0;
}