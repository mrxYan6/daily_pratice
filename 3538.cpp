//
// Created by mrx on 2022/9/16.
//
#include <iostream>
#include <vector>

using ll = long long;

struct hash {
	static constexpr int mod1 = 998244353, mod2 = 1e9 + 7, seed = 233;
	std::string s;
	std::vector<std::pair<ll, ll>> HASH;
	std::vector<std::pair<ll, ll>> POWER;

	hash(const std::string& s) {
		HASH.resize(s.length() + 1);
		POWER.resize(s.length() + 1);
		for (int i = 0; i < s.length(); ++i) {
			HASH[i + 1].first = (HASH[i].first * seed % mod1 + s[i] - 'a') % mod1;
			HASH[i + 1].second = (HASH[i].second * seed % mod2 + s[i] - 'a') % mod2;
		}
		POWER[0] = {1, 1};
		for (int i = 0; i < s.length(); ++i) {
			POWER[i + 1].first = POWER[i].first * seed % mod1;
			POWER[i + 1].second = POWER[i].second * seed % mod2;
		}
	}

	std::pair<ll, ll> getHash(int l, int r) {
		std::pair<ll, ll> ans;
		ans.first = ((HASH[r].first - HASH[l - 1].first * POWER[r - l + 1].first % mod1) % mod1 + mod1) % mod1;
		ans.second = ((HASH[r].second - HASH[l - 1].second * POWER[r - l + 1].second % mod2) % mod2 + mod2) % mod2;
		return ans;
	}

};

void sol() {
	int n;
	std::cin >> n;

	std::vector<int> prime, vis(n + 1), g(n + 1);
	for (int i = 2; i <= n; ++i) {
		if (!vis[i]) {
			prime.push_back(i);
			g[i] = i;
		}
		for (int j = 0; j < prime.size() && i * prime[j] <= n; ++j) {
			vis[i * prime[j]] = 1, g[i * prime[j]] = prime[j];
			if (i % prime[j] == 0)break;
		}
	}

	std::string s;
	std::cin >> s;
	hash HA(s);
	int q;
	std::cin >> q;
	for (int i = 0; i < q; ++i) {
		int a, b;
		std::cin >> a >> b;
//		a--, b--;
		int ans = b - a + 1;
		int len = ans;
		while (len > 1) {
			if (HA.getHash(a + ans / g[len], b) == HA.getHash(a, b - ans / g[len]))ans /= g[len];
			len /= g[len];
		}
		std::cout << ans << '\n';
	}
}

int main() {
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
#endif
#ifndef LOCAL
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
#endif
	sol();
	return 0;
}