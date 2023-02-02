//
// Created by meiru on 2023/1/21.
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
const int N = 1e6 + 10;

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::vector<int> vis(N), primes, phi(N);
	std::vector<i64> pref(N);
//	phi[1] = 1;
	for (int i = 2; i < N; ++i) {
		if (!vis[i]) {
			primes.push_back(i);
			phi[i] = i - 1;
		}
		for (auto p: primes) {
			if (i * p >= N)break;
			vis[i * p] = true;
			if (i % p == 0) {
				phi[i * p] = phi[i] * p;
				break;
			} else {
				phi[i * p] = phi[i] * (p - 1);
			}
		}
	}
	for (int i = 1; i < N; ++i)pref[i] = pref[i - 1] + phi[i];

	int t;
	std::cin >> t;
	while (t--) {
		int n;
		i64 m;
		std::cin >> n >> m;
		i64 ans = 0;
		for (int k = n; k >= 2; --k) {
			if (m < k - 1)continue;
			ans += std::min(m, pref[n / k]) / (k - 1) * k;
			m -= std::min(m, pref[n / k]) / (k - 1) * (k - 1);
		}
		if (m == 0)std::cout << ans << '\n';
		else std::cout << "-1\n";
	}

	return 0;
}