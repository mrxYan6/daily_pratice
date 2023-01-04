//
// Created by meiru on 2023/1/3.
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

void sol() {
	int n, m, k;
	std::cin >> n >> m >> k;
	std::vector<i64> a(m);
	for (auto& x: a)std::cin >> x;
	std::sort(a.begin(), a.end(), std::greater());
	int cnt = std::count(a.begin(), a.end(), a[0]);
	if (a[0] * k + cnt - k > n)std::cout << "NO\n";
	else std::cout << "YES\n";
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	int t;
	std::cin >> t;
	while (t--) {
		sol();
	}
	return 0;
}