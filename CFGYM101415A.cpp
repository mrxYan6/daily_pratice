//
// Created by meiru on 2022/9/22.
//
#include <bits/stdc++.h>

using ll = long long;

int main() {
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
#endif
#ifndef LOCAL
	freopen("A.in", "r", stdin);

	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
#endif
	int n, k, m;
	while (std::cin >> n >> k >> m && n + k + m) {
		int f = 0;
		for (int i = 2; i <= n; ++i)f = (f + k) % i;
		std::cerr << f << '\n';
		f = (m - k + 1 + f) % n;
		if (f <= 0)f += n;
		std::cout << f << '\n';
	}
	return 0;
}