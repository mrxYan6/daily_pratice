//
// Created by mrx on 2022/9/24.
//

#include <vector>
#include <algorithm>
#include <iostream>
#include <array>

using ll = long long;

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::vector<int> prime, vis(5e5 + 10), mu(5e5 + 10), h(5e5 + 10);
	mu[1] = 1, h[1] = 0;
	for (int i = 2; i <= 5e5; ++i) {
		if (!vis[i])prime.push_back(i), mu[i] = -1, h[i] = 1;
		for (int j = 0; j < prime.size() && i * prime[j] <= 5e5; ++j) {
			vis[i * prime[j]] = 1;
			h[prime[j] * i] = h[i] + 1;
			if (i % prime[j]) {
				mu[i * prime[j]] = -mu[i];
			} else {
				mu[i * prime[j]] = 0;
				break;
			}
		}
	}

	std::vector<std::array<ll, 20>> pref(5e5 + 10);
	for (int i = 1; i <= 5e5; ++i) {
		for (int k = 1; i * k <= 5e5; k++) {
			pref[i * k][h[i]] += mu[k];
		}
	}

	for (int i = 0; i <= 5e5; ++i) for (int j = 1; j < 20; ++j)pref[i][j] += pref[i][j - 1];
	for (int i = 1; i < 5e5; ++i)for (int j = 0; j < 20; ++j)pref[i][j] += pref[i - 1][j];

	int q;
	std::cin >> q;
	while (q--) {
		ll n, m, p;
		std::cin >> n >> m >> p;
		if (p >= 18) {
			std::cout << n * m << '\n';
		} else {
			if (n > m)std::swap(n, m);
			ll ans = 0;
			for (ll l = 1, r; l <= n; l = r + 1) {
				r = std::min(n / (n / l), m / (m / l));
				ans += (pref[r][p] - pref[l - 1][p]) * (n / l) * (m / l);
			}
			std::cout << ans << '\n';

		}
	}
	return 0;
}