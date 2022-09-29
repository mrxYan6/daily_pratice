//
// Created by mrx on 2022/9/29.
//

#include <vector>
#include <algorithm>
#include <iostream>
#include <array>

using ll = long long;

void sol() {
	ll t;
	int x, y;
	std::cin >> t >> x >> y;
	if (x + y > t)return void(std::cout << "NO\n");

	t -= x + y;
	std::array<std::array<ll, 120>, 120> f{};
	f[0][0] = t;
	for (int i = 0; i < 120; ++i) {
		for (int j = 0; j < 120; ++j) {
			if (j + 1 < 120)f[i][j + 1] += (f[i][j] + 1) / 2;
			if (i + 1 < 120)f[i + 1][j] += f[i][j] / 2;
		}
	}

	int X = 0, Y = 0;
	while (X < 120 && Y < 120) {
		if (X == x && Y == y) {
			std::cout << "YES\n";
			return;
		}
		if (f[X][Y] & 1) {
			X++;
		} else {
			Y++;
		}
	}

	std::cout << "NO\n";
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int n;
	std::cin >> n;
	while (n--)sol();

	return 0;
}