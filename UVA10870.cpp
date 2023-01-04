//
// Created by mrx on 2022/9/27.
//
#include <vector>
#include <algorithm>
#include <iostream>
#include <array>

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
			exit(2);
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

	std::vector<ll>& operator [](int idx) {
		return mat[idx];
	}

	friend matrix operator ^(matrix bas, long long x) {
		matrix ans(bas.n, bas.n);
		ans.E();
		for (; x; x >>= 1, bas = bas * bas)if (x & 1)ans = bas * ans;
		return ans;
	}
};


int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	ll n, d;
	while (std::cin >> d >> n >> mod && n) {
		matrix A(d, d);
		for (int i = 1; i < d; ++i)A[i][i - 1] = 1;
		std::vector<int> a(d);
		for (int i = 0; i < d; ++i) {
			std::cin >> a[i];
			a[i] %= mod;
		}
		for (int i = 0; i < d; ++i) {
			A[0][i] = a[i];
		}
		matrix f(d, 1);
		for (int i = 0; i < d; ++i) {
			std::cin >> f[d - i - 1][0];
			f[d - 1 - i][0] %= mod;
		}
		if (n <= d) {
			std::cout << f[n - 1][0] << '\n';
		} else {
			matrix ans = (A ^ (n - d)) * f;
			std::cout << ans[0][0] << '\n';
		}
	}
	return 0;
}