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

template<typename T>
T power(T a, ll b) {
	T ans = 1;
	for (; b; b >>= 1, a = a * a)if (b & 1)ans = ans * a;
	return ans;
}

void sol() {
	int n, k, m;
	std::cin >> n >> k >> m;
	std::vector<double> prob(n);
	for (int i = 0; i < n; ++i)std::cin >> prob[i];
	std::vector<double> dp(m + 1);
	dp[0] = 0;
	for (int i = 1; i <= m; ++i) {
		double f = 1;
		for (int j = 0; j < n; ++j) {
			dp[i] += prob[j] * f;
			f *= dp[i - 1];
		}
	}
	std::cout << std::fixed << std::setprecision(6) << power(dp[m], k) << '\n';

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