//
// Created by mrx on 2022/10/8.
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
	int n;
	while (std::cin >> n && n) {
		int q;
		std::cin >> q;
		std::vector<int> a(n + 1);
		for (int i = 0; i < n; ++i)std::cin >> a[i];
		a[n] = a[n - 1] + 1;

		std::vector<int> val, L, R, cnt;
		{
			int l = 0, r = 0;
			while (l < n) {
				if (r <= n && a[l] == a[r])r++;
				else {
					val.push_back(a[l]);
					cnt.push_back(r - l);
					L.push_back(l);
					R.push_back(r - 1);
					l = r;
				}
			}
		}

		std::vector<int> id(n);
		{
			int ptr = 0;
			for (int i = 0; i < n; ++i) {
				if (a[i] == val[ptr]) id[i] = ptr;
				else {
					ptr++;
					id[i] = ptr;
				}
			}
		}

		int sector = cnt.size();
		std::vector<std::array<int, 21>> st(sector);
		for (int i = 0; i < sector; ++i)st[i][0] = cnt[i];

		for (int i = 0; i < 20; ++i) {
			for (int j = 0; j + (1 << i) < sector; ++j) {
				st[j][i + 1] = std::max(st[j][i], st[j + (1 << i)][i]);
			}
		}

		std::function<int(int, int)> qry = [&](int l, int r) {
			int len = r - l + 1;
			int lg = 31 - __builtin_clz(len);
			return std::max(st[l][lg], st[r - (1 << lg) + 1][lg]);
		};
//		std::cerr << __builtin_clz(1) << '\n';
		while (q--) {
			int l, r;
			int ans = 0;
			std::cin >> l >> r;
			l--, r--;
			if (id[l] == id[r]) {
				ans = r - l + 1;
			} else {
				ans = std::max(R[id[l]] - l + 1, r - L[id[r]] + 1);
				if (id[l] + 1 < id[r]) {
					ans = std::max(ans, qry(id[l] + 1, id[r] - 1));
				}
			}
			std::cout << ans << '\n';
		}
	}
	return 0;
}