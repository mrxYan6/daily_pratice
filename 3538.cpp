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

	hash(const std::string& s) {
		HASH.resize(s.length() + 1);
		for (int i = 0; i < s.length(); ++i) {
			HASH[i + 1].first = (HASH[i].first * seed % mod1 + s[i] - 'a') % mod1;
			HASH[i + 1].second = (HASH[i].second * seed % mod2 + s[i] - 'a') % mod2;
		}
	}


};

void sol() {
	int n;
	std::cin >> n;
	std::string s;
	std::cin >> s;
	int q;
	std::cin >> q;
	for (int i = 0; i < q; ++i) {
		int a, b;
		std::cin >> a >> b;
		int l = b - a;

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