//
// Created by mrx on 2022/12/9.
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

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	i64 n, x;
	std::cin >> n >> x;
	std::vector<int> a(n);
	std::map<int, int> mp;
	for (int i = 0; i < n; ++i) {
		std::cin >> a[i];
		mp[a[i]]++;
	}
	bool ok = true;
	for (int i = 1; i < x; ++i) {
		if (mp.count(i)) {
			mp[i + 1] += mp[i] / (i + 1);
			mp[i] %= (i + 1);
			if (mp[i]) {
				ok = false;
				break;
			}
		}
	}
	if (ok)std::cout << "Yes\n";
	else std::cout << "No\n";

	return 0;
}