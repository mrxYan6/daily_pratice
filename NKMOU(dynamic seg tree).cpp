//
// Created by mrx on 2022/10/22.
//

#include <vector>
#include <algorithm>
#include <iostream>
#include <functional>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <array>

using ll = long long;


const ll INF = 1e18;

struct Nod {
	int l, r;
	ll max_pref, sum, val;//tag1为加，tag2为改变

	Nod(int l = 0, int r = 0, ll val = 0) : l(l), r(r), sum((r - l + 1) * val), val(val) {
		max_pref = (std::max(0ll, sum));
	}

	inline void apply(ll v2 = INF) {
		if (v2 != INF) {
			sum = (r - l + 1) * v2;
			max_pref = std::max(sum, 0ll);
			val = v2;
		}
	}

	//根据需要改变
	friend Nod merge(const Nod& lhs, const Nod& rhs) {
		Nod ans;
		ans.l = lhs.l, ans.r = rhs.r;
		ans.sum = lhs.sum + rhs.sum;
		ans.max_pref = std::max({lhs.sum + rhs.max_pref, lhs.max_pref, 0ll});
		return ans;
	}
};

struct seg {
	Nod x;
	seg* lson, * rson;

	seg(int l, int r, ll val = 0) : x(l, r, val) {
		lson = rson = nullptr;
	}

	void push_up() {
		auto nxt = merge(lson->x, rson->x);
		x.max_pref = nxt.max_pref;
		x.sum = nxt.sum;
	}

	void push_down() {
		int m = (x.l + x.r) >> 1;
		delete lson;
		delete rson;
		lson = new seg(x.l, m, x.val);
		rson = new seg(m + 1, x.r, x.val);
	}

	~seg() {
		delete lson;
		delete rson;
	}

	ll query(ll h) {
		if (h >= x.max_pref) {
			return x.r;
		}
		if (lson == nullptr)return x.l + (h / x.val) - 1;
		return h >= lson->x.max_pref ? rson->query(h - lson->x.sum) : lson->query(h);
	}

	void modify(int l, int r, int val) {
		if (l <= x.l && x.r <= r) {
			x.apply(val);
			delete lson;
			delete rson;
			lson = rson = nullptr;
			return;
		}

		if (lson == nullptr)push_down();
		int m = (x.l + x.r) >> 1;
		if (l <= m)lson->modify(l, r, val);
		if (r > m)rson->modify(l, r, val);
		push_up();
	}

	void show() {
		if (lson == nullptr) {
			for (int i = x.l; i <= x.r; ++i)std::cerr << x.val << ' ';
			return;
		}
		lson->show();
		rson->show();
	}
};

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int n;
	std::cin >> n;
	seg tree(1, n, 0);

	char opt;
	while (std::cin >> opt && opt != 'E') {
//		tree.show();
//		std::cerr << '\n';
		if (opt == 'Q') {
			ll h;
			std::cin >> h;
			std::cout << tree.query(h) << '\n';
		} else {
			int l, r, v;
			std::cin >> l >> r >> v;
			tree.modify(l, r, v);
//			std::cerr << "MM\n";
		}
	}

	return 0;
}