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

	ll n, m;
	while (std::cin >> n >> m && n + m) {
		if (n > m)std::swap(n, m);
		std::cout << n * m * (n + m - 2) + 2 * n * (n - 1) * (3 * m - n - 1) / 3 << '\n';
	}

	return 0;
}