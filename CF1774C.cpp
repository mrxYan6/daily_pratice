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
	int n;
	std::cin >> n;
	n--;
	std::string s;
	std::cin >> s;
	int cnt = 1;
	for (int i = 0; i < n; ++i) {
		if (i && s[i] == s[i - 1])cnt++;
		else cnt = 0;
		std::cout << i + 1 - cnt << ' ';
	}
	std::cout << '\n';
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