//
// Created by mrx on 2022/10/5.
//
#include <vector>
#include <algorithm>
#include <iostream>
#include <array>

using ll = long long;

ll power(ll a, ll b, ll p) {
	ll ans = 1;
	for (; b; b >>= 1, a = a * a % p)if (b & 1)ans = ans * a % p;
	return ans;
}

void sol() {
	int n, m, p;
	std::cin >> n >> m >> p;
	std::vector<int> fact(n + m + 1), inv(n + m + 1);
	fact[0] = 1, inv[0] = 1;
	for (int i = 1; i <= n + m; ++i) {
		fact[i] = 1ll * fact[i - 1] * i % p;
		inv[i] = power(fact[i], p - 2, p);
	}
	auto C = [&](int i, int j) {
		return i < j ? 0ll : 1ll * fact[i] * inv[j] % p * inv[i - j] % p;
	};
	std::function<ll(int, int, int)> lucas = [&](int i, int j, int p) -> ll {
		return j == 0 ? 1ll : 1ll * C(i % p, j % p) * lucas(i / p, j / p, p) % p;
	};
	std::cout << lucas(n + m, n, p) << '\n';
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