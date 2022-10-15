//
// Created by mrx on 2022/10/15.
//

#include <vector>
#include <algorithm>
#include <iostream>
#include <array>
#include <numeric>
#include <cassert>

using ll = long long;


const ll INF = 1e18;

struct SegmentTree {
	struct Nod {
		int l, r;
		ll sum;//tag1为加，tag2为改变
		ll suml, sumr, max, lans, rans, ls, rs;

		Nod(int l = 0, int r = 0) : l(l), r(r), sum(0) {}

		inline void apply(ll v1) {
			suml = sumr = max = sum = v1;
		}

	};

	//根据需要改变
	friend Nod merge(const Nod& lhs, const Nod& rhs) {
		Nod ans;
		ans.l = lhs.l, ans.r = rhs.r;
		ans.sum = lhs.sum + rhs.sum;
		if (lhs.max >= lhs.sumr + rhs.suml) {
			if (lhs.max >= rhs.max) {
				ans.lans = lhs.lans;
				ans.rans = lhs.rans;
				ans.max = lhs.max;
			} else {
				ans.lans = rhs.lans;
				ans.rans = rhs.rans;
				ans.max = rhs.max;
			}
		} else {
			if (lhs.sumr + rhs.suml >= rhs.max) {
				ans.lans = lhs.rs;
				ans.rans = rhs.ls;
				ans.max = lhs.sumr + rhs.suml;
			} else {
				ans.lans = rhs.lans;
				ans.rans = rhs.rans;
				ans.max = rhs.max;
			}
		}
		if (lhs.suml >= lhs.sum + rhs.suml) {
			ans.suml = lhs.suml;
			ans.ls = lhs.ls;
		} else {
			ans.suml = lhs.sum + rhs.suml;
			ans.ls = rhs.ls;
		}
		if (lhs.sumr + rhs.sum >= rhs.sumr) {
			ans.sumr = lhs.sumr + rhs.sum;
			ans.rs = lhs.rs;
		} else {
			ans.sumr = rhs.sumr;
			ans.rs = rhs.rs;
		}
//		ans.suml = std::max(lhs.suml, lhs.sum + rhs.suml);
//		ans.sumr = std::max(rhs.sumr, lhs.sumr + rhs.sum);
		return ans;
	}

	std::vector<Nod> tree;
	int n;
#define lson l,m,rt<<1
#define rson m+1,r,rt<<1|1
#define T tree[rt]
#define LS tree[rt<<1]
#define RS tree[rt<<1|1]

	inline void push_up(int rt) {
		T = merge(LS, RS);
	}


	template<typename M>
	void build(int l, int r, int rt, const std::vector<M>& base) {
		T.l = l, T.r = r;
		if (l == r) {
			T.lans = T.rans = T.ls = T.rs = l;
			T.apply(base[l]);
			return;
		}
		int m = (l + r) >> 1;
		build(lson, base);
		build(rson, base);
		push_up(rt);
	}

	Nod qry(int L, int R, int rt) {
		if (L <= T.l && T.r <= R) {
			return T;
		}
		int m = (T.l + T.r) >> 1;
		Nod res;
		if (R <= m)res = qry(L, R, rt << 1);
		else if (L > m)res = qry(L, R, rt << 1 | 1);
		else res = merge(qry(L, R, rt << 1), qry(L, R, rt << 1 | 1));
		push_up(rt);
		return res;
	}

#undef lson
#undef rson
#undef T
#undef LS
#undef RS

	template<class Type>
	SegmentTree(const std::vector<Type>& a) {
		n = a.size();
		n--;
		tree.resize((n << 2) + 1);
		build(1, n, 1, a);
	}

	Nod query(int L, int R) {
		assert(0 < L && L <= R && R <= n);
		return qry(L, R, 1);
	}

	Nod query(int pos) {
		assert(pos > 0 && pos <= n);
		return qry(pos, pos, 1);
	}
};


int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int n, m;
	int cas = 1;
	while (std::cin >> n >> m) {
//		std::cin >> n >> m;
		std::vector<int> arr(n + 1);

		for (int i = 1; i <= n; ++i)std::cin >> arr[i];
		SegmentTree seg(arr);
		std::cout << "Case " << cas++ << ":\n";
		while (m--) {
			int a, b;
			std::cin >> a >> b;
			auto ans = seg.query(a, b);
			std::cout << ans.lans << ' ' << ans.rans << '\n';
		}
	}

	return 0;
}