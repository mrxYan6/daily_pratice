//
// Created by meiru on 2023/1/20.
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

	std::vector<int> a(n);
	for (int i = 0; i < n; ++i)std::cin >> a[i];

	std::vector<int> c(n * 2);
	i64 ans = 0;
	int p = 0;
	c[p]++;
	for (int i = 0; i < n; ++i) {
		p ^= a[i];
		for (int j = 0; j * j < n * 2; ++j) {
			if ((p ^ (j * j)) >= 2 * n)break;
			ans += c[p ^ (j * j)];
		}
		c[p]++;
	}

	std::cout << 1ll * n * (n + 1) / 2 - ans << '\n';
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	int t;
	std::cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}