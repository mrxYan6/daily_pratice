//
// Created by mrx on 2022/9/30.
//
#include <vector>
#include <algorithm>
#include <iostream>
#include <bitset>
#include <array>

using ll = long long;

struct matrix {
	std::vector<std::bitset<510>> mat;
	int n;

	matrix(int _n) {
		mat.resize(_n, {});
		n = _n;
	}

	int gauss(int m) {
		int row = 0, col = 0;
		for (; row < n && col < m; ++col) {
			int nxt;
			for (nxt = row; nxt < n - 1; nxt++)if (mat[nxt][col])break;
			if (!mat[nxt][col])continue;
			std::swap(mat[nxt], mat[row]);
			for (int r = 0; r < n; ++r) {
				if (row == r)continue;
				if (mat[r][col]) mat[r] ^= mat[row];
			}
			row++;
		}
		return row;
	}

	void show(int m) {
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j)std::cout << mat[i][j] << ' ';
			std::cout << '\n';
		}
	}

	std::bitset<510>& operator [](int idx) { return mat[idx]; }
};


int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::vector<int> prime, vis(666);
	for (int i = 2; i <= 555; ++i) {
		if (!vis[i])prime.push_back(i);
		for (int j = 0; j < prime.size() && i * prime[j] <= 555; ++j) {
			vis[i * prime[j]] = 1;
			if (i % prime[j] == 0)break;
		}
	}

	int t;
	std::cin >> t;
	while (t--) {
		int n;
		std::cin >> n;
		matrix mat(n);
		int maxm = 0;
		std::vector<ll> num(n);
		for (int i = 0; i < n; ++i) {
			ll x;
			std::cin >> x;
			num[i] = x;
			for (int j = 0; j < prime.size() && prime[j] <= x; ++j) {
				while (x % prime[j] == 0) {
					maxm = std::max(maxm, j + 1);
					x /= prime[j];
					mat[i].flip(j);
				}
			}
		}
		int cnt = mat.gauss(maxm);
		unsigned long long ans = (1ull << (n - cnt)) - 1;
		std::cout << ans << '\n';
	}

	return 0;
}