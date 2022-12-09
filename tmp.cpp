//
// Created by meiru on 2022/12/6.
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

using ll = long long;

long long exgcd(long long a, long long b, long long& x, long long& y) {
	if (b == 0) {
		x = 1, y = 0;
		return a;
	}
	ll d = exgcd(b, a % b, x, y);
	ll t = x;
	x = y;
	y = t - a / b * x;
	return d;
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	i64 n, m;
	std::cin >> n >> m;
	i64 sum = 0;
	for (int i = 0; i < n; ++i) {
		i64 x;
		std::cin >> x;
		(sum += x) %= m;
	}
	if (m == 1) {
		std::cout << "0\n0 0\n";
		return 0;
	}
	if (!(n & 1)) {
		i64 mid, t;
		i64 g = exgcd(n / 2, m, mid, t);
		i64 res = sum % g;
		i64 cnt = (res - sum) / g;
		mid = mid * cnt % m;
		mid = (mid % m + m) % m;
		std::cout << res << '\n';
		if (mid & 1) {
			i64 d = (mid - 1) / 2 - n / 2;
			d = (m + d % m) % m;
			std::cout << d << ' ' << 1 << '\n';
		} else {
			i64 d = mid / 2;
			d = (m + d % m) % m;
			std::cout << d << ' ' << 0 << '\n';
		}
	} else {
		i64 mid, t;
		i64 g = exgcd(n, m, mid, t);
		i64 res = sum % g;
		i64 cnt = (res - sum) / g;
		mid = mid * cnt % m;
		mid = (mid % m + m) % m;
		std::cout << res << '\n';
		std::cout << (m + mid % m) % m << ' ' << 0 << '\n';
	}
	return 0;
}