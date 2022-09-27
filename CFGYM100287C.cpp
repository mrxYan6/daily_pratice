//
// Created by mrx on 2022/9/27.
//
#include <vector>
#include <algorithm>
#include <iostream>
#include <array>
#include <ios>
#include <iomanip>

using ll = long long;
int mod;

struct matrix {
	std::vector<std::vector<ll>> mat;
	ll n, m;

	matrix(ll a, ll b) {
		n = a, m = b;
		mat.clear();
		mat.resize(n);
		for (auto& x: mat)x.resize(m, 0);
	}

	void clear() {
		for (ll i = 0; i < n; ++i) {
			for (ll j = 0; j < m; ++j)mat[i][j] = 0;
		}
	}

	void E() {
		clear();
		for (ll i = 0; i < std::min(n, m); ++i) {
			mat[i][i] = 1;
		}
	}

	void show() {
		for (auto x: mat) {
			for (auto y: x)std::cout << y << ' ';
			std::cout << '\n';
		}
	}

	matrix operator *(const matrix& rhs) {
		matrix ans(n, rhs.m);
		if (m != rhs.n) {
			std::cerr << "Matrix not matching!";
		}
		for (ll i = 0; i < n; ++i) {
			for (ll j = 0; j < m; ++j) {
				for (ll k = 0; k < rhs.m; ++k) {
					ans.mat[i][k] = (ans.mat[i][k] + mat[i][j] * rhs.mat[j][k] % mod) % mod;
				}
			}
		}
		return ans;
	}

	matrix operator &(const matrix& rhs) {
		matrix ans(n, n);
		std::vector<ll> line(n);
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				line[j] = (line[j] + mat[0][i] * rhs[i][j] % mod) % mod;
			}
		}
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				ans[i][(i + j) % n] = line[j];
			}
		}
		return ans;
	}

	friend matrix operator ^(matrix bas, long long x) {
		matrix ans(bas.n, bas.n);
		ans.E();
		for (; x; x >>= 1, bas = bas & bas)if (x & 1)ans = ans & bas;
		return ans;
	}

	std::vector<ll>& operator [](int idx) {
		return mat[idx];
	}

	const std::vector<ll>& operator [](int idx) const {
		return mat[idx];
	}
};

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	freopen("cell.in", "r", stdin);
	freopen("cell.out", "w", stdout);

	int n, d, k;
	std::cin >> n >> mod >> d >> k;
	matrix F(n, 1);
	for (int i = 0; i < n; ++i)std::cin >> F[i][0];
	matrix A(n, n);
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			if (std::min(std::abs(i - j), n - std::abs(i - j)) <= d)A[i][j] = 1;
		}
	}
	matrix ans = (A ^ k) * F;
	for (int i = 0; i < n; ++i)std::cout << ans[i][0] << ' ';
	std::cout << '\n';

	return 0;
}