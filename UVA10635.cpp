//
// Created by meiru on 2022/9/22.
//
#include <bits/stdc++.h>

using ll = long long;

int main() {
	int t;
	std::cin >> t;
	for (int cas = 1; cas <= t; ++cas) {
		std::cout << "Case " << cas << ": ";
		int n, p, q;
		std::cin >> n >> p >> q;
		std::vector<int> mp(n * n + 1, 0);
		std::vector<int> a(p + 1), b(q + 1);
		for (int i = 0; i <= p; ++i) std::cin >> a[i], mp[a[i]] = i + 1;
		std::vector<int> rem;
		for (int i = 0; i <= q; ++i) {
			std::cin >> b[i];
			if (mp[b[i]] != 0)rem.push_back(mp[b[i]]);
		}
		int len = rem.size();
		std::vector<std::vector<int>> dp(len + 1);
		std::vector<int> pos(len + 1, 0x3f3f3f3f);
		int ans = 0;
		for (int i = 0; i < len; ++i) {
			int k = std::lower_bound(pos.begin() + 1, pos.end(), rem[i]) - pos.begin();
			pos[k] = rem[i];
			ans = std::max(ans, k);
		}
		std::cout << ans << '\n';
	}
	return 0;
}