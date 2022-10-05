//
// Created by mrx on 2022/10/4.
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

	std::vector<int> f(1e6 + 10);
	f[3] = 0;
	for (int i = 4; i <= 1e6; ++i)f[i] = f[i - 1] + ((i - 1) * (i - 2) / 2 - (i - 1) / 2) / 2;

	int n;

	while (std::cin >> n && n >= 3) {
		std::cout << f[n] << '\n';
	}
	return 0;
}