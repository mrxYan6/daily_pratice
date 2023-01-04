//
// Created by mrx on 2022/10/8.
//
#include <vector>
#include <algorithm>
#include <iostream>
#include <array>

using ll = long long;

template<class T>
struct Fenwick {
	const int n;
	std::vector<T> a;

	Fenwick(int n) : n(n), a(n + 1) {}

	void add(int idx, T val) {
		for (int i = idx; i <= n; i += i & -i) a[i] += val;
	}

	T qry(int idx) {
		T res = 0;
		for (int i = idx; i > 0; i -= i & -i) res += a[i];
		return res;
	}

	T range_qry(int l, int r) {
		l = std::max(0, l);
		r = std::min(r, n);
		if (l > r) return 0;
		return qry(r) - qry(l - 1);
	}
};

void sol() {
	int n;
	std::cin >> n;
	std::vector<int> a(n), l(n), r(n);
	int maxn = 0;
	for (int i = 0; i < n; ++i) {
		std::cin >> a[i];
		maxn = std::max(maxn, a[i]);
	}

	Fenwick<int> c1(maxn), c2(maxn);
	for (int i = 0; i < n; ++i) {
		l[i] = c1.qry(a[i]);
		c1.add(a[i], 1);
	}
	for (int i = n - 1; i >= 0; --i) {
		r[i] = c2.qry(a[i]);
		c2.add(a[i], 1);
	}

	ll ans = 0;
	for (int i = 0; i < n; ++i) {
		ans += l[i] * (n - i - r[i] - 1) + (i - l[i]) * r[i];
	}
	std::cout << ans << '\n';
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	int t;
	std::cin >> t;
	while (t--)sol();
	return 0;
}