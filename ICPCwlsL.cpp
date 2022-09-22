//
// Created by mrx on 2022/9/17.
//

#include <algorithm>
#include <vector>
#include <iostream>

struct seg {
	struct nod {
		int l, r, val, lazy;

		nod(int l, int r, int val, int lz) : l(l), r(r), val(val), lazy(lz) {}

		nod() {}

		friend nod merge(const nod& lhs, const nod& rhs) {
			return {lhs.l, rhs.r, std::max(lhs.val, rhs.val), 0};
		}

		void apply(int lz) {
			val += lz;
			lazy += lz;
		}
	};

	std::vector<nod> a;

	seg(int n) {
		a.resize(n << 2 | 1);
		build(1, n, 1);
	}

	void push_down(int rt) {
		if (a[rt].lazy) {
			a[rt << 1].apply(a[rt].lazy);
			a[rt << 1 | 1].apply(a[rt].lazy);
			a[rt].lazy = 0;
		}
	}

	void build(int l, int r, int rt) {
		if (l == r) {
			a[rt] = nod(l, l, 0, 0);
			return;
		}
		int m = (l + r) >> 1;
		build(l, m, rt << 1);
		build(m + 1, r, rt << 1 | 1);
		a[rt] = merge(a[rt << 1], a[rt << 1 | 1]);
	}

	void modify(int L, int R, int c, int rt = 1) {
		if (a[rt].l >= L && a[rt].r <= R) {
			a[rt].val += c;
			a[rt].lazy += c;
			return;
		}
		int m = (a[rt].l + a[rt].r) >> 1;
		push_down(rt);
		if (L <= m) modify(L, R, c, rt << 1);
		if (m < R) modify(L, R, c, rt << 1 | 1);
		a[rt] = merge(a[rt << 1], a[rt << 1 | 1]);
	}

	nod qry(int L, int R, int rt = 1) {
		if (a[rt].l >= L && a[rt].r <= R) {
			return a[rt];
		}
		push_down(rt);
		nod ret;
		int m = (a[rt].l + a[rt].r) >> 1;
		if (m >= R) ret = qry(L, R, rt << 1);
		else if (m < L)ret = qry(L, R, rt << 1 | 1);
		else ret = merge(qry(L, R, rt << 1), qry(L, R, rt << 1 | 1));
		a[rt] = merge(a[rt << 1], a[rt << 1 | 1]);
		return ret;
	}
};

int main() {
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
#endif
#ifndef LOCAL
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
#endif

	std::string s, t;
	std::cin >> s >> t;
	s = '*' + s;
	t = '#' + t;
	int n = s.length(), m = t.length();
	std::vector<std::pair<int, int>> pos(26, {1e9, -1e9});
	seg dp(m);

	for (int i = 1; i < m; ++i) {
		pos[t[i] - 'a'].first = std::min(pos[t[i] - 'a'].first, i);
		pos[t[i] - 'a'].second = std::max(pos[t[i] - 'a'].second, i);
	}
	for (int i = 1; i < n; ++i) {
		auto [l, r] = pos[s[i] - 'a'];
		if (l == 1e9 && r == -1e9) {
			dp.modify(1, m, 1);
		} else {
			int mx = dp.qry(r, m).val;
			int cur = dp.qry(l, l).val;
			if (mx + 1 > cur)dp.modify(l, l, mx + 1 - cur);
		}
	}
	std::cout << dp.qry(1, m, 1).val << '\n';
}