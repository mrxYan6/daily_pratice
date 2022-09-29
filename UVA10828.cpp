//
// Created by mrx on 2022/9/29.
//

#include <vector>
#include <algorithm>
#include <iostream>
#include <array>
#include <iomanip>

using ll = long long;

const double eps = 1e-8;

struct matrix {
	std::vector<std::vector<double>> mat;
	int n, m;

	matrix(int n, int m) : mat(n, std::vector<double>(m)), n(n), m(m) {}

	void gauss() {
		for (int row = 0; row < n; ++row) {
			int nxt;
			for (nxt = row; nxt < n - 1; nxt++)if (std::abs(mat[nxt][row]) > eps)break;
			if (std::abs(mat[nxt][row]) < eps)continue;
			std::swap(mat[nxt], mat[row]);
			for (int r = 0; r < n; ++r) {
				if (row == r)continue;
				for (int j = m - 1; j >= row; --j)mat[r][j] -= mat[r][row] / mat[row][row] * mat[row][j];
			}
		}
	}

	void show() {
		for (auto& x: mat) {
			for (auto v: x)std::cout << v << ' ';
			std::cout << '\n';
		}
	}

	std::vector<double>& operator [](int idx) {
		return mat[idx];
	}
};

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int cas = 1;
	int n;
	while (std::cin >> n && n) {
		std::cout << "Case #" << cas++ << ":\n";
		std::vector<std::vector<int>> adj(n);
		std::vector<int> out(n);

		int u, v;
		while (std::cin >> u >> v && u + v) {
			u--, v--;
			adj[v].push_back(u);
			out[u]++;
		}

		matrix mat(n, n + 1);
		for (int i = 0; i < n; ++i) {
			mat[i][i] = 1;
			for (auto j: adj[i]) {
				mat[i][j] -= 1.0 / out[j];
			}
			if (i == 0)mat[i][n] = 1;
		}
		mat.gauss();
		std::vector<bool> ok(n);
		for (int i = n - 1; i >= 0; i--) {
			if (std::abs(mat[i][i]) < eps && std::abs(mat[i][n]) > eps) ok[i] = true;
			for (int j = i + 1; j < n; j++) {
				if (std::abs(mat[i][j]) > eps && ok[j]) ok[i] = true;
			}
		}
		int q;
		std::cin >> q;
		while (q--) {
			int x;
			std::cin >> x;
			x--;
			if (ok[x])std::cout << "infinity\n";
			else {
				double ans = 0;
				if (std::abs(mat[x][x]) > eps)ans = mat[x][n] / mat[x][x];
				std::cout << std::fixed << std::setprecision(3) << ans << '\n';
			}
		}
	}
	return 0;
}