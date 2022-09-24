//
// Created by mrx on 2022/9/24.
//
#include <vector>
#include <algorithm>
#include <iostream>
#include <array>

using ll = long long;
using ull = unsigned long long;


int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::vector<bool> vis(4e4 + 10);
	std::vector<int> prime;
	for (int i = 2; i <= 4e4; ++i) {
		if (!vis[i])prime.push_back(i);
		for (int j = 0; j < prime.size() && i * prime[j] <= 4e4; ++j) {
			vis[i * prime[j]] = true;
			if (i % prime[j] == 0)break;
		}
	}

	int t;
	std::cin >> t;
	while (t--) {
		int n;
		std::cin >> n;
		ull ans1 = 1, ans2 = n;
		int tmp = n;
		for (int i = 0; i < prime.size() && prime[i] * prime[i] <= tmp; ++i) {
			if (tmp % prime[i] == 0) {
				int cnt = 0;
				while (tmp % prime[i] == 0)tmp /= prime[i], cnt++;
				ull cur = 1, base = prime[i] * prime[i];
				for (int j = 0; j < cnt; ++j) {
					cur += base;
					base *= (ull) prime[i] * (ull) prime[i];
				}
				ans1 *= cur;
				ans2 *= cnt + 1;
			}
		}
		if (tmp != 1)ans1 *= (1ull + (ull) tmp * (ull) tmp), ans2 *= 2ull;
		ull ans = ans1 - ans2;
		std::cout << ans << '\n';
	}
	return 0;
}