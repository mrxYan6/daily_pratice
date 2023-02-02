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
	int n, m;
	std::cin >> n >> m;

	std::vector a(n, std::vector<int>(m));
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			std::cin >> a[i][j];
		}
	}

	auto check = [&](int x) {
		std::vector pref(n + 1, std::vector<int>(m + 1));
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= m; ++j) {
				pref[i][j] = a[i - 1][j - 1] >= x;
			}
		}

		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= m; ++j) {
				pref[i][j] += pref[i - 1][j] + pref[i][j - 1] - pref[i - 1][j - 1];
			}
		}

		for (int i = x; i <= n; ++i) {
			for (int j = x; j <= m; ++j) {
				if (pref[i][j] - pref[i - x][j] - pref[i][j - x] + pref[i - x][j - x] == x * x)return true;
			}
		}
		return false;
	};

	int l = 0, r = std::min(n, m), ans = 0;
	while (l <= r) {
		int mid = (l + r) >> 1;

		if (check(mid)) {
			ans = mid;
			l = mid + 1;
		} else r = mid - 1;
	}
	std::cout << ans << '\n';

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