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

	std::vector<int> a(n), b(n);
	for (auto& x: a) {
		std::cin >> x;
	}
	for (auto& x: b) {
		std::cin >> x;
	}

	std::vector<int> d(n + 1);
	for (int i = 0; i < n; i++) {
		if (a[i] > b[i]) {
			d[b[i]]++;
			d[a[i]]--;
		}
	}

	for (int i = 1; i <= n; ++i)d[i] += d[i - 1];

	std::vector<int> ans;
	for (int k = 1; k <= n; ++k) {
		bool ok = true;
		for (int i = k; i <= n; i += k) {
			if (d[i])ok = false;
		}
		if (ok)ans.push_back(k);
	}

	std::cout << ans.size() << '\n';
	for (int i = 0; i < ans.size(); ++i)std::cout << ans[i] << " \n"[i + 1 == ans.size()];
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