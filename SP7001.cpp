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
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
#endif
	std::vector<int> prime, vis(1e6 + 10), mu(1e6 + 10);
	mu[1] = 1;
	for (int i = 2; i <= 1e6; ++i) {
		if (!vis[i]) {
			mu[i] = -1;
			prime.push_back(i);
		}
		for (int j = 0; j < prime.size() && i * prime[j] <= 1e6; ++j) {
			vis[i * prime[j]] = 1;
			if (i % prime[j] == 0) {
				mu[i * prime[j]] = 0;
				break;
			} else mu[i * prime[j]] = mu[i] * -1;
		}
	}

	int t;
	std::cin >> t;
	while (t--) {
		int n;
		std::cin >> n;
		ll ans = 3;
		for (int d = 1; d <= n; ++d) {
			ll k = n / d;
			ans += mu[d] * (k * k * (k + 3));
		}
		std::cout << ans << '\n';
	}
	return 0;
}