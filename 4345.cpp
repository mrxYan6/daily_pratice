//
// Created by mrx on 2022/10/5.
//

#include <vector>
#include <algorithm>
#include <iostream>
#include <array>

using ll = long long;

const int mod = 2333;

ll quickPow(ll base, ll fact, ll p) {
	ll ans = 1;
	while (fact) {
		if (fact & 1) ans = ans * base % p;
		base = base * base % p;
		fact >>= 1;
	}
	return ans;
}


int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::vector<ll> fact(3000), inv(3000);
	fact[0] = inv[0] = 1;
	for (int i = 1; i <= 2333; ++i) {
		fact[i] = fact[i - 1] * i % mod;
		inv[i] = quickPow(fact[i], mod - 2, mod);
	}

	int t;
	std::cin >> t;
	while (t--) {
		ll n, k;
		std::cin >> n >> k;

	}
	return 0;
}