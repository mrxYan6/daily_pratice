//
// Created by mrx on 2023/2/20.
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
	int n;
	std::cin >> n;
	std::vector<i64> a(n + 1);
	for (int i = 0; i < n; ++i) {
		std::cin >> a[i];
	}
	for (int i = 1; i <= n; ++i) {
		a[i] += a[i - 1];
	}
	if (a[n] % 3 != 0)std::cout << "0\n";
	else {
		std::vector<int> cnt2(n);
		for (int i = 0; i < n - 1; ++i) {
			cnt2[i] = a[i] == a[n] / 3 * 2;
		}
		for (int i = n - 2; i >= 0; --i) {
			cnt2[i] += cnt2[i + 1];
		}
		i64 ans = 0;
		for (int i = 0; i < n - 1; ++i) {
			if (a[i] == a[n] / 3)ans += cnt2[i + 1];
		}
		std::cout << ans << '\n';
	}
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	int t = 1;
//	std::cin >> t;
	while (t--) {

		solve();
	}
	return 0;
}