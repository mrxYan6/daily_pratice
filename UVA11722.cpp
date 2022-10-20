//
// Created by mrx on 2022/10/20.
//

#include <vector>
#include <algorithm>
#include <iostream>
#include <array>
#include <numeric>
#include <cmath>
#include <functional>
#include <iomanip>

using ll = long long;

void sol() {
	int t1, t2, s1, s2, w;
	std::cin >> t1 >> t2 >> s1 >> s2 >> w;
	ll fm = (t2 - t1) * (s2 - s1);
	auto cacal = [&](double x) -> double {
		if (s1 <= t1 + x && t1 + x <= s2 && s2 <= t2 + x)
			return (s2 - (t1 + x)) * ((s2 - x) - t1) / 2;
		if (t1 + x <= s1 && s2 <= t2 + x)
			return (((s2 - x) - t1) + ((s1 - x) - t1)) * (s2 - s1) / 2;
		if (t1 + x <= s1 && s1 <= t2 + x && t2 + x <= s2)
			return (s2 - s1) * (t2 - t1) - (t2 - (s1 - x)) * ((t2 + x) - s1) / 2;
		if (s1 <= t1 + x && t1 + x <= s2 && s1 <= t2 + x && t2 + x <= s2)
			return ((s2 - (t1 + x)) + (s2 - (t2 + x))) * (t2 - t1) / 2;
		if (s2 <= t1 + x) return 0.0;
		if (t2 + x <= s1) return (s2 - s1) * (t2 - t1);
	};

	double fz = cacal(-w) - cacal(w);
	std::cout << std::fixed << std::setprecision(6) << fz / fm << '\n';
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int t;
	std::cin >> t;
	for (int i = 1; i <= t; ++i) {
		std::cout << "Case #" << i << ": ";
		sol();
	}

	return 0;
}