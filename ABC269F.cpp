//
// Created by mrx on 2022/9/17.
//
#include <iostream>
#include <vector>
#include <algorithm>

using ll = long long;

int main() {
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
#endif
#ifndef LOCAL
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
#endif
	int n, m;
	std::cin >> n >> m;
	int q;
	std::cin >> q;
	while (q--) {
		int x1, x2, y1, y2;
		std::cin >> x1 >> x2 >> y1 >> y2;
		int len = y2 - y1;

	}
	return 0;
}